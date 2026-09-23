#include <iostream>
#include <vector>

#include "tree_binary_lifting.hpp"

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int node_count, query_count;
    std::cin >> node_count >> query_count;

    std::vector<std::vector<int>> graph(node_count + 1);
    for (int edge = 0; edge < node_count - 1; ++edge)
    {
        int first, second;
        std::cin >> first >> second;
        graph[first].push_back(second);
        graph[second].push_back(first);
    }

    const cp::RootedTree rooted = cp::root_tree_iterative(graph, 1);
    const cp::BinaryLifting tree(rooted.parent, rooted.depth);

    while (query_count-- > 0)
    {
        int first, second;
        std::cin >> first >> second;
        std::cout << tree.distance(first, second) << '\n';
    }
}

