#include <bits/stdc++.h>

using namespace std;

void show_help()
{
    cout << "Uso: ./kosaraju [opcoes]\n"
    << "Opcoes:\n"
    << "  -h                mostra essa ajuda e sai\n"
    << "  -o <arquivo>      redireciona a saida para o 'arquivo'\n"
    << "  -f <arquivo>      indica o 'arquivo' que contem o grafo de entrada\n";
}

void dfs1(int v, vector<vector<int>>& adj, vector<int>& vis, vector<int>& pos)
{
    vis[v] = 1; // seta como visitado

    for (int w : adj[v])
        if (!vis[w])
            dfs1(w, adj, vis, pos);
    
    pos.push_back(v);
}

void dfs2(int v, vector<vector<int>>& adjT, vector<int>& vis, ostream& out)
{
    // repassa o dfs na pos ordem e vai imprimindo as cfc's
    vis[v] = 1;

    cout << v + 1 << " ";
    for (int w : adjT[v])
        if (!vis[w])
            dfs2(w, adjT, vis, out);
}

int main(int argc, char *argv[])
{
    string file_in = "";
    string file_out = "";

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

    vector<vector<int>> adj(n), adjT(n);
    
    int v, u;
    for (int i = 0; i < m; i++)
    {
        fin >> v >> u;
        v--, u--;
        
        adj[v].push_back(u);
        adjT[u].push_back(v);
    }
    fin.close();
    
    vector<int> vis(n, 0), pos;

    for (int i = 0; i < n; i++)
        if (!vis[i])
            dfs1(i, adj, vis, pos);

    fill(vis.begin(), vis.end(), 0); // reseta o vetor de visita a cada um dos vertices
    reverse(pos.begin(), pos.end());

    ostream* out;
    ofstream fout;

    if (!file_out.empty())
    {
        fout.open(file_out);
        if (!fout.is_open())
        {
            cerr << "Erro ao criar arquivo de saída: " << file_out << endl;
            return 1;
        }
        out = &fout;
    }
    else
        out = &cout;

    for (int v : pos)
        if (!vis[v])
        {
            dfs2(v, adjT, vis, *out);
            *out << endl;
        }

    return 0;
}