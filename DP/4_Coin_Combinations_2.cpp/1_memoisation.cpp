#include <iostream>
using namespace std;

int find_ways(int ind, int target, vector<int> coins, vector<vector<int>> &dp)
{
    if (ind < 0)
        return 0;

    if (target == 0)
        return 1;

    if (dp[ind][target] != -1)
        return dp[ind][target];

    int not_take = find_ways(ind - 1, target, coins, dp);

    int take = 0;
    if (coins[ind] <= target)
    {
        take = find_ways(ind, target - coins[ind], coins, dp);
    }

    return dp[ind][target] = take + not_take;
}

int main()
{

    int n, x;
    cin >> n;
    cin >> x;

    vector<int> coins(n);
    for (int i = 0; i < n; i++)
    {
        cin >> coins[i];
    }

    vector<vector<int>> dp(n, vector<int>(x + 1, -1));
    return find_ways(n - 1, x, coins, dp);
}