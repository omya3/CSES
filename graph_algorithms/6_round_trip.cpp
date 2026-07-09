#include <vector>
#include <iostream>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

int cycle_start = -1;
int cycle_end = -1;

// Standard DFS to find cycles using 3-state tracking
bool dfs(int current, int from, const vector<vector<int>> &grid, vector<int> &visited, vector<int> &parents)
{
    visited[current] = 1; // 1 = Currently visiting (active in recursion stack)

    for (auto neigh : grid[current])
    {
        if (neigh == from)
            continue;

        if (visited[neigh] == 0)
        {
            parents[neigh] = current;
            if (dfs(neigh, current, grid, visited, parents))
                return true;
        }
        else if (visited[neigh] == 1) // Cycle detected!
        {
            cycle_end = current;
            cycle_start = neigh;
            return true;
        }
    }

    visited[current] = 2; // FIX 3: 2 = Fully processed, safe to remove from stack
    return false;
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

    vector<int> parents(cities + 1, -1);
    vector<int> visited(cities + 1, 0);

    for (int i = 1; i <= cities; i++)
    {
        if (visited[i] == 0)
        {
            if (dfs(i, -1, grid, visited, parents))
            {
                // FIX 1: Keep path and printing variables INSIDE this conditional scope
                vector<int> path;
                int curr = cycle_end;

                // FIX 2: Correct backtracking direction (End -> Start)
                path.push_back(cycle_start);
                while (curr != cycle_start)
                {
                    path.push_back(curr);
                    curr = parents[curr]; // Step backward through parent relations
                }
                path.push_back(cycle_start); // Close the circular path loop

                // Flip back to correct chronological order
                reverse(path.begin(), path.end());

                cout << path.size() << "\n";
                for (size_t j = 0; j < path.size(); j++)
                {
                    cout << path[j] << (j + 1 == path.size() ? "" : " ");
                }
                cout << "\n";
                return 0;
            }
        }
    }

    cout << "IMPOSSIBLE\n";
    return 0;
}
