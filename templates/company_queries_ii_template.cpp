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

    for (int node = 2; node <= node_count; ++node)
    {
        std::cin >> parent[node];
        depth[node] = depth[parent[node]] + 1;
    }

    const cp::BinaryLifting tree(parent, depth);

    while (query_count-- > 0)
    {
        int first, second;
        std::cin >> first >> second;
        std::cout << tree.lca(first, second) << '\n';
    }
}

