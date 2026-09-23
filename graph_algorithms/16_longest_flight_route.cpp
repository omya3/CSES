#include <iostream>
#include <vector>
#include <queue>
#include <algorithm> // Required for reverse()

using namespace std;

int main()
{
    // Fast I/O optimization
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m))
        return 0;

    // Use a vector of vectors for dynamic 2D array representation
    vector<vector<int>> adj(n + 1);
    vector<int> indegree(n + 1, 0);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        indegree[b] += 1;
    }

    queue<int> q;
    for (int i = 1; i <= n; i++)
    {
        if (indegree[i] == 0)
            q.push(i);
    }

    vector<int> toposort;
    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        toposort.push_back(node);

        for (int neigh : adj[node])
        {
            indegree[neigh] -= 1;
            if (indegree[neigh] == 0)
                q.push(neigh);
        }
    }

    vector<int> distance(n + 1, -1);
    vector<int> parent(n + 1, -1);
    distance[1] = 1; // Start at city 1 with a count of 1 city visited

    for (int u : toposort)
    {
        // CRITICAL FIX FOR TEST 5: Only push updates forward if 'u' is reachable from node 1
        if (distance[u] != -1)
        {
            for (int v : adj[u])
            {
                if (distance[u] + 1 > distance[v])
                {
                    distance[v] = distance[u] + 1;
                    parent[v] = u;
                }
            }
        }
    }

    if (distance[n] == -1)
    {
        cout << "IMPOSSIBLE\n";
    }
    else
    {
        // CRITICAL FIX: Print the maximum number of cities first!
        cout << distance[n] << "\n";

        vector<int> path;
        int curr = n;

        while (curr != -1)
        {
            path.push_back(curr);
            curr = parent[curr];
        }

        reverse(path.begin(), path.end());

        // Using 'size_t' to match signedness and eliminate compiler warnings
        for (size_t i = 0; i < path.size(); i++)
        {
            cout << path[i] << (i == path.size() - 1 ? "" : " ");
        }
        cout << "\n";
    }
    return 0;
}
