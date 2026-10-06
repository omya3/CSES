#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/**
 * Extracts the longest contiguous palindromic substring using Manacher's Algorithm.
 * Time Complexity:  O(N) - Linear time because right boundary R increases monotonically.
 * Space Complexity: O(N) - To store the interleaved transformed string and the radius array.
 */
string longest_palindromic_substring(string &s)
{
    // Edge Case: An empty string contains no palindromes
    if (s.empty())
        return "";

    // L and R define the active bounding box [L, R] of the rightmost expanding palindrome found so far.
    // They are absolute index boundaries in our transformed string `s_new`.
    int L = 0;
    int R = 0;

    // 1. STRING TRANSFORMATION (Parity Uniformity)
    // We interleave the string with '#' characters so that both odd-length ("aba")
    // and even-length ("abba") palindromes map to an odd-length structure with a clear central index.
    // We add unique sentinels '^' at the start and '\$' at the end. Because '^' != '\$' != '#',
    // the outward expansion loop terminates naturally at the boundaries without needing manual index checks.
    // Example: If s = "babad", s_new becomes "^#b#a#b#a#d#\$"
    string s_new = "^#";
    for (auto it : s)
    {
        s_new += it;
        s_new += '#';
    }
    s_new += "\$";
    int n = s_new.size();

    // man_box[i] tracks the exact palindromic radius centered at index `i` inside `s_new`.
    // Beautiful Math Property: The radius in `s_new` is EXACTLY equal to the length of that palindrome in `s`.
    vector<int> man_box(n, 0);

    int max_rad = 0; // Tracks the maximum radius (length) discovered across the entire run
    int max_i = 0;   // Tracks the center index of that longest palindrome inside `s_new`

    // 2. MAIN LINEAR PROCESSING LOOP
    // We skip index 0 ('^') and index n-1 ('\$') since they are out-of-bounds sentinels.
    for (int i = 1; i < n - 1; i++)
    {
        // CASE A: The current index `i` falls completely inside our known rightmost palindromic window [L, R]
        if (i <= R)
        {
            // Find the symmetrical reflection point of `i` inside the current [L, R] box.
            // Mathematical Derivation:
            // Distance from left edge to mirror equals distance from i to right edge.
            // mirror - L = R - i  ==>  mirror = L + R - i
            int mirror = L + R - i;

            // Mirror Symmetry Optimization:
            // We initialize man_box[i] using values we already calculated.
            // It is bounded by the distance remaining to our known right boundary (R - i).
            // max(0, ...) acts as a defensive floor to guarantee radii never dip below 0.
            man_box[i] = max(0, min(R - i, man_box[mirror]));
        }

        // 3. OUTWARD LINEAR EXPANSION CHECK
        // (1 + man_box[i]) is simply our "Adjusted Look-Ahead Index Offset".
        // It calculates how far out from the center we need to test.
        // As man_box[i] increments by 1, the offset automatically progresses (e.g., 1, 2, 3...)
        // Checking every single character position sequentially without skipping anything.
        // It naturally toggles: Center (Text) -> Offset 1 (#) -> Offset 2 (Text) -> Offset 3 (#)
        while (s_new[i - (1 + man_box[i])] == s_new[i + (1 + man_box[i])])
        {
            man_box[i] += 1; // Valid matching pair found! Expand radius counter by 1.
        }

        // 4. BOUNDING BOX WINDOW SHIFTING
        // If the palindrome centered at `i` extends beyond our global right boundary `R`,
        // we shift our active [L, R] window forward to align with this newly extended palindrome.
        if (i + man_box[i] > R)
        {
            L = i - man_box[i]; // Update absolute Left boundary
            R = i + man_box[i]; // Update absolute Right boundary
        }

        // Global Max Update: Track the maximum palindrome information on-the-fly
        if (man_box[i] > max_rad)
        {
            max_rad = man_box[i];
            max_i = i;
        }
    }

    // 5. INDEX RECONVERSION MAPPING
    // Converts the transformed `s_new` coordinate domain back to the original string `s` space.
    // Step-by-Step Translation Logic:
    // Left edge of palindrome in s_new = max_i - max_rad
    // Adjusting for leading sentinel '^' shift (+1) to find first real text index: (max_i - max_rad) + 1
    // Because s_new is expanded 2x by hashes, original index relation follows: s_new_idx = 2 * s_idx + 2
    // Rearranging to isolate s_idx: s_idx = (s_new_idx - 2) / 2
    // Substituting our first real index: start_index = ((max_i - max_rad + 1) - 2) / 2
    // Which simplifies cleanly to: (max_i - max_rad - 1) / 2
    int start_index = (max_i - max_rad - 1) / 2;

    // s.substr(starting_position, length_of_substring)
    // Remember: max_rad perfectly equals the length of the palindrome in the original string!
    return s.substr(start_index, max_rad);
}

int main()
{
    // Fast I/O Optimization for Competitive Programming environments
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (cin >> s)
    {
        string longest_palindrome = longest_palindromic_substring(s);
        cout << "Longest Palindrome: " << longest_palindrome << "\n";
    }
    return 0;
}
