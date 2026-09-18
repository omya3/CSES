#include <iostream>
#include <vector> // FIXED: Added missing header

using namespace std;

int main()
{
    // Optimize fast standard I/O streams for execution performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    if (!(cin >> n >> x)) return 0;
    int MOD = 1e9 + 7;

    vector<int> coins(n);
    for (int i = 0; i < n; i++)
    {
        cin >> coins[i];
    }

    // Allocation bounds: We keep it as global/heap-allocated vector
    vector<vector<int>> dp(n, vector<int>(x + 1, 0));

    for (int ind = 0; ind < n; ind++)
    {
        dp[ind][0] = 1;
    }

    for (int target = 1; target < x + 1; target++)
    {
        if (target % coins[0] == 0)
            dp[0][target] = 1;
    }

    for (int ind = 1; ind < n; ind++)
    {
        for (int target = 1; target <= x; target++)
        {
            int not_take = dp[ind - 1][target];

            int take = 0;
            if (coins[ind] <= target)
            {
                take = dp[ind][target - coins[ind]];
            }

            // FIXED: Added modulo operation to keep values within bounds
            dp[ind][target] = (take + not_take) % MOD;
        }
    }
    cout << dp[n - 1][x] << "\n";
    return 0;
}
