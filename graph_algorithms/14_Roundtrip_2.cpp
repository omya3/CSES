#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int node_with_cycle = -1;
int start_node = -1;

bool dfs(int node, vector<vector<int>> &adj, vector<int> &visited, vector<int> &parent)
{
    visited[node] = 1;

    for (auto &neigh : adj[node])
    {
        if (visited[neigh] == 0)
        {
            parent[neigh] = node;
            if (dfs(neigh, adj, visited, parent))
            {

                return true;
            }
        }

        else if (visited[neigh] == 1)
        {
            node_with_cycle = neigh;
            start_node = node;
            return true;
        }
    }

    visited[node] = 2;
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < m; i++)
    {
        int u;
        int v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    vector<int> visited(n + 1, 0);
    vector<int> parent(n + 1, 0);

    for (int i = 1; i < n + 1; i++)
    {
        if (visited[i] == 0)
        {
            if (dfs(i, adj, visited, parent))
                break;
        }
    }

    if (node_with_cycle == -1)
    {
        cout << "IMPOSSIBLE" << "\n";
    }
    else
    {

        vector<int> nodes_on_path;

        // Start from the ending node of the cycle and walk backwards using parents
        int curr = start_node;
        nodes_on_path.push_back(node_with_cycle); // The closing duplicate node

        while (curr != node_with_cycle)
        {
            nodes_on_path.push_back(curr);
            curr = parent[curr];
        }
        nodes_on_path.push_back(node_with_cycle); // The starting node of the cycle

        // Since we collected them backwards, reverse to read chronologically
        reverse(nodes_on_path.begin(), nodes_on_path.end());

        // Print the answer format requested by CSES
        cout << nodes_on_path.size() << "\n";
        for (int i = 0; i < nodes_on_path.size(); i++)
        {
            cout << nodes_on_path[i] << (i + 1 == nodes_on_path.size() ? "" : " ");
        }
        cout << "\n";
    }
    return 0;
}