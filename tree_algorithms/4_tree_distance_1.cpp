#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Generic DFS function to calculate distances from a specific starting source
void get_distances(int node, int parent, int current_dist, const vector<vector<int>> &adj, vector<int> &dist)
{
    dist[node] = current_dist; // Record zero-based distance for the current node

    for (int neigh : adj[node])
    {
        if (neigh == parent)
            continue; // Prevent infinite loop back to the parent node

        get_distances(neigh, node, current_dist + 1, adj, dist);
    }
}

int main()
{
    // Fast I/O optimization for competitive programming
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n))
        return 0;

    // Build the 1-indexed adjacency list
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // --- DFS 1: Start at an arbitrary node (Node 1) to find Endpoint A ---
    vector<int> dist_from_1(n + 1, 0);
    get_distances(1, 0, 0, adj, dist_from_1);

    int node_A = 1;
    for (int i = 1; i <= n; i++)
    {
        if (dist_from_1[i] > dist_from_1[node_A])
        {
            node_A = i; // node_A is now the furthest leaf from Node 1
        }
    }

    // --- DFS 2: Start at Endpoint A to find Endpoint B and populate distA ---
    vector<int> distA(n + 1, 0);
    get_distances(node_A, 0, 0, adj, distA);

    int node_B = 1;
    for (int i = 1; i <= n; i++)
    {
        if (distA[i] > distA[node_B])
        {
            node_B = i; // node_B is the furthest leaf from A (the opposite side of the diameter)
        }
    }

    // --- DFS 3: Start at Endpoint B to populate distB ---
    vector<int> distB(n + 1, 0);
    get_distances(node_B, 0, 0, adj, distB);

    // --- Final Output Pass ---
    // The maximum distance from any node is its distance to either node_A or node_B
    for (int i = 1; i <= n; i++)
    {
        cout << max(distA[i], distB[i]) << (i == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}
