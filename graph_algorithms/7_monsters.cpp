#include <vector>
#include <iostream>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

int n1[] = {-1, 0, +1, 0};
int n2[] = {0, +1, 0, -1};
char direction[] = {'U', 'R', 'D', 'L'};

int main()
{
    // Optimise standard I/O streams for execution speed
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int rows, cols;
    if (!(cin >> rows >> cols))
        return 0;

    vector<string> grid(rows);
    vector<vector<int>> time_matrix(rows, vector<int>(cols, 1e9));

    for (int i = 0; i < rows; i++)
    {
        cin >> grid[i];
    }

    int a_row = -1;
    int a_col = -1;
    queue<tuple<int, int, int>> q;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (grid[i][j] == 'M')
            {
                time_matrix[i][j] = 0;
                q.push({i, j, 0});
            }
            if (grid[i][j] == 'A')
            {
                a_row = i;
                a_col = j;
            }
        }
    }

    if (a_row == -1 and a_col == -1)
    {
        cout << "NO" << "\n";
    }

    while (!q.empty())
    {

        auto [r, c, t] = q.front();
        q.pop();

        for (int k = 0; k < 4; k++)
        {
            int neigh_row = r + n1[k];
            int neigh_col = c + n2[k];

            if (neigh_row >= 0 and neigh_row < rows and neigh_col >= 0 and neigh_col < cols)
            {
                if (grid[neigh_row][neigh_col] != '#' and time_matrix[neigh_row][neigh_col] == 1e9)
                {
                    time_matrix[neigh_row][neigh_col] = t + 1;
                    q.push({neigh_row, neigh_col, t + 1});
                }
            }
        }
    }

    // --- STEP 2: Player Escape Route BFS ---
    // Instead of DFS, we use BFS to find the absolute shortest path safely
    queue<tuple<int, int, int>> pq;
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<vector<char>> parent_dir(rows, vector<char>(cols, 0)); // To retrace steps

    pq.push({a_row, a_col, 0});
    visited[a_row][a_col] = true;

    int exit_row = -1, exit_col = -1;

    while (!pq.empty())
    {
        auto [r, c, t] = pq.front();
        pq.pop();

        // Immediate Win Condition Check: Am I on a boundary square?
        if (r == 0 || r == rows - 1 || c == 0 || c == cols - 1)
        {
            exit_row = r;
            exit_col = c;
            break;
        }

        for (int k = 0; k < 4; k++)
        {
            int neigh_row = r + n1[k];
            int neigh_col = c + n2[k];

            if (neigh_row >= 0 && neigh_row < rows && neigh_col >= 0 && neigh_col < cols)
            {
                // FIX 1: You must reach the tile STRICTLY BEFORE (t + 1 < time_matrix) the monster
                if (grid[neigh_row][neigh_col] != '#' && !visited[neigh_row][neigh_col] && (t + 1 < time_matrix[neigh_row][neigh_col]))
                {
                    visited[neigh_row][neigh_col] = true;
                    parent_dir[neigh_row][neigh_col] = direction[k]; // Log movement key
                    pq.push({neigh_row, neigh_col, t + 1});
                }
            }
        }
    }

    // --- STEP 3: Reconstruct and Print Path ---
    if (exit_row != -1)
    {
        cout << "YES\n";
        string path = "";
        int r = exit_row;
        int c = exit_col;

        while (r != a_row || c != a_col)
        {
            char move = parent_dir[r][c];
            path.push_back(move);
            if (move == 'U')
                r++;
            else if (move == 'D')
                r--;
            else if (move == 'L')
                c++;
            else if (move == 'R')
                c--;
        }

        reverse(path.begin(), path.end());
        cout << path.length() << "\n"
             << path << "\n";
    }
    else
    {
        cout << "NO\n";
    }

    return 0;
}
