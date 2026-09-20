#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Initialize to 0 so it handles single edges and small inputs correctly
int diameter = 0;

int find_diameter(int parent, int node, vector<vector<int>> &tree, vector<int> &heights)
{
    // Clean base case: if it's a leaf node, its height contribution is 0
    if (tree[node].size() == 1 && tree[node][0] == parent)
    {
        heights[node] = 0;
        return 0;
    }

    int first_max_height = 0;
    int second_max_height = 0;

    for (auto &it : tree[node])
    {
        if (it == parent)
            continue;

        if (heights[it] == -1)
        {
            // The edge connecting to the child contributes exactly 1 unit of length
            heights[it] = 1 + find_diameter(node, it, tree, heights);
        }

        if (heights[it] > first_max_height)
        {
            second_max_height = first_max_height;
            first_max_height = heights[it];
        }
        else if (heights[it] > second_max_height)
        {
            second_max_height = heights[it];
        }
    }

    // A node's height is simply the height of its longest branch
    heights[node] = first_max_height;

    // The maximum path passing through this node as a turning point
    diameter = max(diameter, first_max_height + second_max_height);

    return heights[node];
}

int main()
{
    // Fast I/O for performance efficiency
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n))
        return 0;

    // Corner case explicitly caught
    if (n == 1)
    {
        cout << 0 << "\n";
        return 0;
    }

    vector<vector<int>> tree(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    vector<int> heights(n + 1, -1);

    // Pass '0' as a dummy parent value for the root node 1
    find_diameter(0, 1, tree, heights);

    cout << diameter << "\n";
    return 0;
}
