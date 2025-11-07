#include <bits/stdc++.h>

using namespace std;

void show_help()
{
    cout << "Uso: ./dijkstra [opcoes]\n"
    << "Opcoes:\n"
    << "  -h                mostra essa ajuda e sai\n"
    << "  -o <arquivo>      redireciona a saida para o 'arquivo'\n"
    << "  -f <arquivo>      indica o 'arquivo' que contem o grafo de entrada\n"
    << "  -i <vertice>      vertice inicial\n";
}

void dijkstra(vector<vector<pair<int, int>>>& adj, int s, ostream& out)
{
    int n = adj.size();
    vector<int> dist(n, INT_MAX);

    dist[s] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({dist[s], s});

    while (!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();

        for (auto [v, w] : adj[u])
        {
            if (dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    // imprimir a distancia final de cada vertice a partir do vertice inicial escolhido
    for (int i = 0; i < n; i++)
    {
        if (dist[i] == INT_MAX) out << "-1 ";
        else out << i + 1 << ":" << dist[i] << " ";
    }
    out << endl;
}

int main(int argc, char *argv[])
{
    string file_in = "";
    string file_out = "";
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
        else
        {
            cerr << "Parametro invalido" << arg << endl;
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

    for (int i = 0; i < m; i++)
    {
        int v, u, w;
        fin >> v >> u >> w;
        v--, u--;

        adj[v].push_back({u, w});
        adj[u].push_back({v, w});
    }
    fin.close();

    if (file_out.empty())
        dijkstra(adj, start, cout);
    else
    {
        ofstream fout(file_out);

        if (!fout.is_open())
        {
            cerr << "Erro ao criar arquivo de saida: " << file_out << endl;
            return 1;
        }

        dijkstra(adj, start, fout);
        fout.close();
    }

    return 0;
}
