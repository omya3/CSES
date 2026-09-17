#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main()
{
    // Fast I/O to ensure it clears strict execution time limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    cin >> n;
    cin >> x;

    vector<int> sizes(n, 0);
    vector<int> prices(n, 0);

    for (int i = 0; i < n; i++)
    {
        cin >> sizes[i];
    }

    for (int i = 0; i < n; i++)
    {
        cin >> prices[i];
    }

    vector<int> prev(x + 1, 0);
    vector<int> curr(x + 1, 0);

    // Handle base case for the first book
    for (int i = 0; i < x + 1; i++)
    {
        if (i >= sizes[0])
            prev[i] = prices[0];
    }

    // Initialize curr with prev's values in case n = 1
    curr = prev;

    for (int ind = 1; ind < n; ind++)
    {
        for (int remaining_size = 0; remaining_size < x + 1; remaining_size++)
        {
            int not_take = prev[remaining_size];

            int take = INT_MIN;
            int curr_size = sizes[ind];

            if (curr_size <= remaining_size)
            {
                take = prices[ind] + prev[remaining_size - curr_size];
            }

            curr[remaining_size] = max(take, not_take);
        }
        // Fixed: The current row calculations become the previous row for the next book
        prev = curr;
    }

    cout << curr[x] << "\n";

    return 0;
}
