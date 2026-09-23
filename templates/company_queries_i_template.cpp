#include <iostream>
#include <vector>

#include "tree_binary_lifting.hpp"

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int node_count, query_count;
    std::cin >> node_count >> query_count;

    std::vector<int> parent(node_count + 1, 0);
    std::vector<int> depth(node_count + 1, 0);

    // CSES guarantees parent[node] < node, so the parent's depth is ready.
    for (int node = 2; node <= node_count; ++node)
    {
        std::cin >> parent[node];
        depth[node] = depth[parent[node]] + 1;
    }

    const cp::BinaryLifting tree(parent, depth);

    while (query_count-- > 0)
    {
        int node;
        long long steps;
        std::cin >> node >> steps;
        std::cout << tree.kth_ancestor(node, steps) << '\n';
    }
}

