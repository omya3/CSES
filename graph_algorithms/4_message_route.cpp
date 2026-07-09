#include <vector>
#include <iostream>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

// Standard BFS to find the shortest path across the computers network
int bfs(int start_i, int end, const vector<vector<int>> &grid, vector<bool> &visited, vector<int> &parents)
{
    queue<pair<int, int>> q;
    q.push({start_i, 0});
    visited[start_i] = true;

    while (!q.empty())
    {
        int curr_node = q.front().first;
        int dist = q.front().second;
        q.pop();

        if (curr_node == end)
            return dist;

        for (auto neigh : grid[curr_node])
        {
            if (!visited[neigh])
            {
                visited[neigh] = true;
                parents[neigh] = curr_node;
                q.push({neigh, dist + 1}); // FIX: Make sure to increment distance for the neighbor!
            }
        }
    }
    return -1; // FIX: Return -1 explicitly if the target node is unreachable
}

int main()
{
    // Optimise standard I/O streams for execution speed
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n_comp, conn;
    if (!(cin >> n_comp >> conn))
        return 0;

    vector<vector<int>> grid(n_comp + 1);

    for (int i = 0; i < conn; i++)
    {
        int c1, c2;
        cin >> c1 >> c2;

        grid[c1].push_back(c2);
        grid[c2].push_back(c1);
    }

    vector<bool> visited(n_comp + 1, false);
    vector<int> parents(n_comp + 1, -1);

    int k = bfs(1, n_comp, grid, visited, parents);

    // FIX: Verify path existence based on the explicit -1 return flag
    if (k == -1)
    {
        cout << "IMPOSSIBLE\n";
    }
    else
    {
        // FIX: Total nodes on the path is always the number of edges (k) + 1
        cout << k + 1 << "\n";

        vector<int> path;
        int curr_node = n_comp;

        // Trace path backwards from destination to start node
        while (curr_node != -1)
        {
            path.push_back(curr_node);
            curr_node = parents[curr_node]; // Safe, unique traversal link
        }

        reverse(path.begin(), path.end());

        for (size_t i = 0; i < path.size(); i++)
        {
            cout << path[i] << (i + 1 == path.size() ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}
