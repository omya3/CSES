#include <iostream>
#include <map>
#include <set> // FIX 1: Added missing set header
#include <vector>

using namespace std;

int main()
{
    // FIX 2: Corrected comment syntax from '/' to '//'
    // Optimise standard I/O streams for execution speed
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n, k;
    if (!(cin >> n >> k))
        return 0;

    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    map<int, int> my_map;
    map<int, set<int>> my_inv_map;

    int i = 0;

    for (int j = 0; j < n; j++)
    {
        // 1. Add incoming element to window
        int old_count = my_map[arr[j]]++;
        if (old_count >= 1)
        {
            my_inv_map[old_count].erase(arr[j]);
            if (my_inv_map[old_count].empty()) // FIX 3: Replaced len() with .empty()
            {
                my_inv_map.erase(old_count);
            }
        }
        my_inv_map[old_count + 1].insert(arr[j]);

        // 2. Wait until window reaches size K
        if (j - i + 1 < k)
        {
            continue;
        }
        else
        {
            // Your one-liner works! rbegin() fetches the highest frequency key.
            auto [_, ele] = *my_inv_map.rbegin();
            cout << *ele.begin() << " ";

            // 3. Remove outgoing element (arr[i]) from window
            int current_count = my_map[arr[i]]; // FIX 4: Corrected variable logic to target arr[i]
            my_map[arr[i]]--;

            if (my_map[arr[i]] == 0)
            {
                my_map.erase(arr[i]);
            }

            // Update inverted map for the outgoing element
            my_inv_map[current_count].erase(arr[i]);
            if (my_inv_map[current_count].empty())
            {
                my_inv_map.erase(current_count);
            }

            if (current_count > 1)
            {
                my_inv_map[current_count - 1].insert(arr[i]);
            }

            i++; // Slide window forward
        }
    }
    cout << "\n";
    return 0;
}
