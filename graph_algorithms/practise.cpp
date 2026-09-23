#include <iostream>
using namespace std;

class DSU
{
public:
    vector<int> parent;
    vector<int> rank;

private:
    DSU(int n)
    {
        parent.resize(n + 1);
        rank.resize(n + 1);
        for (int i = 0; i < parent.size(); i++)
            parent[i] = i;
    }

    bool find_set(int v)
    {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }

    bool union_sets(int a, int b)
    {
        a = find_set(a);
        b = find_set(b);
        if (a != b)
        {
            if (rank[a] < rank[b])
                swap(a, b);

            parent[b] = a;

            if (rank[a] == rank[b])
                rank[a] += 1;
            return true;
        }
        return false;
    }
};