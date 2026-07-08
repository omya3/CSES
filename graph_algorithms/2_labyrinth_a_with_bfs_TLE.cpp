#include <vector>
#include <iostream>
#include <string>
#include <queue>
#include <tuple>

using namespace std;

string bfs(int start_i, int start_j, const vector<string> &grid, vector<vector<bool>> &visited)
{
    int n = grid.size();
    int m = grid[0].size();

    queue<tuple<int, int, string>> q;
    q.push({start_i, start_j, ""});
    visited[start_i][start_j] = true;

    vector<int> n1 = {-1, 0, +1, 0};
    vector<int> n2 = {0, +1, 0, -1};
    vector<char> direction = {'U', 'R', 'D', 'L'};

    while (!q.empty())
    {
        auto curr_node = q.front();
        q.pop();

        int curr_row = get<0>(curr_node);
        int curr_col = get<1>(curr_node);
        string curr_path = get<2>(curr_node);

        if (grid[curr_row][curr_col] == 'B')
            return curr_path;

        for (int k = 0; k < 4; k++)
        {
            int neigh_row = curr_row + n1[k];
            int neigh_col = curr_col + n2[k];
            char neigh_dir = direction[k];

            if (neigh_row >= 0 && neigh_row < n && neigh_col >= 0 && neigh_col < m)
            {
                // FIX 2: Allow stepping on either floor '.' or the destination 'B'
                if ((grid[neigh_row][neigh_col] == '.' || grid[neigh_row][neigh_col] == 'B') && !visited[neigh_row][neigh_col])
                {
                    visited[neigh_row][neigh_col] = true;
                    // FIX 1: Use '+' instead of '+=' to avoid corrupting paths for other directions
                    q.push({neigh_row, neigh_col, curr_path + neigh_dir});
                }
            }
        }
    }
    return "";
}

int main()
{
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m))
        return 0;

    vector<string> grid(n);
    int start_r = -1, start_c = -1;

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
        }
    }

    vector<vector<bool>> visited(n, vector<bool>(m, false));

    // Run BFS starting directly from the found 'A' position
    string path = bfs(start_r, start_c, grid, visited);

    if (!path.empty())
    {
        cout << "YES\n";
        cout << path.length() << "\n";
        cout << path << "\n";
    }
    else
    {
        // An empty path string can mean 'A' and 'B' are next to each other,
        // so ensure we check if the start tile itself was 'B' (not possible per rules, but safe)
        if (grid[start_r][start_c] == 'B')
        {
            cout << "YES\n0\n\n";
        }
        else
        {
            cout << "NO\n";
        }
    }
    return 0;
}
