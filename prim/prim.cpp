#include <bits/stdc++.h>

using namespace std;

void show_help()
{
    cout << "Uso: ./prim [opcoes]\n"
    << "Opcoes:\n"
    << "  -h                mostra essa ajuda e sai\n"
    << "  -o <arquivo>      redireciona a saida para o 'arquivo'\n"
    << "  -f <arquivo>      indica o 'arquivo' que contem o grafo de entrada\n"
    << "  -s                imprime a solucao (arestas da AGM) em vez do custo\n"
    << "  -i <vertice>      vertice inicial\n";
}

void prim(vector<vector<pair<int, int>>>& adj, bool printsol, int start, ostream& out)
{
    int n = adj.size();

    vector<int> custo(n, INT_MAX);
    vector<int> pai(n, -1);
    vector<bool> naAGM(n, false);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    custo[start] = 0;
    pq.push({0, start});

    while (!pq.empty())
    {
        // v = h.pop()

        // for u in N(v)
            // if custo[u] > w(v, u)
                // custo[u] = w(v , u)
                // increase_priority(u, custo[u])

        int v = pq.top().second;
        pq.pop();

        if (naAGM[v])
            continue;
        naAGM[v] = true;

        for (auto [u, w] : adj[v])
        {
            if (!naAGM[u] && w < custo[u])
            {
                custo[u] = w;
                pai[u] = v;
                pq.push({w, u});
            }
        }
    }

    int total = 0;
    vector<pair<int, int>> agm;

    for (int i = 0; i < n; i++)
    {
        if (pai[i] != -1)
        {
            agm.push_back({pai[i], i});
            total += custo[i];
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

    return;
}

int main(int argc, char *argv[])
{
    string file_in = "";
    string file_out = "";
    bool printsol = false;
    int start = -1;

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
        else if (arg == "-i" && i + 1 < argc)
            start = stoi(argv[++i]) - 1;
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

    if (start == -1)
    {
        start = 0;
        cerr << "Aviso: vertice inicial nao especificado. Usando vertice 1.\n";
    }

    ifstream fin(file_in);
    if (!fin.is_open())
    {
        cerr << "Erro ao abrir arquivo: " << file_in << endl;
        return 1;
    }

    int n, m;
    fin >> n >> m;

    vector<vector<pair<int, int>>> adj(n);
    
    int v, u, w;
    for (int i = 0; i < m; i++)
    {
        fin >> v >> u >> w;
        v--, u--;

        adj[v].push_back({u, w});
        adj[u].push_back({v, w});
    }
    fin.close();

    if (file_out.empty())
        prim(adj, printsol, start, cout);
    else
    {
        ofstream fout(file_out);
        if (!fout.is_open())
        {
            cerr << "Erro ao abrir arquivo de saida: " << file_out << endl;
            return 1;
        }
        prim(adj, printsol, start, fout);
        fout.close();
    }

    return 0;
}