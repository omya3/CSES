#include <iostream>
#include <set>
#include <map>    // FIX 1: Added missing map header
#include <vector> // FIX 1: Added missing vector header

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

    set<int> unseen_set;
    map<int, int> seen_map;

    // A sliding window of size K can contain at most K distinct elements.
    // Therefore, the MEX can never be strictly greater than K.
    for (int i = 0; i <= k; i++)
    {
        unseen_set.insert(i);
    }

    int i = 0;
    for (int j = 0; j < n; j++)
    {
        seen_map[arr[j]] += 1;

        // FIX 3: Erase from unseen_set ONLY when it transitions from 0 to 1 appearance
        if (seen_map[arr[j]] == 1)
        {
            unseen_set.erase(arr[j]);
        }

        // Wait until window reaches size K
        if (j - i + 1 < k)
        {
            continue;
        }
        else
        {
            // O(1) time complexity operation to find the MEX
            cout << *unseen_set.begin() << " ";

            // Remove outgoing element (arr[i])
            seen_map[arr[i]]--;

            // FIX 3: If frequency drops to 0, it is officially unseen again
            if (seen_map[arr[i]] == 0)
            {
                unseen_set.insert(arr[i]);
                seen_map.erase(arr[i]); // Clean up map to save space
            }
            i++; // Slide window
        }
    }
    cout << "\n";
    return 0;
}
