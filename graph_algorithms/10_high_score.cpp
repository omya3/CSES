#include <iostream>
#include <vector>
#include <tuple>
#include <set>

using namespace std;

void dfs(int i, vector<vector<int>> &adj, vector<int> &visited)
{
    visited[i] = 1;

    for (auto &it : adj[i])
    {
        if (visited[it] == 0)
        {
            dfs(it, adj, visited);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    int m;
    cin >> n >> m;

    vector<tuple<int, int, int>> edges;
    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < m; i++)
    {
        int u;
        int v;
        int w;

        cin >> u >> v >> w;

        edges.push_back({u, v, w});
        adj[v].push_back(u);
    }

    vector<long long> dist(n + 1, -1e17);
    dist[1] = 0;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < m; j++)
        {
            auto [a, b, w] = edges[j];

            if (dist[a] > -1e16 and dist[b] < dist[a] + w)
            {
                dist[b] = dist[a] + w;
            }
        }
    }

    set<int> cycle_nodes;

    for (int j = 0; j < m; j++)
    {
        auto [a, b, w] = edges[j];

        if (dist[a] > -1e16 and dist[b] < dist[a] + w)
        {
            cycle_nodes.insert(b);
        }
    }

    // apply dfs now
    vector<int> visited(n + 1, 0);

    dfs(n, adj, visited);
    for (int i = 1; i < n + 1; i++)
    {
        if (visited[i] == 1 and cycle_nodes.find(i) != cycle_nodes.end())
        {
            cout << -1 << "\n";
            return 0;
        }
    }
    cout << dist[n] << "\n";
    return 0;
}