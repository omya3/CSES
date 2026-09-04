#include <iostream>
#include <vector>

using namespace std;

// Depth-First Search to find the maximum matching greedily from the bottom up
void dfs(int node, int parent, const vector<vector<int>> &adj, vector<int> &matched, int &count)
{
    // Step 1: Traverse all children first (Post-order)
    for (int neigh : adj[node])
    {
        if (neigh == parent)
            continue; // Prevent going backward to the parent

        dfs(neigh, node, adj, matched, count);
    }

    // Step 2: After all children have finished, try to match this node with its parent
    if (parent != 0 && !matched[node] && !matched[parent])
    {
        count += 1;
        matched[node] = 1;
        matched[parent] = 1;
    }
}

int main()
{
    // Fast I/O for performance in competitive programming
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

    // Tracking array to check if a node has been picked in a pair
    vector<int> matched(n + 1, 0);
    int count = 0;

    // Start DFS traversal from Node 1 with a dummy parent (0)
    dfs(1, 0, adj, matched, count);

    // Print the final maximum matching answer
    cout << count << "\n";

    return 0;
}
