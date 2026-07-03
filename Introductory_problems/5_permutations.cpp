#include <iostream>
using namespace std;

int main()
{

    int n;
    cin >> n;

    if (n <= 3 and n >= 2)
    {
        cout << "NO SOLUTION";
        return 0;
    }

    int j = 2;
    while (j <= n)
    {
        cout << j << " ";
        j += 2;
    }

    j = 1;

    while (j <= n)
    {
        cout << j << " ";
        j += 2;
    }

    return 0;
}