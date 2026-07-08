#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

// Direction step adjustments
int n1[] = {-1, 0, +1, 0};
int n2[] = {0, +1, 0, -1};
char direction[] = {'U', 'R', 'D', 'L'};

int main()
{
    // High-speed stream buffers for competitive programming execution
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m))
        return 0;

    vector<string> grid(n);
    int start_r = -1, start_c = -1;
    int end_r = -1, end_c = -1;

    for (int i = 0; i < n; i++)
    {
        cin >> grid[i];
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == 'A')
            {
                start_r = i;
                start_c = j;
            }
            if (grid[i][j] == 'B')
            {
                end_r = i;
                end_c = j;
            }
        }
    }

    // Tracks visited states and the incoming direction taken to reach cell (i, j)
    vector<vector<char>> parent_dir(n, vector<char>(m, 0));
    vector<vector<bool>> visited(n, vector<bool>(m, false));

    queue<pair<int, int>> q;
    q.push({start_r, start_c});
    visited[start_r][start_c] = true;

    bool found = false;

    while (!q.empty())
    {
        auto [curr_row, curr_col] = q.front();
        q.pop();

        if (curr_row == end_r && curr_col == end_c)
        {
            found = true;
            break;
        }

        for (int k = 0; k < 4; k++)
        {
            int neigh_row = curr_row + n1[k];
            int neigh_col = curr_col + n2[k];

            if (neigh_row >= 0 && neigh_row < n && neigh_col >= 0 && neigh_col < m)
            {
                if (grid[neigh_row][neigh_col] != '#' && !visited[neigh_row][neigh_col])
                {
                    visited[neigh_row][neigh_col] = true;
                    parent_dir[neigh_row][neigh_col] = direction[k]; // Record the path direction move
                    q.push({neigh_row, neigh_col});
                }
            }
        }
    }

    if (found)
    {
        cout << "YES\n";

        // Backtrack path assembly from 'B' back to 'A'
        string path = "";
        int r = end_r;
        int c = end_c;

        while (r != start_r || c != start_c)
        {
            char move = parent_dir[r][c];
            path.push_back(move);

            // Move backward against the path direction vector orientations
            if (move == 'U')
                r++;
            else if (move == 'D')
                r--;
            else if (move == 'L')
                c++;
            else if (move == 'R')
                c--;
        }

        // Reverse the reconstructed string because we collected it backwards
        reverse(path.begin(), path.end());

        cout << path.length() << "\n";
        cout << path << "\n";
    }
    else
    {
        cout << "NO\n";
    }
    return 0;
}
