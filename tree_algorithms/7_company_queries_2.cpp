#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 2^19 = 524,288 which safely handles N = 200,000 nodes
int LOG = 20;

// DFS function to determine the distance (depth) of every single node from the root (1)
void find_depths(int parent, int node, int d, const vector<vector<int>> &adj, vector<int> &depth)
{
    depth[node] = d;
    for (int child : adj[node])
    {
        if (child != parent)
        {
            find_depths(node, child, d + 1, adj, depth);
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

    /**
     * STEP 4: TRACE EXAMPLE FOR THE TWIN-LIFTING LOOP
     *
     * Imagine the remaining distance from nodes 'a' and 'b' to their true LCA is 13 steps.
     * In binary, 13 is represented as 1101 (8 + 4 + 0 + 1).
     *
     * The loop starts searching from the largest possible jump size (bit = 19) down to 0:
     *
     * --------------------------------------------------------------------------------------
     * 🌟 Bit = 3 (Jump size = 2^3 = 8 steps):
     *    - Distance to LCA is 13. A jump of 8 steps keeps 'a' and 'b' underneath the LCA.
     *    - Because they are underneath the LCA, their ancestors will be DIFFERENT.
     *    - condition (up[a][3] != up[b][3]) evaluates to TRUE.
     *    - ACTION: SAFE JUMP TAKEN! Both nodes move up 8 steps.
     *    - Remaining distance left to the LCA: 13 - 8 = 5 steps.
     *
     * --------------------------------------------------------------------------------------
     * 🌟 Bit = 2 (Jump size = 2^2 = 4 steps):
     *    - Remaining distance to LCA is 5. A jump of 4 steps keeps them underneath the LCA.
     *    - Because they are still underneath the LCA, their ancestors will be DIFFERENT.
     *    - condition (up[a][2] != up[b][2]) evaluates to TRUE.
     *    - ACTION: SAFE JUMP TAKEN! Both nodes move up another 4 steps.
     *    - Remaining distance left to the LCA: 5 - 4 = 1 step.
     *
     * --------------------------------------------------------------------------------------
     * 🌟 Bit = 1 (Jump size = 2^1 = 2 steps):
     *    - Remaining distance to LCA is 1. A jump of 2 steps will OVERSHOOT past the LCA.
     *    - Because they overshoot, they will land on the SAME common ancestor higher up.
     *    - condition (up[a][1] != up[b][1]) evaluates to FALSE (they match!).
     *    - ACTION: DANGER ZONE! DO NOT JUMP. Nodes stay right where they are.
     *    - Remaining distance left to the LCA: Still 1 step.
     *
     * --------------------------------------------------------------------------------------
     * 🌟 Bit = 0 (Jump size = 2^0 = 1 step):
     *    - Remaining distance to LCA is exactly 1. A jump of 1 step lands exactly ON the LCA.
     *    - Because they land on the LCA, they will match.
     *    - condition (up[a][0] != up[b][0]) evaluates to FALSE (they match!).
     *    - ACTION: DO NOT JUMP. Nodes stay right where they are.
     *
     * --------------------------------------------------------------------------------------
     * 🏁 FINAL POSITION SUMMARY:
     *    Because the loop refused to take any jump that caused them to match, they were unable
     *    to make that last 1-step jump. They are left standing EXACTLY 1 step below the LCA!
     */
    for (int bit = LOG - 1; bit >= 0; bit--)
    {
        // Jump ONLY if they land on different nodes (meaning we haven't reached or passed the LCA)
        if (up[a][bit] != up[b][bit])
        {
            a = up[a][bit];
            b = up[b][bit];
        }
    }

    // Since they are standing exactly one step right below the LCA,
    // their immediate parent (2^0 boss) is the lowest common ancestor!
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

    // Build the tree structures
    vector<vector<int>> adj(n + 1);
    vector<vector<int>> up(n + 1, vector<int>(LOG, -1));

    for (int i = 2; i < n + 1; i++)
    {
        int p;
        cin >> p;
        up[i][0] = p;        // Store the immediate parent (2^0 boss)
        adj[p].push_back(i); // Undirected tree connection
        adj[i].push_back(p);
    }

    // Precompute node depths starting from root 1 at depth 0
    vector<int> depth(n + 1, 0);
    find_depths(0, 1, 0, adj, depth);

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

    // Execute queries
    for (int i = 0; i < q; i++)
    {
        int a, b;
        cin >> a >> b;

        // FIXED: Corrected parameter order and matrix name from 'boss' to 'up'
        cout << find_lca(a, b, depth, up) << "\n";
    }

    return 0;
}
