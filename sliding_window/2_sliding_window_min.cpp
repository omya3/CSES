#include <iostream>
#include <vector>
#include <queue> // Required for std::deque

using namespace std;

int main()
{
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n, k;
    if (!(cin >> n >> k))
        return 0;

    long long x, a, b, c;
    cin >> x >> a >> b >> c;

    long long ans = 0; // FIX 5: Initialize ans to 0

    // FIX 3: Changed vector to an actual deque to allow pop_front()
    deque<pair<long long, int>> dq;

    long long current_x = x;

    for (int i = 0; i < n; i++)
    {
        // Generate the sequence on-the-fly (Fixes MLE Issue)
        if (i > 0)
        {
            current_x = ((__int128)current_x * a + b) % c;
        }

        // Maintain the increasing monotonic property
        while (!dq.empty() && dq.back().first >= current_x)
        {
            dq.pop_back();
        }

        dq.push_back({current_x, i});

        // Remove the oldest element if it falls out of the sliding window boundary
        if (dq.front().second <= i - k)
        {
            dq.pop_front();
        }

        // FIX 4: Check if the first complete window of size k is formed
        if (i >= k - 1)
        {
            ans = ans ^ dq.front().first;
        }
    }

    cout << ans << "\n";
    return 0;
}
