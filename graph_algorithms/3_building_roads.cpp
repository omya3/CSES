#include <vector>
#include <iostream>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

// Standard BFS to mark all cities in the same connected component
void bfs(int start_i, const vector<vector<int>> &grid, vector<bool> &visited)
{
    queue<int> q;
    q.push(start_i);
    visited[start_i] = true;

    while (!q.empty())
    {
        int curr_node = q.front();
        q.pop();

        for (auto neigh : grid[curr_node])
        {
            if (!visited[neigh])
            {
                visited[neigh] = true;
                q.push(neigh);
            }
        }
    }
}

int main()
{
    // Optimise standard I/O streams for execution speed
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int cities, roads;
    if (!(cin >> cities >> roads))
        return 0;

    vector<vector<int>> grid(cities + 1);

    for (int i = 0; i < roads; i++)
    {
        int c1, c2;
        cin >> c1 >> c2;

        grid[c1].push_back(c2);
        grid[c2].push_back(c1);
    }

    vector<bool> visited(cities + 1, false);
    vector<int> component_leaders; // To store one city from each component

    // Loop through ALL cities to find every disconnected component
    for (int i = 1; i <= cities; i++)
    {
        if (!visited[i])
        {
            component_leaders.push_back(i); // This city represents its component
            bfs(i, grid, visited);          // Mark everything connected to it
        }
    }

    // Number of new roads needed is always (total components - 1)
    cout << component_leaders.size() - 1 << "\n";

    // Connect the components in a single chain
    for (size_t i = 0; i < component_leaders.size() - 1; i++)
    {
        cout << component_leaders[i] << " " << component_leaders[i + 1] << "\n";
    }

    return 0;
}
