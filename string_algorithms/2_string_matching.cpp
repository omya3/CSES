#include <iostream>
#include <string> // Added explicitly
#include <vector> // Fix 1: Added missing vector header
using namespace std;

// Removed the unused 'string p' parameter to keep it clean
vector<int> z_function(string s)
{
    int l = 0, r = 0;
    int n = s.size();
    vector<int> z(n);
    for (int i = 1; i < n; i++)
    {
        // Fix 2a: Changed '>=' to '<=' to check if we are INSIDE the window
        if (i <= r)
        {
            // Fix 2b: Corrected mirror position formula
            int k = i - l;
            z[i] = min(r - i + 1, z[k]);
        }

        while (i + z[i] < n and s[z[i]] == s[i + z[i]])
        {
            z[i] += 1;
        }

        if (i + z[i] - 1 > r)
        {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

int main()
{
    // Fast I/O for large inputs (10^6 constraints)
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s, p;
    if (!(cin >> s >> p))
        return 0;

    if (p.size() > s.size())
    {
        cout << 0 << "\n";
        return 0;
    }

    int count = 0;
    // Pass the combined string into the corrected z_function
    vector<int> z = z_function(p + '$' + s);

    // Fix 3: Start loop from p.size() + 1 to only look inside the 's' portion
    for (int i = p.size() + 1; i < z.size(); i++)
    {
        if (z[i] == p.size())
            count += 1;
    }

    cout << count << "\n";
    return 0;
}
