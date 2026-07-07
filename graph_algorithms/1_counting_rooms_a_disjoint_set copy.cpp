#include <vector>
#include <iostream>
#include <string> // FIX 1: Added missing string header

using namespace std;

class DisjointSet
{
    vector<int> rank, parent, size;

public:
    // Constructor to initialize the data structure for 'n' elements
    DisjointSet(int n)
    {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        size.resize(n + 1, 1);
        for (int i = 0; i <= n; i++)
        {
            parent[i] = i;
        }
    }

    // Find ultimate parent with path compression optimization
    int findUPar(int node)
    {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]);
    }

    // Union operation based on the Rank of trees
    void unionByRank(int u, int v)
    {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v)
            return;

        if (rank[ulp_u] < rank[ulp_v])
        {
            parent[ulp_u] = ulp_v;
        }
        else if (rank[ulp_v] < rank[ulp_u])
        {
            parent[ulp_v] = ulp_u;
        }
        else
        {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }

    // Union operation based on the Size of components
    void unionBySize(int u, int v)
    {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v)
            return;

        if (size[ulp_u] < size[ulp_v])
        {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
        else
        {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

int main()
{
    // Optimise standard I/O streams for execution speed
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m))
        return 0;

    vector<string> grid(n);
    for (int i = 0; i < n; i++)
    {
        cin >> grid[i];
    }

    // FIX 2: Declared the DisjointSet object with grid size
    DisjointSet ds(n * m);

    // FIX 3: Declared direction delta arrays for tracking 4-way neighbors
    vector<int> n1 = {-1, 0, +1, 0};
    vector<int> n2 = {0, +1, 0, -1};

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == '#')
                continue;

            int curr_node = i * m + j;

            // exploring neighbors
            for (int k = 0; k < 4; k++)
            {
                int neigh_row = i + n1[k];
                int neigh_col = j + n2[k];
                if (neigh_row >= 0 and neigh_row < n and neigh_col >= 0 and neigh_col < m)
                {
                    if (grid[neigh_row][neigh_col] == '.')
                    {
                        int neigh_node = neigh_row * m + neigh_col;
                        ds.unionBySize(curr_node, neigh_node);
                    }
                }
            }
        }
    }

    // Count how many independent floor components exist
    int components = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            // Only count floor cells that are the ultimate parent of their component
            if (grid[i][j] == '.')
            {
                int node_id = i * m + j;
                if (ds.findUPar(node_id) == node_id)
                {
                    components++;
                }
            }
        }
    }

    cout << components << "\n";
    return 0;
}
