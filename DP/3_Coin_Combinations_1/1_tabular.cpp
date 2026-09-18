#include <iostream>
#include <vector> // FIXED: Added missing header

using namespace std;

int main()
{
    // Optimize fast standard I/O operations
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    if (!(cin >> n >> x))
        return 0;

    vector<int> coins(n);
    for (int i = 0; i < n; i++)
    {
        cin >> coins[i];
    }

    int MOD = 1e9 + 7;
    vector<int> dp(x + 1, 0);

    // FIXED: Base case set to 1.
    // This handles the "coins[j] == i" check automatically through dp[0]!
    dp[0] = 1;

    for (int i = 1; i <= x; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // FIXED: Combined both checks safely
            if (coins[j] <= i)
            {
                dp[i] = (dp[i] + dp[i - coins[j]]) % MOD;
            }
        }
    }

    cout << dp[x] << "\n"; // FIXED: Print out the response
    return 0;              // FIXED: Main must return 0
}
