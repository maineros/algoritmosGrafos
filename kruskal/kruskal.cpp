#include <bits/stdc++.h>

using namespace std;

vector<int> pai, rankv;

void show_help()
{
    cout << "Uso: ./kruskal [opcoes]\n"
    << "Opcoes:\n"
    << "  -h                mostra essa ajuda e sai\n"
    << "  -o <arquivo>      redireciona a saida para o 'arquivo'\n"
    << "  -f <arquivo>      indica o 'arquivo' que contem o grafo de entrada\n"
    << "  -s                imprime a solucao (arestas da AGM) em vez do custo\n";
}

void make_set(int v)
{
    pai[v] = v;
    rankv[v] = 0;
}

int find_set(int v)
{
    if (pai[v] != v)
        pai[v] = find_set(pai[v]);
    
    return pai[v];
}

void union_set(int v, int u)
{
    v = find_set(v);
    u = find_set(u);

    if (v != u)
    {
        if (rankv[v] < rankv[u])
            swap(v, u);

        pai[u] = v;

        if (rankv[v] == rankv[u])
            rankv[v]++;
    }
}

void kruskal(vector<pair<pair<int, int>, int>>& arestas, int n, bool printsol, ostream& out)
{
    // for v in V
        // make_set(v)

    // ordenar as arestas de forma crescente pelo peso w

    // for (u, v) in arestas // ordem crescente
        // if (find(u) != find(v))
            // E' = E' U {(u, v)}
            // union(find(u), find(v))

    pai.resize(n);
    rankv.resize(n);

    for (int i = 0; i < n; i++)
        make_set(i);

    sort(arestas.begin(), arestas.end(),
        [](auto& a, auto& b) {
            return a.second < b.second;
        });

    int total = 0;
    vector<pair<int, int>> agm;

    for (auto [edge, w] : arestas)
    {
        int v = edge.first;
        int u = edge.second;

        if (find_set(v) != find_set(u))
        {
            agm.push_back({v, u});
            total += w;
            union_set(v, u);
        }
    }
    
    if (printsol)
    {
        for (auto [v, u] : agm)
            out << "(" << v + 1 << ", " << u + 1 << ") ";
        out << endl;
    }
    else
        out << total << endl;
}

int main(int argc, char *argv[])
{
    string file_in = "";
    string file_out = "";
    bool printsol = false;

    for (int i = 1; i < argc; i++)
    {
        string arg = argv[i];

        if (arg == "-h")
        {
            show_help();
            return 0;
        }
        else if (arg == "-o" && i + 1 < argc)
            file_out = argv[++i];
        else if (arg == "-f" && i + 1 < argc)
            file_in = argv[++i];
        else if (arg == "-s")
            printsol = true;
        else
        {
            cerr << "Parametro invalido " << arg << endl;
            return 1;
        }
    }

    if (file_in.empty())
    {
        cerr << "Erro: arquivo de entrada nao especificado (-f <arquivo>).\n";
        return 1;
    }

    ifstream fin(file_in);
    if (!fin.is_open())
    {
        cerr << "Erro ao abrir arquivo: " << file_in << endl;
        return 1;
    }

    int n, m;
    fin >> n >> m;

    vector<pair<pair<int, int>, int>> arestas; // aresta e peso
    
    int v, u, w;
    for (int i = 0; i < m; i++)
    {
        fin >> v >> u >> w;
        v--, u--;

        arestas.push_back({{v, u}, w});
    }
    fin.close();

    if (file_out.empty())
        kruskal(arestas, n, printsol, cout);
    else
    {
        ofstream fout(file_out);
        if (!fout.is_open())
        {
            cerr << "Erro ao abrir arquivo de saida: " << file_out << endl;
            return 1;
        }
        kruskal(arestas, n, printsol, fout);
        fout.close();
    }

    return 0;
}