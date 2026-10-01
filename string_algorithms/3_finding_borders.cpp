#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    // Optimise standard I/O operations for performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (!(cin >> s))
        return 0;

    int n = s.length();
    vector<int> z(n, 0);

    // 1. Standard O(n) Z-Algorithm implementation
    int l = 0, r = 0;
    for (int i = 1; i < n; i++)
    {
        if (i <= r)
        {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
        {
            z[i]++;
        }
        if (i + z[i] - 1 > r)
        {
            l = i;
            r = i + z[i] - 1;
        }
    }

    // 2. Scan to collect border lengths in increasing order
    // We check from the largest index down to 1 (which translates to processing
    // smaller border lengths to larger border lengths)
    for (int i = n - 1; i >= 1; i--)
    {
        if (z[i] == n - i)
        {
            cout << z[i] << " ";
        }
    }
    cout << "\n";

    return 0;
}
