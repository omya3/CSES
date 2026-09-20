#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 1000000;

int main()
{
    // Fast standard I/O for competitive programming platforms
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 1. Allocate DP tables for precomputation
    vector<long long> fused(MAXN + 1, 0);
    vector<long long> separate(MAXN + 1, 0);

    // 2. Establish Base Cases for height = 1
    fused[1] = 1;
    separate[1] = 1;

    // 3. Populate DP table bottom-up up to 10^6
    for (int i = 2; i <= MAXN; i++)
    {
        // fused[i] = 2 * fused[i-1] + 1 * separate[i-1]
        fused[i] = (2 * fused[i - 1] + separate[i - 1]) % MOD;

        // separate[i] = 1 * fused[i-1] + 4 * separate[i-1]
        separate[i] = (fused[i - 1] + 4 * separate[i - 1]) % MOD;
    }

    // 4. Process all independent test cases efficiently
    int t;
    if (cin >> t)
    {
        while (t--)
        {
            int n;
            cin >> n;

            // Total towers at height n is the sum of both top-layer variations
            long long total_towers = (fused[n] + separate[n]) % MOD;
            cout << total_towers << "\n";
        }
    }

    return 0;
}
