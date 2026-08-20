// Key errors in solving the CSES Shortest Routes I problem included using uninitialized vectors,
// failing to erase nodes from the std::set in Dijkstra's, and using an insufficiently large value for infinity (1e9 vs 1e18) [1].
//  Additional mistakes involved incorrect relaxation logic, C++ syntax errors, and failing to optimize input/output for large datasets [1].
//  Review these patterns to avoid segmentation faults, TLE, and WA on graph problems.

#include <iostream>
#include <vector>
#include <set>

using namespace std;
const long long INF = 1e17;

int main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int cities, routes;
    cin >> cities >> routes;

    vector<vector<pair<int, int>>> map(cities + 1);
    vector<long long> dist(cities + 1, INF);

    for (int i = 0; i < routes; i++)
    {
        int c1, c2, d;
        cin >> c1 >> c2 >> d;

        map[c1].push_back({c2, d});
    }

    set<pair<long long, int>> q;

    q.insert({0, 1});
    dist[1] = 0;

    while (!q.empty())
    {

        auto [d, node] = *q.begin();
        q.erase(q.begin());

        for (auto &neigh : map[node])
        {
            int neigh_node = neigh.first;
            int edge_weight = neigh.second;

            if (dist[neigh_node] > dist[node] + edge_weight)
            {
                if (dist[neigh_node] != INF)
                {
                    q.erase({dist[neigh_node], neigh_node});
                }

                dist[neigh_node] = dist[node] + edge_weight;
                q.insert({dist[neigh_node], neigh_node});
            }
        }
    }

    for (int i = 1; i <= cities; i++)
    {
        cout << dist[i] << (i == cities ? "" : " ");
    }
    cout << "\n";

    return 0;
}