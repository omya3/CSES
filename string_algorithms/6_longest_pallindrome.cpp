#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// FIX 1: Changed return type to void since the function prints the output directly
void largest_pal(string s)
{
    int l = 0;
    int r = 0;

    string s_new = "^#";
    for (auto &it : s)
    {
        s_new += it;
        s_new += '#';
    }
    s_new += '$';

    int max_rad = 0;
    int max_i = 0;

    int n = s_new.size();
    vector<int> man_box(n, 0);

    for (int i = 1; i < n - 1; i++)
    {
        if (i < r)
        {
            man_box[i] = max(0, min(r - i, man_box[l + r - i]));
        }

        while (s_new[i - (1 + man_box[i])] == s_new[i + (1 + man_box[i])])
        {
            man_box[i] += 1;
        }

        if (i + man_box[i] > r)
        {
            l = i - man_box[i];
            r = i + man_box[i];
        }

        if (man_box[i] > max_rad)
        {
            max_rad = man_box[i];
            max_i = i;
        }
    }

    int start_index = (max_i - max_rad - 1) / 2;
    // FIX 2: Used "\n" instead of endl to prevent slow flushing times on huge text inputs
    cout << s.substr(start_index, max_rad) << "\n";
}

int main()
{
    // FIX 3: Desynchronize standard I/O streams for competitive programming speeds
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (cin >> s)
    {
        largest_pal(s);
    }
    return 0;
}
