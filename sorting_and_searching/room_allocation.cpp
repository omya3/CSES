#include <iostream>
#include <set>
#include <vector>    // Fixed: Added missing header
#include <algorithm> // Fixed: Added missing header

using namespace std;

struct Customer
{
    int arrival;
    int departure;
    int original_index;
};

int main()
{
    // Fast I/O for CSES performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<Customer> schedule(n); // Fixed: Initialized with size 'n'
    multiset<pair<int, int>> mt; // dep and room no.

    for (int i = 0; i < n; i++)
    {
        // Fixed: Read directly into the structured vector elements
        cin >> schedule[i].arrival;
        cin >> schedule[i].departure;
        schedule[i].original_index = i;
    }
    
    auto cmp = [](const Customer &a, const Customer &b)
    {
        if (a.arrival == b.arrival)
        {
            return a.departure < b.departure;
        }
        return a.arrival < b.arrival;
    };

    sort(schedule.begin(), schedule.end(), cmp);
    int room_count = 0;
    vector<int> room_list(n, -1);

    for (auto sc : schedule)
    {
        if (!mt.empty() && mt.begin()->first < sc.arrival)
        {
            int reused_room = mt.begin()->second;
            // Fixed: Safely erasing only the first element iterator 
            mt.erase(mt.begin()); 

            room_list[sc.original_index] = reused_room;
            mt.insert({sc.departure, reused_room});
        }
        else
        {
            room_count += 1;
            room_list[sc.original_index] = room_count;
            mt.insert({sc.departure, room_count});
        }
    }

    // Fixed: Added mandatory output logic for CSES
    cout << room_count << "\n";
    for (int i = 0; i < n; i++)
    {
        cout << room_list[i] << (i == n - 1 ? "" : " ");
    }
    cout << "\n";

    return 0; // Fixed: main must return an int
}
