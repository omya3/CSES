#include <iostream>
#include <vector> // FIX 1: Added missing vector header

// Required extensions for Policy-Based Data Structures
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds; // FIX 2: Added missing PBDS namespace

typedef tree<
    int,
    null_type,
    less_equal<int>, // Use less_equal instead of less to allow duplicate numbers
    rb_tree_tag,
    tree_order_statistics_node_update>
    ordered_multiset;

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

    ordered_multiset my_window;

    int i = 0;
    for (int j = 0; j < n; j++)
    {
        my_window.insert(arr[j]); // FIX 3: Added missing semicolon

        // Wait until window reaches size K
        if (j - i + 1 < k)
        {
            continue;
        }
        else
        {
            // O(log K) time complexity operation to find the Median
            cout << *my_window.find_by_order((k - 1) / 2) << " ";

            // Erase exactly one copy of the outgoing element safely
            auto erase_it = my_window.find_by_order(my_window.order_of_key(arr[i]));
            my_window.erase(erase_it); // FIX 4: Added missing semicolon

            i++; // Slide window
        }
    }
    cout << "\n";
    return 0;
}
