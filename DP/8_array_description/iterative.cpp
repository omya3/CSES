#include <iostream>
#include <vector> // FIXED: Missing vector header

using namespace std;

int main()
{
    // Optimize standard I/O operations for performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m))
        return 0;

    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    int MOD = 1e9 + 7; // FIXED: Added the required modulo constant

    // creating dp matrix
    vector<vector<int>> dp(n, vector<int>(m + 1, 0));

    // Base Case for index 0
    if (arr[0] != 0)
    {
        dp[0][arr[0]] = 1;
    }
    else
    {
        for (int i = 1; i <= m; i++)
        {
            dp[0][i] = 1;
        }
    }

    // Transitions
    for (int i = 1; i < n; i++)
    {
        if (arr[i] != 0)
        {
            int val = arr[i];
            long long sum = dp[i - 1][val];

            // FIXED: Added defensive boundary checks
            if (val - 1 >= 1)
                sum = (sum + dp[i - 1][val - 1]) % MOD;
            if (val + 1 <= m)
                sum = (sum + dp[i - 1][val + 1]) % MOD;

            dp[i][val] = sum;
        }
        else
        {
            for (int j = 1; j <= m; j++)
            {
                long long sum = dp[i - 1][j];

                // FIXED: Added defensive boundary checks
                if (j - 1 >= 1)
                    sum = (sum + dp[i - 1][j - 1]) % MOD;
                if (j + 1 <= m)
                    sum = (sum + dp[i - 1][j + 1]) % MOD;

                dp[i][j] = sum;
            }
        }
    }

    // Aggregate the total valid full arrays
    int count = 0;
    for (int i = 1; i <= m; i++)
    {
        count = (count + dp[n - 1][i]) % MOD; // FIXED: Added modulo accumulation
    }

    cout << count << "\n"; // FIXED: Print the output correctly
    return 0;              // FIXED: Terminate cleanly
}
