#include <vector>
#include <iostream>
#include <string> // FIX 1: Added missing string header

using namespace std;

int main()
{
    // Optimise standard I/O streams for execution speed
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m))
        return 0;

    vector<string> grid(n);
    for (int i = 0; i < n; i++)
    {
        cin >> grid[i];
    }

    vector<string> grid(n);

    queue<int, int> q;
    q.push(0, 0);
    int count = 0;
    while (!q.empty())
    {
    }

    return 0;
}
