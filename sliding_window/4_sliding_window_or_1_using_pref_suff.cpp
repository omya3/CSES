#include <iostream>
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

    long long x, a, b, c;
    cin >> x >> a >> b >> c;

    // Use vector<int> to stay perfectly within the 512MB memory limit
    vector<int> arr(n);

    // LOGIC BLOCK 1: Clean Element Generation
    arr[0] = x;
    for (int i = 1; i < n; i++)
    {
        // Cast to __int128 to prevent internal 64-bit multiplication overflows
        arr[i] = ((__int128)arr[i - 1] * a + b) % c;
    }

    // LOGIC BLOCK 2: Forward Prefix Calculation (Resets every k steps)
    vector<int> prefix(n);
    for (int i = 0; i < n; i++)
    {
        if (i % k == 0)
        {
            prefix[i] = arr[i];
        }
        else
        {
            prefix[i] = prefix[i - 1] | arr[i]; // Use standard bitwise OR '|'
        }
    }

    // LOGIC BLOCK 3: Backward Suffix Calculation (Resets every k steps)
    vector<int> suffix(n);
    for (int i = n - 1; i >= 0; i--)
    {
        // Reset condition: If it's the last element of the entire array,
        // OR if it's the absolute end element of a block of size k.
        if (i == n - 1 || (i + 1) % k == 0)
        {
            suffix[i] = arr[i];
        }
        else
        {
            suffix[i] = suffix[i + 1] | arr[i];
        }
    }

    // LOGIC BLOCK 4: Window Query Calculation
    long long ans = 0;
    for (int i = k - 1; i < n; i++)
    {
        int left_idx = i - k + 1;
        int right_idx = i;

        // The left bound spans to its block's end using SUFFIX.
        // The right bound spans from its block's start using PREFIX.
        long long curr = suffix[left_idx] | prefix[right_idx];
        ans = ans ^ curr;
    }

    cout << ans << "\n";
    return 0;
}
