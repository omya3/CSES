#include <iostream>
#include <vector> // Required for vector allocation in CSES
#include <algorithm>

using namespace std;

int min_cut(int l, int b, vector<vector<int>> &dp)
{
    if (l == b)
        return 0;

    if (l > b)
    {
        return min_cut(b, l, dp);
    }

    if (dp[l][b] != -1)
        return dp[l][b];

    int min_cost = 1e9;

    // cutting through length
    for (int i = 1; i < l; i++)
    {
        min_cost = min({min_cost,
                        1 + min_cut(i, b, dp) + min_cut(l - i, b, dp)});
    }

    // cutting through breadth
    for (int i = 1; i < b; i++)
    {
        min_cost = min({min_cost,
                        1 + min_cut(l, i, dp) + min_cut(l, b - i, dp)});
    }

    return dp[l][b] = min_cost;
}

int main()
{
    // Optimize standard I/O operations for competitive programming limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int a, b;
    if (cin >> a >> b)
    {
        int max_dim = max(a, b);
        vector<vector<int>> dp(max_dim + 1, vector<int>(max_dim + 1, -1));

        cout << min_cut(a, b, dp) << "\n";
    }
    return 0;
}
