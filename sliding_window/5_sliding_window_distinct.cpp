#include <iostream>
#include <map> // FIX: Include missing map header
#include <vector>

using namespace std;

int main()
{
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
    int ans_unique = 0;

    // 1. Process the very first window of size k
    for (int i = 0; i < k; i++)
    {
        if (my_map.find(arr[i]) == my_map.end())
        {
            ans_unique++;
            my_map[arr[i]] = 1;
        }
        else
        {
            my_map[arr[i]] += 1;
        }
    }

    cout << ans_unique << " ";

    int left = 0;
    int right = k - 1;

    // 2. Slide the window safely across the remainder of the array
    while (right < n - 1)
    {
        // --- REMOVE OLD ELEMENT (arr[left]) ---
        my_map[arr[left]]--; // FIX: Use arr[left], not index 'left'
        if (my_map[arr[left]] == 0)
        {
            ans_unique--;
            my_map.erase(arr[left]); // Clean up map to avoid phantom entries
        }
        left++;

        // --- ADD NEW ELEMENT (arr[right + 1]) ---
        right++; // Advance safely within bounds

        // FIX: Use arr[right] consistently as the key and add () to .end()
        if (my_map.find(arr[right]) != my_map.end())
        {
            my_map[arr[right]]++; // FIX: Use arr[right], not index 'right'
        }
        else
        {
            my_map[arr[right]] = 1; // FIX: Use arr[right], not index 'right'
            ans_unique++;
        }

        cout << ans_unique << " ";
    }

    cout << "\n";
    return 0;
}
