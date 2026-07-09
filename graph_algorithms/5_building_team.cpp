#include <vector>
#include <iostream>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

// Standard BFS to find the shortest path across the computers network
int bfs(int start, const vector<vector<int>> &grid, vector<int> &color)
{
    queue<int> q;
    q.push(start);
    color[start] = 1;

    while (!q.empty())
    {
        int curr_node = q.front();
        int curr_color = color[curr_node];
        q.pop();

        for (auto neigh : grid[curr_node])
        {
            if (color[neigh] == 0)
            {
                color[neigh] = 3 - curr_color;
                q.push(neigh); // FIX: Make sure to increment distance for the neighbor!
            }
            else if (color[curr_node] == color[neigh])
            {
                return false;
            }
        }
    }
    return true; // FIX: Return -1 explicitly if the target node is unreachable
}

int main()
{
    // Optimise standard I/O streams for execution speed
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n_people, friendships;
    if (!(cin >> n_people >> friendships))
        return 0;

    vector<vector<int>> grid(n_people + 1);

    for (int i = 0; i < friendships; i++)
    {
        int p1, p2;
        cin >> p1 >> p2;

        grid[p1].push_back(p2);
        grid[p2].push_back(p1);
    }

    vector<bool> visited(n_people + 1, false);
    vector<int> color(n_people + 1, 0);

    // Loop through ALL cities to find every disconnected component
    for (int i = 1; i <= n_people; i++)
    {
        if (color[i] == 0)
        {
            if (!bfs(i, grid, color))
            {
                cout << "IMPOSSIBLE\n";
                return 0; // Terminate execution immediately on tracking any failure
            }
        }
    }

    for (int i = 1; i <= n_people; i++)
    {
        cout << color[i] << (i == n_people ? "" : " ");
    }
    cout << "\n";

    return 0;
}
