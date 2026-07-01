#include <iostream>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n;
    cin >> n;

    long long sum = 0;
    for (int i = 0; i < n - 1; i++)
    {
        long long j;
        cin >> j;
        sum += j;
    }

    long long sum_n = (n * (n + 1) / 2);

    cout << sum_n - sum;
}