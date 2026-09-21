#include <iostream>
#include <vector>

using namespace std;

int main()
{
    // Fast I/O optimization for competitive programming
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q))
        return 0;

    int LOG = 19;
    vector<vector<int>> boss(n + 1, vector<int>(LOG, -1));

    // Read the immediate parent (2^0-th boss)
    for (int i = 2; i < n + 1; i++)
    {
        cin >> boss[i][0];
    }

    // Precomputing bosses using Binary Lifting
    for (int level = 1; level < LOG; level++)
    {
        for (int emp = 1; emp < n + 1; emp++)
        {
            int intermediate_boss = boss[emp][level - 1];
            if (intermediate_boss != -1)
                boss[emp][level] = boss[intermediate_boss][level - 1];
        }
    }

    // Processing queries
    for (int i = 0; i < q; i++)
    {
        int emp;
        int level;
        cin >> emp >> level;

        int kth_boss = emp;
        for (int bit = 0; bit < LOG; bit++)
        {
            if ((level >> bit) & 1)
            {
                // CRITICAL FIX: Ensure kth_boss isn't already -1 before accessing the array
                if (kth_boss == -1)
                    break;

                kth_boss = boss[kth_boss][bit];
            }
        }

        // Final guard check in case the last jump landed on -1
        if (kth_boss == -1)
            cout << -1 << "\n";
        else
            cout << kth_boss << "\n";
    }
    return 0;
}
