#include <iostream>
#include <vector>    // Added missing library
#include <algorithm> // For sort and lower_bound

using namespace std;

struct Project
{
    int start;
    int end;
    long long value; // Upgraded to long long to prevent overflow

    Project(int start, int end, long long val) : start(start), end(end), value(val) {}
};

// Upgraded return type to long long
long long finder(int ind, vector<Project> &p_list)
{
    if (ind >= p_list.size())
        return 0;

    long long select = p_list[ind].value;
    int select_end = p_list[ind].end;
    int next_start = select_end + 1;

    auto it = lower_bound(p_list.begin() + ind + 1, p_list.end(), next_start,
                          [](const Project &p1, int target)
                          {
                              return p1.start < target;
                          });

    int next_idx = distance(p_list.begin(), it);
    select += finder(next_idx, p_list);

    long long not_select = 0 + finder(ind + 1, p_list);

    return max(select, not_select);
}

int main()
{
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (cin >> n)
    {
        vector<Project> p_list;
        for (int i = 0; i < n; i++)
        {
            int start;
            int end;
            long long value; // Upgraded to long long

            cin >> start;
            cin >> end;
            cin >> value;
            p_list.push_back(Project(start, end, value));
        }

        sort(p_list.begin(), p_list.end(), [](const Project &p1, const Project &p2)
             {
                 if (p1.start != p2.start)
                 {
                     return p1.start < p2.start;
                 }
                 return p1.end < p2.end; });

        // Correctly print the result to the console
        cout << finder(0, p_list) << "\n";
    }

    return 0;
}
