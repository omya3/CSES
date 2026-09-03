#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    // Fast I/O for CSES performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int x, n;
    cin >> x >> n;

    set<int> positions;    // Tracks where lights are
    multiset<int> lengths; // Tracks the sizes of all segments

    // Initialize boundaries
    positions.insert(0);
    positions.insert(x);
    lengths.insert(x); // Initially, one massive segment of length x

    for (int i = 0; i < n; i++)
    {
        int l_pos;
        cin >> l_pos;

        // Find the light right AFTER the new light
        auto it = positions.upper_bound(l_pos);

        int a_pos = *it;       // Position after
        int p_pos = *prev(it); // Position before (using prev leaves 'it' untouched)

        // 1. Remove the old combined length from our tracking multiset
        // Use find() so we only erase a single instance of that length!
        lengths.erase(lengths.find(a_pos - p_pos));

        // 2. Insert the two new smaller segment lengths
        lengths.insert(l_pos - p_pos);
        lengths.insert(a_pos - l_pos);

        // 3. Add the new light to our position tracker
        positions.insert(l_pos);

        // 4. The maximum length is always at the very end of the sorted multiset
        cout << *lengths.rbegin() << (i == n - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}
