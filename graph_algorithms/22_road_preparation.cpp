#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent a road/edge
struct Edge
{
    int u, v;
    long long cost;

    // Custom comparator to sort edges by their cost in ascending order
    bool operator<(const Edge &other) const
    {
        return cost < other.cost;
    }
};

// Disjoint Set Union (DSU) Structure for Cycle Detection
struct DSU
{
    vector<int> parent;
    vector<int> rank;

    DSU(int n)
    {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        for (int i = 1; i <= n; i++)
        {
            parent[i] = i;
        }
    }

    // Find operation with path compression
    int find_set(int v)
    {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }

    // Union operation by rank
    bool union_sets(int a, int b)
    {
        a = find_set(a);
        b = find_set(b);
        if (a != b)
        {
            if (rank[a] < rank[b])
                swap(a, b);
            parent[b] = a;
            if (rank[a] == rank[b])
                rank[a]++;
            return true; // Union successful, no cycle created
        }
        return false; // Nodes are already connected, adding this edge would create a cycle
    }
};

int main()
{
    // Fast I/O optimization
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m))
        return 0;

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++)
    {
        cin >> edges[i].u >> edges[i].v >> edges[i].cost;
    }

    sort(edges.begin(), edges.end());

    // FIXED: Must use 'long long' to handle summed values exceeding 2*10^9
    long long cost = 0;
    int num_edges = 0;

    DSU ds(n);

    // Using 'size_t' to match signedness and prevent compiler warnings
    for (size_t i = 0; i < edges.size(); i++)
    {
        if (ds.union_sets(edges[i].u, edges[i].v))
        {
            cost += edges[i].cost;
            num_edges += 1;
        }

        if (num_edges == n - 1)
            break;
    }

    if (num_edges == n - 1)
    {
        cout << cost << "\n";
    }
    else
    {
        cout << "IMPOSSIBLE\n";
    }

    return 0;
}
