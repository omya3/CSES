#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Using a large value for infinity that won't overflow during addition
const long long INF = 1e18;

struct Edge
{
    int to;
    long long price;
};

struct State
{
    long long cost;
    int city;
    int coupon_used;

    // Custom comparator for min-heap sorting
    bool operator>(const State &other) const
    {
        return cost > other.cost;
    }
};

int main()
{
    // Optimize standard I/O operations for performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m))
        return 0;

    vector<vector<Edge>> adj(n + 1);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
    }

    // dist[city][0/1 coupon status]
    vector<vector<long long>> dist(n + 1, vector<long long>(2, INF));
    vector<vector<bool>> visited(n + 1, vector<bool>(2, false));
    priority_queue<State, vector<State>, greater<State>> pq;

    // Initialize source (City 1, cost 0, coupon unused)
    dist[1][0] = 0;
    pq.push({0, 1, 0});

    while (!pq.empty())
    {
        State curr = pq.top();
        pq.pop();

        int u = curr.city;
        int used = curr.coupon_used;

        // When City N pops from the heap with the coupon used, we have our answer
        if (u == n && used == 1)
        {
            cout << curr.cost << "\n";
            return 0;
        }

        if (visited[u][used])
            continue;
        visited[u][used] = true;

        for (const auto &edge : adj[u])
        {
            int v = edge.to;
            long long weight = edge.price;

            // Option 1: Move forward normally without using a coupon
            if (dist[u][used] + weight < dist[v][used])
            {
                dist[v][used] = dist[u][used] + weight;
                pq.push({dist[v][used], v, used});
            }

            // Option 2: Apply the coupon to this leg (only if it hasn't been used yet)
            if (used == 0)
            {
                long long discounted_weight = weight / 2;
                if (dist[u][0] + discounted_weight < dist[v][1])
                {
                    dist[v][1] = dist[u][0] + discounted_weight;
                    pq.push({dist[v][1], v, 1});
                }
            }
        }
    }

    return 0;
}
