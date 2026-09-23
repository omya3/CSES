#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 2^19 = 524,288 which safely handles N = 200,000 nodes
int LOG = 20;

// DFS function to determine the depth of every node AND identify their immediate parents
void find_depths(int parent, int node, int d, const vector<vector<int>> &adj, vector<int> &depth, vector<vector<int>> &up)
{
    depth[node] = d;
    up[node][0] = parent; // Set the immediate parent (2^0 level) during traversal

    for (int child : adj[node])
    {
        if (child != parent)
        {
            find_depths(node, child, d + 1, adj, depth, up);
        }
    }
}

// Function to calculate the Lowest Common Ancestor (LCA) using Binary Lifting
int find_lca(int a, int b, vector<int> &depth, vector<vector<int>> &up)
{
    // STEP 1: Always make sure node 'a' is the deeper node
    if (depth[a] < depth[b])
    {
        swap(a, b);
    }

    // STEP 2: Lift node 'a' up so it is at the exact same depth level as node 'b'
    int diff_depth = depth[a] - depth[b];

    for (int bit = 0; bit < LOG; bit++)
    {
        if ((diff_depth >> bit) & 1) // If the bit is set, make the jump
            a = up[a][bit];
    }

    // STEP 3: If 'a' landed directly on 'b', then 'b' was an ancestor of 'a' all along!
    if (a == b)
    {
        return a;
    }

    // STEP 4: TWIN-LIFTING LOOP
    for (int bit = LOG - 1; bit >= 0; bit--)
    {
        // Jump ONLY if they land on different nodes (meaning we haven't reached or passed the LCA)
        if (up[a][bit] != up[b][bit])
        {
            a = up[a][bit];
            b = up[b][bit];
        }
    }

    // Return the immediate parent of their final standing position
    return up[a][0];
}

int main()
{
    // Fast I/O optimization for performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q))
        return 0;

    // Build standard tree structures using an adjacency list
    vector<vector<int>> adj(n + 1);
    vector<vector<int>> up(n + 1, vector<int>(LOG, -1));

    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v); // Trees are undirected graphs
        adj[v].push_back(u);
    }

    // Setup node depths array tracker
    vector<int> depth(n + 1, 0);

    // Pass root node 1 with a dummy parent 0 to populate depth and immediate (2^0) ancestors
    find_depths(0, 1, 0, adj, depth, up);

    // Precompute the remaining ancestors using DP / Binary Lifting
    for (int level = 1; level < LOG; level++)
    {
        for (int emp = 1; emp <= n; emp++)
        {
            int intermed_boss = up[emp][level - 1];
            if (intermed_boss != -1)
            {
                up[emp][level] = up[intermed_boss][level - 1];
            }
        }
    }

    // Execute distance queries using the mathematically adjusted depth formula
    for (int i = 0; i < q; i++)
    {
        int a, b;
        cin >> a >> b;

        int lca_node = find_lca(a, b, depth, up);

        // Apply your correct formula: depth[a] + depth[b] - 2 * depth[LCA]
        int distance = depth[a] + depth[b] - 2 * depth[lca_node];

        cout << distance << "\n";
    }

    return 0;
}
