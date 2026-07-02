#include <iostream>

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

    // Generator 1: Tracks the leading edge (incoming element)
    long long lead_x = x;
    long long current_window_sum = lead_x;

    // Build the very first window frame (1 to k)
    for (int i = 2; i <= k; i++)
    {
        lead_x = ((__int128)lead_x * a + b) % c;
        current_window_sum += lead_x;
    }

    // XOR track initialized with the first window's sum
    long long final_xor = current_window_sum;

    // Generator 2: Tracks the trailing edge (outgoing element), starting back at x_1
    long long trail_x = x;

    // Slide the window across the remaining n - k positions
    for (int i = k + 1; i <= n; i++)
    {
        // 1. Subtract the element leaving the window
        current_window_sum -= trail_x;

        // 2. Advance the trailing generator by 1 step to match the next drop
        trail_x = ((__int128)trail_x * a + b) % c;

        // 3. Advance the leading generator to pull in the new element
        lead_x = ((__int128)lead_x * a + b) % c;
        current_window_sum += lead_x;

        // 4. Update the aggregate running XOR result
        final_xor ^= current_window_sum;
    }

    cout << final_xor << "\n";
    return 0;
}
