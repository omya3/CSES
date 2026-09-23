#include <iostream>
#include <vector> // FIXED: Included required vector header
#include <queue>

using namespace std;

const int MOD = 1e9 + 7;

int main()
{
    // Fast I/O optimization for performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m))
        return 0;

    vector<vector<int>> adj(n + 1);
    vector<int> indegree(n + 1, 0);

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        indegree[v] += 1;
    }

    vector<long long> ways(n + 1, 0);

    queue<int> q;

    for (int i = 1; i < n + 1; i++)
    {
        if (indegree[i] == 0)
        {
            q.push(i);
        }
    }

    vector<int> toposort;
    while (!q.empty())
    {
        int node = q.front();
        q.pop();

        toposort.push_back(node);

        for (auto neigh : adj[node])
        {
            indegree[neigh] -= 1;
            if (indegree[neigh] == 0)
            {
                q.push(neigh);
            }
        }
    }

    ways[1] = 1;
    for (auto node : toposort)
    {
        if (ways[node] > 0)
        {
            for (auto neigh : adj[node])
            {
                ways[neigh] = (ways[neigh] + ways[node]) % MOD;
            }
        }
    }

    cout << ways[n] << endl;
    return 0;
}
