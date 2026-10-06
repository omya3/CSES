#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

// Use a clear long long infinity constant to prevent underflow/overflow bugs
const long long INF = 1e18;
int node_cycle = -1;

bool bellmanford(int n, vector<long long> &dist, vector<tuple<int, int, int>> &edges, vector<int> &parent)
{
    // 1. Relax edges n-1 times
    for (int i = 0; i < n - 1; i++)
    {
        for (auto &[u, v, w] : edges)
        {
            if (dist[u] != INF && dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                parent[v] = u;
            }
        }
    }

    // 2. The nth relaxation step to catch the cycle
    for (auto &[u, v, w] : edges)
    {
        if (dist[u] != INF && dist[v] > dist[u] + w)
        {
            parent[v] = u;
            node_cycle = v; // This node is guaranteed to be affected by the cycle
            return true;
        }
    }
    return false;
}

int main()
{
    // Optimize standard I/O operations for speed
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m))
        return 0;

    vector<tuple<int, int, int>> edges;

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    vector<int> parent(n + 1, -1);

    // FIX 1 & 3: Use long long for distances, initialized to 0 to capture
    // negative cycles in disconnected components instantly.
    vector<long long> dist(n + 1, 0);

    // applying bellmanford
    if (bellmanford(n, dist, edges, parent))
    {
        cout << "YES\n";

        // Step 1: Back up n times to guarantee we land inside the cycle loop
        for (int i = 0; i < n; i++)
        {
            node_cycle = parent[node_cycle];
        }

        int curr = node_cycle;
        vector<int> path_cycle;

        // Step 2: Extract the cycle nodes backwards
        while (true)
        {
            path_cycle.push_back(curr);
            if (curr == node_cycle && path_cycle.size() > 1)
            {
                break;
            }
            curr = parent[curr];
        }

        // Step 3: Reverse the sequence to restore correct traversal order
        reverse(path_cycle.begin(), path_cycle.end());

        // Step 4: Print the final cycle path
        for (int node : path_cycle)
        {
            cout << node << " ";
        }
        cout << "\n";
    }
    else
    {
        cout << "NO\n";
    }

    return 0;
}
