#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * 🧠 FLOYD-WARSHALL ALGORITHM (CSES: Shortest Routes II)
 *
 * 📌 POINTS TO REMEMBER FOR PLACEMENT / COMPETITIVE TESTS:
 *
 * 1. MULTIPLE EDGES BETWEEN SAME NODES (Critical Trap):
 *    - The problem statement says "roads between them", but input can list multiple different
 *      roads between the same two cities.
 *    - ALWAYS use `min(dist[a][b], c)` when reading inputs to drop suboptimal parallel paths.
 *
 * 2. OVERFLOW RISK (Data Types):
 *    - Node limits are n <= 500, but route weights can reach c <= 10^9.
 *    - Accumulating these values over multiple path steps will overflow a standard 32-bit `int`.
 *    - ALWAYS use a `long long` for both the matrix layout and the infinity definition.
 *
 * 3. CONTROLLED INFINITY VALUE (INF):
 *    - Do NOT use LLONG_MAX or 1e18 as your INF value!
 *    - Inside the nested loop, you evaluate `dist[i][k] + dist[k][j]`. If both are 1e18,
 *      adding them yields 2e18, which triggers a positive sign overflow crash in C++.
 *    - Choose a safe bound like `1e15`. It is larger than any possible path max length (500 * 10^9)
 *      but small enough that adding `INF + INF` doesn't spill past `long long` limits.
 *
 * 4. INITIALIZE SELF-DISTANCE (The Base Diagonal):
 *    - Remember to manually seed `dist[i][i] = 0` for all nodes.
 *    - If left as INF, calculations involving moving from a node to itself will calculate dummy paths.
 *
 * 5. LOOP ORDER MATTERS (The Intermediate Node First):
 *    - The outer loop variable MUST be the intermediate node `k`.
 *    - If you put `i` or `j` as the outer loops, the DP matrix will calculate snapshots out of order,
 *      resulting in incorrect shortest values.
 */

const long long INF = 1e15; // Safe buffer boundary avoiding variable additions overflows

int main()
{
    // Fast I/O optimization
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q;
    if (!(cin >> n >> m >> q))
        return 0;

    // Initialize the adjacency matrix with our safe INF threshold
    vector<vector<long long>> dist(n + 1, vector<long long>(n + 1, INF));

    // Point 4: Distance from a node to itself is always 0
    for (int i = 1; i <= n; i++)
    {
        dist[i][i] = 0;
    }

    // Read road segments
    for (int i = 0; i < m; i++)
    {
        long long a, b, c;
        cin >> a >> b >> c;
        // Point 1: Keep only the minimum edge weight for multiple edges between identical nodes
        dist[a][b] = min(dist[a][b], c);
        dist[b][a] = min(dist[b][a], c);
    }

    // Floyd-Warshall Engine: O(n^3) implementation
    // Point 5: 'k' (intermediate pivot helper node) MUST be the outermost loop
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                // If a route traveling through 'k' offers a shortcut, relax the path cell
                if (dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Handle incoming queries in O(1) constant lookup time
    for (int i = 0; i < q; i++)
    {
        int a, b;
        cin >> a >> b;

        // If distance remains untouched at INF, the cities are physically unreachable
        if (dist[a][b] >= INF)
        {
            cout << -1 << "\n";
        }
        else
        {
            cout << dist[a][b] << "\n";
        }
    }

    return 0;
}
