#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

const long long INF = 1e18; // Fixed: Use long long infinity to prevent overflow
const int MOD = 1e9 + 7;    // Fixed: Required modulo constraint

int main() // Fixed: Corrected function name from manin()
{
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m))
        return 0;

    vector<vector<pair<int, int>>> adj(n + 1);

    for (int i = 0; i < m; i++)
    {
        int u, v, cost;
        cin >> u >> v >> cost;
        adj[u].push_back({v, cost});
    }

    vector<long long> min_dist(n + 1, INF); // Fixed: Initialized to long long INF
    vector<long long> num_routes(n + 1, 0);
    vector<int> min_flights(n + 1, 2e9);
    vector<int> max_flights(n + 1, -1);

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push({0, 1});
    min_dist[1] = 0;
    num_routes[1] = 1;
    min_flights[1] = 0;
    max_flights[1] = 0;

    while (!pq.empty())
    {
        // Fixed: Unpacked pair correctly as [cost, node]
        auto [cost, node] = pq.top();
        pq.pop();

        if (cost > min_dist[node])
            continue;

        for (auto &[neigh, neigh_cost] : adj[node])
        {
            if (cost + neigh_cost < min_dist[neigh])
            {
                min_dist[neigh] = cost + neigh_cost;
                num_routes[neigh] = num_routes[node];
                min_flights[neigh] = min_flights[node] + 1;
                max_flights[neigh] = max_flights[node] + 1;
                pq.push({min_dist[neigh], neigh});
            }
            else if (cost + neigh_cost == min_dist[neigh]) // Fixed: Use 'else if' and proper metrics accumulation
            {
                num_routes[neigh] = (num_routes[neigh] + num_routes[node]) % MOD;    // Fixed: Modulo addition
                min_flights[neigh] = min(min_flights[neigh], min_flights[node] + 1); // Fixed: Take minimum
                max_flights[neigh] = max(max_flights[neigh], max_flights[node] + 1); // Fixed: Take maximum
            }
        }
    }
    cout << min_dist[n] << " " << num_routes[n] << " " << min_flights[n] << " " << max_flights[n] << "\n";
    return 0;
}
