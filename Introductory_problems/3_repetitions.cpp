#include <iostream>
using namespace std;

int main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string str;
    cin >> str;
    int n = str.length();

    long long max_len = 1;
    long long len = 1;

    for (int i = 1; i < n; i++)
    {
        if (str[i] == str[i - 1])
        {
            len += 1;
            max_len = max(max_len, len);
        }
        else
        {
            len = 1;
        }
    }

    cout << max_len;
}