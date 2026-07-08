#include <vector>
#include <iostream>
#include <string>
#include <queue> // FIX 1: Added missing queue header

using namespace std;

// FIX 2: Corrected parameter types to match main() containers exactly
void bfs(int start_i, int start_j, const vector<string> &grid, vector<vector<bool>> &visited)
{
    int n = grid.size();
    int m = grid[0].size();

    queue<pair<int, int>> q;
    q.push({start_i, start_j});
    visited[start_i][start_j] = true; // Mark the starting cell as visited immediately

    vector<int> n1 = {-1, 0, +1, 0};
    vector<int> n2 = {0, +1, 0, -1};

    while (!q.empty())
    {
        auto curr_node = q.front();
        q.pop();

        int curr_row = curr_node.first;
        int curr_col = curr_node.second;

        for (int k = 0; k < 4; k++)
        {
            // FIX 3: Look at the neighbors of curr_row/curr_col instead of the initial parameters i/j
            int neigh_row = curr_row + n1[k];
            int neigh_col = curr_col + n2[k];

            if (neigh_row >= 0 && neigh_row < n && neigh_col >= 0 && neigh_col < m)
            {
                // FIX 5: Use clear boolean checks for the visited matrix
                if (grid[neigh_row][neigh_col] == '.' && !visited[neigh_row][neigh_col])
                {
                    visited[neigh_row][neigh_col] = true;
                    q.push({neigh_row, neigh_col});
                }
            }
        }
    }
}

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

    // FIX 2 & 5: Changed to a clear boolean tracking matrix
    vector<vector<bool>> visited(n, vector<bool>(m, false));

    int count = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            // FIX 4: Run BFS on unvisited floors ('.') instead of walls ('#')
            if (grid[i][j] == '.' && !visited[i][j])
            {
                count += 1;
                bfs(i, j, grid, visited);
            }
        }
    }

    // FIX 6: Use cout to output the room count to the screen
    cout << count << "\n";
    return 0;
}
