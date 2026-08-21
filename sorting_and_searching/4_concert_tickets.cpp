#include <iostream>
#include <set>
#include <vector> // Fixed: Added missing header

using namespace std;

int main()
{
    // Fixed: Fast I/O for competitive programming performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<int> customers(m, 0);
    multiset<int> mt;

    for (int i = 0; i < n; i++)
    {
        int price; // Fixed: Declared the variable type
        cin >> price;
        mt.insert(price);
    }

    for (int i = 0; i < m; i++)
    {
        cin >> customers[i];
    }

    for (auto amt : customers)
    {
        auto it = mt.upper_bound(amt);

        if (it == mt.begin())
        {
            cout << -1 << "\n"; // Fixed: Changed space to newline
        }
        else
        {
            --it;
            cout << *it << "\n"; // Fixed: Changed space to newline
            mt.erase(it);
        }
    }

    return 0;
}
