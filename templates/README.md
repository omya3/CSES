# Binary Lifting Templates

These templates cover three common tree-query operations:

```cpp
tree.kth_ancestor(node, steps); // Missing ancestor -> -1
tree.lca(first, second);        // Lowest common ancestor
tree.distance(first, second);   // Number of tree edges
```

## Files

- `tree_binary_lifting.hpp` — reusable implementation
- `company_queries_i_template.cpp` — k-th ancestor driver
- `company_queries_ii_template.cpp` — LCA driver for a parent list
- `distance_queries_template.cpp` — distance driver for undirected edges

## Complexity

For `n` nodes:

- Preprocessing: `O(n log n)`
- Each k-th ancestor query: `O(log n)`
- Each LCA query: `O(log n)`
- Each distance query: `O(log n)`
- Memory: `O(n log n)`

## Core memory model

```text
up[bit][node] = node's 2^bit-th ancestor

k-th ancestor:
    decompose k into set bits and take those jumps

LCA:
    1. level the deeper node
    2. if equal, return it
    3. twin-lift from largest bit to smallest
    4. return the immediate parent

distance(a, b):
    depth[a] + depth[b] - 2 * depth[lca(a, b)]
```

## Design decisions

- Nodes are 1-indexed.
- Node `0` is the internal missing-parent sentinel.
- The public k-th ancestor API returns `-1` when no ancestor exists.
- `LOG` is calculated dynamically; do not memorize `19` or `20`.
- General trees are rooted iteratively to avoid recursion-stack overflow on a
  long chain.
- Query methods are `const` because they do not modify preprocessing data.

## Compile

From this directory:

```sh
clang++ -std=c++17 -O2 -Wall -Wextra -pedantic company_queries_i_template.cpp -o company_queries_i
clang++ -std=c++17 -O2 -Wall -Wextra -pedantic company_queries_ii_template.cpp -o company_queries_ii
clang++ -std=c++17 -O2 -Wall -Wextra -pedantic distance_queries_template.cpp -o distance_queries
```

## What to memorize

Memorize the four ideas, not every line:

1. `up[bit][node]` table construction
2. lifting one node by the set bits of a distance
3. leveling followed by descending twin-lifting for LCA
4. the distance formula

Before a placement, retype the class once without looking and test it on a
five-node tree.

