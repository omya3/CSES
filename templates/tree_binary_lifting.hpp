#pragma once

#include <algorithm>
#include <utility>
#include <vector>

namespace cp
{

// parent[root] = 0 and depth[root] = 0.
struct RootedTree
{
    std::vector<int> parent;
    std::vector<int> depth;
};

// Iterative rooting avoids recursion-depth problems on a chain of 2e5 nodes.
inline RootedTree root_tree_iterative(const std::vector<std::vector<int>>& graph,
                                      int root = 1)
{
    const int node_count = static_cast<int>(graph.size()) - 1;
    RootedTree result{
        std::vector<int>(node_count + 1, 0),
        std::vector<int>(node_count + 1, -1)};

    std::vector<int> pending;
    pending.push_back(root);
    result.depth[root] = 0;

    while (!pending.empty())
    {
        const int node = pending.back();
        pending.pop_back();

        for (int neighbour : graph[node])
        {
            if (result.depth[neighbour] != -1)
            {
                continue;
            }

            result.parent[neighbour] = node;
            result.depth[neighbour] = result.depth[node] + 1;
            pending.push_back(neighbour);
        }
    }

    return result;
}

class BinaryLifting
{
public:
    // Arrays are 1-indexed. Use parent[root] = 0.
    BinaryLifting(const std::vector<int>& parent,
                  const std::vector<int>& depth)
        : node_count_(static_cast<int>(parent.size()) - 1), depth_(depth)
    {
        log_ = 1;
        while ((1LL << log_) <= std::max(1, node_count_))
        {
            ++log_;
        }

        up_.assign(log_, std::vector<int>(node_count_ + 1, 0));

        for (int node = 1; node <= node_count_; ++node)
        {
            // Normalize either -1 or 0 to the internal missing-node sentinel 0.
            up_[0][node] = parent[node] > 0 ? parent[node] : 0;
        }

        // up[bit][node] = the 2^bit-th ancestor of node.
        for (int bit = 1; bit < log_; ++bit)
        {
            for (int node = 1; node <= node_count_; ++node)
            {
                const int halfway = up_[bit - 1][node];
                up_[bit][node] = up_[bit - 1][halfway];
            }
        }
    }

    // Returns -1 when the requested ancestor does not exist.
    int kth_ancestor(int node, long long steps) const
    {
        if (!valid_node(node) || steps < 0 || steps > depth_[node])
        {
            return -1;
        }

        return lift(node, static_cast<int>(steps));
    }

    int lca(int first, int second) const
    {
        if (!valid_node(first) || !valid_node(second))
        {
            return -1;
        }

        // MEMORY: level first, then twin-lift from the largest jump down.
        if (depth_[first] < depth_[second])
        {
            std::swap(first, second);
        }

        first = lift(first, depth_[first] - depth_[second]);
        if (first == second)
        {
            return first;
        }

        for (int bit = log_ - 1; bit >= 0; --bit)
        {
            if (up_[bit][first] != up_[bit][second])
            {
                first = up_[bit][first];
                second = up_[bit][second];
            }
        }

        return up_[0][first];
    }

    int distance(int first, int second) const
    {
        const int ancestor = lca(first, second);
        if (ancestor == -1)
        {
            return -1;
        }

        return depth_[first] + depth_[second] - 2 * depth_[ancestor];
    }

    int depth(int node) const
    {
        return valid_node(node) ? depth_[node] : -1;
    }

private:
    int node_count_ = 0;
    int log_ = 1;
    std::vector<int> depth_;
    std::vector<std::vector<int>> up_; // up_[bit][node]

    bool valid_node(int node) const
    {
        return node >= 1 && node <= node_count_ && depth_[node] >= 0;
    }

    int lift(int node, int steps) const
    {
        for (int bit = 0; bit < log_; ++bit)
        {
            if ((steps >> bit) & 1)
            {
                node = up_[bit][node];
            }
        }
        return node;
    }
};

} // namespace cp

