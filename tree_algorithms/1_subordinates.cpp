#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<vector<int>> tree(n + 1);
    vector<int> parent_of(n + 1, 0);

    for (int i = 2; i <= n; i++)
    {
        int p;
        cin >> p;
        tree[p].push_back(i);
        parent_of[i] = p; // Keep track of parent for fast bottom-up processing
    }

    // Step 1: Flatten tree from top to bottom (Generates a safe processing order)
    vector<int> order;
    order.push_back(1);
    int idx = 0;

    while (idx < (int)order.size())
    {
        int curr = order[idx++];
        for (int child : tree[curr])
        {
            order.push_back(child);
        }
    }

    // Step 2: Initialize subtree sizes. Every node is a subtree of size 1 (itself).
    vector<int> subtree_size(n + 1, 1);

    // Step 3: Run backwards from leaf nodes up to the root
    for (int i = n - 1; i >= 0; i--)
    {
        int curr_node = order[i];
        int p = parent_of[curr_node];

        if (p != 0)
        { // If a valid parent exists
            // Add this child's total subtree weight to its immediate parent
            subtree_size[p] += subtree_size[curr_node];
        }
    }

    // Step 4: Subordinates = Subtree Size - 1 (excluding the node itself)
    for (int i = 1; i <= n; i++)
    {
        cout << subtree_size[i] - 1 << " ";
    }
    cout << "\n";

    return 0;
}
