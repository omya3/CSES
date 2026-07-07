#include <iostream>
#include <vector>

// Required extensions for Policy-Based Data Structures
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

// FIX 1: We track unique pair<int, int> -> {value, global_index}
// We use less<pair<int, int>> because tracking the unique index eliminates identical duplicates!
typedef tree<
    pair<int, int>,
    null_type,
    less<pair<int, int>>,
    rb_tree_tag,
    tree_order_statistics_node_update>
    ordered_window_set;

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

    ordered_window_set my_window;

    int i = 0;
    long long inv = 0; // Inversions can exceed integer limits for larger windows

    for (int j = 0; j < n; j++)
    {
        // 1. Calculate how many elements currently in the window are STRICTLY GREATER than arr[j].
        // To find elements > arr[j], we find how many are less than or equal to {arr[j], total_infinity}.
        // The value {arr[j] + 1, 0} serves as a perfect boundary.
        int elements_less_or_equal = my_window.order_of_key({arr[j] + 1, 0});
        int strictly_greater = my_window.size() - elements_less_or_equal;

        inv += strictly_greater;

        // Insert incoming element paired with its unique index
        my_window.insert({arr[j], j});

        // Wait until window reaches size K
        if (j - i + 1 < k)
        {
            continue;
        }
        else
        {
            cout << inv << " ";

            // 2. Remove the outgoing element (arr[i]) and subtract its contribution.
            // Elements inside the window that form an inversion with arr[i] are those
            // that are STRICTLY LESS than arr[i].
            long long strictly_less = my_window.order_of_key({arr[i], 0});
            inv -= strictly_less;

            // Safe removal in O(log K) because the pair is globally unique
            my_window.erase({arr[i], i});
            i++; // Slide window
        }
    }
    cout << "\n";
    return 0;
}
