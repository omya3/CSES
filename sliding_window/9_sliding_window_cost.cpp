#include <iostream>
#include <vector>
#include <set>

using namespace std;

typedef long long ll;

multiset<int> left_set, right_set;
ll ls = 0, rs = 0;
ll k;

// Universal balancing logic that safely protects against empty structures
void rebalance()
{
    // We strictly enforce that right_set contains exactly (k + 1) / 2 elements.
    size_t target_right_size = (k + 1) / 2;

    while (right_set.size() < target_right_size && !left_set.empty())
    {
        auto it = prev(left_set.end());
        ll v = *it;
        ls -= v;
        rs += v;
        right_set.insert(v);
        left_set.erase(it);
    }
    while (right_set.size() > target_right_size && !right_set.empty())
    {
        auto it = right_set.begin();
        ll v = *it;
        rs -= v;
        ls += v;
        left_set.insert(v);
        right_set.erase(it);
    }
}

void add(ll v)
{
    // If right_set has elements and v belongs to the upper half
    if (!right_set.empty() && v >= *right_set.begin())
    {
        rs += v;
        right_set.insert(v);
    }
    else
    {
        ls += v;
        left_set.insert(v);
    }
    rebalance();
}

void remove_val(ll v)
{
    // Check if the value to remove lies in the right_set or left_set
    if (!right_set.empty() && v >= *right_set.begin())
    {
        auto it = right_set.find(v);
        if (it != right_set.end())
        {
            rs -= v;
            right_set.erase(it);
        }
    }
    else
    {
        auto it = left_set.find(v);
        if (it != left_set.end())
        {
            ls -= v;
            left_set.erase(it);
        }
    }
    rebalance();
}

ll get_cost()
{
    ll med = *right_set.begin(); // Perfect median point
    ll left_cost = (ll)left_set.size() * med - ls;
    ll right_cost = rs - (ll)right_set.size() * med;
    return left_cost + right_cost;
}

int main()
{
    // Optimize standard I/O streams for competitive programming speeds
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n;
    if (!(cin >> n >> k))
        return 0;

    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    int i = 0;
    for (int j = 0; j < n; j++)
    {
        add(arr[j]);

        if (j - i + 1 < k)
            continue;

        cout << get_cost() << " ";

        remove_val(arr[i]);
        i++;
    }
    cout << "\n";
    return 0;
}
