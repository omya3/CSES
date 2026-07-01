#include <iostream>
#include <vector>

using namespace std;

int main()
{
    // Fast I/O for competitive programming
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n;
    cin >> n;

    while (n > 1)
    {
        cout << n << " ";

        if (n % 2 == 1)
        {
            n = n * 3 + 1;
        }
        else
        {
            n /= 2;
        }
    }

    // FIX: Print the final 1 after the loop ends
    cout << n << "\n";

    return 0;
}
