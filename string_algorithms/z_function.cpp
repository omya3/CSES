#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
private:
    // This helper function creates the Z-array.
    // z[i] stores the length of the longest substring starting at index 'i'
    // that matches the prefix (the very beginning) of the string.
    vector<int> zfunction(string txt)
    {
        int l = 0, r = 0; // [l, r] defines our active "Z-box" window.
                          // It represents the rightmost substring we have already matched with the prefix.
        int n = txt.length();
        vector<int> z(n); // z[0] is always left as 0 because a string matching itself isn't a subsegment.

        for (int i = 1; i < n; i++)
        {
            // --- BLOCK 1: THE SMART LOOK-BACK ---
            // If true, we are INSIDE the active window [l, r]. We can borrow old data!
            // Example: If txt = "ababac" and we are at i=2 (the second 'a'), l=0, r=3.
            // Since i <= r (2 <= 3), we are inside the box and don't need to rebuild from scratch.
            if (i <= r)
            {
                int k = i - l; // 'k' is the relative "mirror position" at the front of the string.
                               // If i=2 and l=0, then k = 2 - 0 = 2. We copy information from z[2].

                // We take the minimum because we can only safely trust data inside our current window.
                // r - i + 1 is the remaining space left in the box.
                z[i] = min(r - i + 1, z[k]);
            }

            // --- BLOCK 2: THE BRUTE-FORCE CHECKER ---
            // This while loop handles character comparisons. It acts in two situations:
            // 1. We were outside the box (i > r), so we must check from scratch.
            // 2. We were inside the box, but the look-back value z[k] hit the edge of the window boundary (r).
            //    This loop steps OUTSIDE the window to see if the match continues further right.
            // Example: txt[z[i]] matches the prefix pointer, txt[i + z[i]] matches our current trailing pointer.
            while (i + z[i] < n && txt[z[i]] == txt[i + z[i]])
            {
                z[i] += 1;
            }

            // --- BLOCK 3: THE WINDOW UPDATER ---
            // If the match starting at index 'i' stretched out further right than our current boundary 'r',
            // we shift our Z-box window to align with this new furthest-right zone.
            // Example: If i=4 and z[i]=3, the match stretches up to index: 4 + 3 - 1 = 6.
            // If our old r was 3, since 6 > 3, our new window snaps to l=4, r=6.
            if (i + z[i] - 1 > r)
            {
                l = i;
                r = i + z[i] - 1;
            }
        }
        return z;
    }

public:
    // Main function to search for a pattern inside a text.
    vector<int> search(string &pat, string &txt)
    {
        // We concatenate pattern + unique delimiter + text.
        // Example: pat = "abc", txt = "xabc" -> s = "abc$xabc"
        string s = pat + "$" + txt;
        vector<int> z = zfunction(s);
        vector<int> pos;

        int m = pat.size();

        // We start scanning 'z' right after the pattern and the '$' character.
        // In "abc$xabc", the pattern is length 3, '$' is at index 3, text starts at index 4 (m + 1).
        for (int i = m + 1; i < z.size(); i++)
        {
            // If z[i] equals the pattern length 'm', it means a perfect match of the pattern
            // starts at this exact position in the concatenated string!
            if (z[i] == m)
            {
                // We convert the index from the combined string 's' back to the original index in 'txt'.
                // Formula: current_index - pattern_length - 1 (for the '$' delimiter).
                // Example: If match is found at i=4 and m=3: 4 - 3 - 1 = 0. The match is at index 0 of txt.
                pos.push_back(i - m - 1);
            }
        }

        // Return the vector holding all starting indices where the pattern was found.
        return pos;
    }
};
