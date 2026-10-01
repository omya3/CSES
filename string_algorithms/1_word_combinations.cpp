#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

struct Node
{
    // Fix: Modern C++ syntax to perfectly zero-initialize all 26 pointers to nullptr
    Node *links[26] = {};
    bool end = false;

    bool containsKey(char ch)
    {
        return (links[ch - 'a'] != nullptr);
    }

    void put(char ch, Node *node)
    {
        links[ch - 'a'] = node;
    }

    Node *get(char ch)
    {
        return links[ch - 'a'];
    }

    void setEnd(bool flag)
    {
        end = flag;
    }

    bool isEnd()
    {
        return end;
    }
};

class Trie
{
private:
    Node *root;

public:
    Trie()
    {
        root = new Node();
    }

    Node *getRoot()
    {
        return root;
    }

    void insert(string word)
    {
        Node *node = root;
        int n = word.size();

        for (int i = 0; i < n; i++)
        {
            if (!node->containsKey(word[i]))
            {
                node->put(word[i], new Node());
            }
            node = node->get(word[i]);
        }
        node->setEnd(true);
    }

    bool search(string word)
    {
        int n = word.size();
        Node *node = root;

        for (int i = 0; i < n; i++)
        {
            if (!node->containsKey(word[i]))
            {
                return false;
            }
            node = node->get(word[i]);
        }
        return node->isEnd();
    }

    bool startsWith(string prefix) // Standard practice: renamed 'word' to 'prefix'
    {
        int n = prefix.size();
        Node *node = root;

        for (int i = 0; i < n; i++)
        {
            if (!node->containsKey(prefix[i]))
            {
                return false;
            }
            node = node->get(prefix[i]);
        }
        return true;
    }
};

const int MOD = 1e9 + 7;

// 1. Added '&' to 'string &s' to pass by reference and avoid copying memory
int finder(int ind, const string &s, Trie &tr, vector<int> &dp)
{
    if (ind >= s.size())
        return 1;

    if (dp[ind] != -1)
        return dp[ind];

    int take = 0;
    Node *node = tr.getRoot();

    for (int i = ind; i < s.size(); i++)
    {
        if (!node->containsKey(s[i]))
            break;

        node = node->get(s[i]);
        if (node->isEnd())
        {
            take = (take + finder(i + 1, s, tr, dp)) % MOD;
        }
    }
    return dp[ind] = take;
}

int main()
{
    // 2. Added Fast I/O lines
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;
    int k;
    cin >> k;
    Trie tr;
    vector<int> dp(s.size(), -1);

    for (int i = 0; i < k; i++)
    {
        string p;
        cin >> p;
        tr.insert(p);
    }

    // 3. Print the output instead of just returning it from main
    cout << finder(0, s, tr, dp) << "\n";
    return 0;
}
