#include <iostream>
#include <vector> // FIXED: Included required vector header

using namespace std;

const int MOD = 1e9 + 7;

// Added 'n' explicitly to make the destination base case transparent and readable
int count_ways(int node, int n, vector<vector<int>> &adj, vector<long long> &ways)
{
    // Base Case: Successfully reached the destination city
    if (node == n)
        return 1;

    // Return the cached value if we have already visited this node
    if (ways[node] != -1)
        return ways[node];

    long long total_ways = 0;
    for (auto it : adj[node])
    {
        total_ways = (total_ways + count_ways(it, n, adj, ways)) % MOD;
    }

    return ways[node] = total_ways;
}

int main()
{
    // Fast I/O optimization for performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m))
        return 0;

    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    vector<long long> ways(n + 1, -1);

    // FIXED: Print the returned result to standard output instead of returning it as an exit status
    cout << count_ways(1, n, adj, ways) << "\n";

    return 0;
}
