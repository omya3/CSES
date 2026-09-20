/**
 * PROBLEM: Tree Distances II (CSES)
 *
 * 💡 CORE LOGIC BREAKDOWN (Rerooting Technique):
 * 1. A naive O(N^2) solution running a DFS/BFS from every node will Time Out (TLE) for N = 200,000.
 *    Instead, we use a Two-Pass Tree DP (Rerooting Technique) running in linear O(N) time.
 *
 * 2. PASS 1 (dfs):
 *    - Pick node 1 arbitrarily as the root.
 *    - Compute 'sub_tree[i]': The total number of nodes in node i's subtree (including itself).
 *    - Compute 'dist_A[i]': The individual absolute distance from root node 1 to node i.
 *    - Sum all elements in 'dist_A' to seed 'dist_sum[1]' (the initial known total distance sum).
 *
 * 3. PASS 2 (cal_dist_sum):
 *    - Traverse down from a parent 'P' to a child 'C'.
 *    - Moving from P to C brings us 1 step closer to all nodes inside C's subtree world ('sub_tree[C]' nodes).
 *    - It takes us 1 step further away from all nodes outside C's subtree world ('N - sub_tree[C]' nodes).
 *    - The net balance shifting equation simplifies to:
 *      dist_sum[C] = dist_sum[P] + N - 2 * sub_tree[C]
 *    - This updates every node's total distance sum in O(1) constant time as we travel.
 */

#include <iostream>
#include <vector>

using namespace std;

// Pass 1: Computes subtree sizes bottom-up and tracks absolute node depths from root node 1
int dfs(int parent, int node, vector<vector<int>> &adj, vector<long long> &sub_tree, vector<long long> &dist_A, int dis)
{
    // Base Case: If it's a leaf node (only connected to its parent)
    if (adj[node].size() == 1 && adj[node][0] == parent)
    {
        sub_tree[node] = 1; // A leaf's subtree size is always just 1 (itself)
        return 1;
    }

    int num_subtrees = 0; // Tracks the accumulated sizes of all children subtrees
    for (auto &it : adj[node])
    {
        if (it == parent)
            continue; // Skip backtracking up to the parent node

        dist_A[it] = dis; // Store the absolute depth of this child from root node 1

        if (sub_tree[it] == -1)
        {
            // Recursively evaluate the child's subtree and update the tracking table
            sub_tree[it] = dfs(node, it, adj, sub_tree, dist_A, dis + 1);
        }
        num_subtrees += sub_tree[it]; // Accumulate child's subtree size
    }

    sub_tree[node] = 1 + num_subtrees; // Current node size = 1 (itself) + total child subtree nodes
    return sub_tree[node];
}

// Pass 2: Reroots the tree top-down, propagating finalized total distance sums using the DP shifting formula
void cal_dist_sum(int parent, int node, vector<vector<int>> &adj, vector<long long> &dist_sum, vector<long long> &sub_tree)
{
    if (parent != 0)
    {
        // Shifting equation: dist_sum[child] = dist_sum[parent] + Total_Nodes - 2 * child_subtree_size
        // Note: adj.size() - 1 evaluates exactly to N because adj is 1-indexed (size is N + 1)
        dist_sum[node] = dist_sum[parent] + adj.size() - 1 - 2 * sub_tree[node];
    }

    for (auto &it : adj[node])
    {
        if (it != parent)
        {
            // Propagate the shift down to all neighboring branches recursively
            cal_dist_sum(node, it, adj, dist_sum, sub_tree);
        }
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

    // CRITICAL CORNER CASE: A tree containing only 1 single node has a distance sum of 0
    if (n == 1)
    {
        cout << 0 << "\n";
        return 0;
    }

    // Build the 1-indexed adjacency list
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b); // Add bidirectional edge (Trees are undirected graphs)
        adj[b].push_back(a);
    }

    // Allocate memory trackers initialized with base states
    vector<long long> sub_tree(n + 1, -1);
    vector<long long> dist_sum(n + 1, -1);
    vector<long long> dist_A(n + 1, 0);

    // Run Pass 1: Start at node 1 with a dummy parent 0 and initial step depth 1
    long long sub_tree_1 = dfs(0, 1, adj, sub_tree, dist_A, 1);

    // Sum up individual node depths to calculate the absolute total distance sum for root node 1
    long long dist_sum_A = 0;
    for (int i = 1; i < n + 1; i++)
    {
        dist_sum_A += dist_A[i];
    }

    // Seed the root node entry with its computed absolute total sum
    dist_sum[1] = dist_sum_A;

    // Run Pass 2: Distribute distance sums using the Rerooting DP equation starting from root 1
    cal_dist_sum(0, 1, adj, dist_sum, sub_tree);

    // Print out the finalized sequence of answer distances separated by spaces
    for (int i = 1; i <= n; i++)
    {
        cout << dist_sum[i] << (i == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}
