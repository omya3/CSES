#include <iostream>
#include <vector> // FIXED: Added missing header

using namespace std;

int main()
{
    // Optimize fast standard input/output operations
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    if (!(cin >> n >> x))
        return 0;
    int MOD = 1e9 + 7;

    vector<int> coins(n);
    for (int i = 0; i < n; i++)
    {
        cin >> coins[i];
    }

    vector<int> prev(x + 1, 0);
    vector<int> curr(x + 1, 0);

    prev[0] = 1;
    for (int target = 1; target < x + 1; target++)
    {
        if (target % coins[0] == 0)
            prev[target] = 1;
    }

    // FIXED: If there is only one coin, output from prev instantly
    if (n == 1)
    {
        cout << prev[x] << "\n";
        return 0;
    }

    for (int ind = 1; ind < n; ind++)
    {
        curr[0] = 1;
        for (int target = 1; target <= x; target++)
        {
            int not_take = prev[target];

            int take = 0;
            if (coins[ind] <= target)
            {
                take = curr[target - coins[ind]];
            }

            curr[target] = (take + not_take) % MOD;
        }
        prev = curr;
    }
    cout << curr[x] << "\n";
    return 0;
}
