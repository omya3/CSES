#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;

    long long need = 0;

    int first;
    int second;

    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            cin >> second;
        }
        else
        {
            cin >> first;
            if (first <= second)
            {
                need += (second - first);
            }
            else
            {
                second = first;
            }
        }
    }
    cout << need;
}