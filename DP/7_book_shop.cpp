#include <iostream>
#include <vector>
#include <algorithm> // Good practice for max()
#include <climits>   // Fixed: Required for INT_MIN

using namespace std;

int selector(int ind, int remaining_size, vector<int> &sizes, vector<int> &prices, vector<vector<int>> &dp)
{
    if (ind < 0)
        return 0;

    if (remaining_size <= 0)
        return 0;

    if (dp[ind][remaining_size] != -1)
        return dp[ind][remaining_size];

    int not_take = selector(ind - 1, remaining_size, sizes, prices, dp);

    int take = INT_MIN;
    int curr_size = sizes[ind];

    if (curr_size <= remaining_size)
    {
        // Fixed: Successfully passes ind - 1 for 0/1 knapsack
        take = prices[ind] + selector(ind - 1, remaining_size - curr_size, sizes, prices, dp);
    }

    return dp[ind][remaining_size] = max(take, not_take); // Fixed: Save to DP table
}

int main()
{
    int n, x;
    cin >> n;
    cin >> x;

    vector<int> sizes(n, 0);  // This will store book prices (weights)
    vector<int> prices(n, 0); // This will store book pages (values)

    // Fixed: First input line contains the book prices
    for (int i = 0; i < n; i++)
    {
        cin >> sizes[i];
    }

    // Fixed: Second input line contains the pages
    for (int i = 0; i < n; i++)
    {
        cin >> prices[i];
    }

    vector<vector<int>> dp(n, vector<int>(x + 1, -1)); // Fixed size
    cout << selector(n - 1, x, sizes, prices, dp) << endl;

    return 0;
}
