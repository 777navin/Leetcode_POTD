/*
=========================================================
Date        : 27-08-2026
Problem Name: 3720. Lexicographically Smallest Permutation Greater Than Target
Platform    : LeetCode
Difficulty  : Medium
Tags        : Hash Table, String, Greedy, Counting, Enumeration

Problem Summary:
Given two lowercase English strings s and target of equal length n,
find the lexicographically smallest permutation of s that is strictly
greater than target. If no such permutation exists, return "".

Key Observation:
To make the permutation strictly greater than target while keeping it minimal,
we must share the longest possible prefix with target, place a strictly larger
character at the first diverging position, and sort the remaining characters ascendingly.
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Brute Force (Next Permutations)
---------------------------------------------------------
• Intuition:
  Generate all unique permutations of s in sorted order and pick the first one strictly greater than target.
• Approach:
  Sort string s, then repeatedly use next_permutation to generate strings and compare with target.
• Why it Works:
  It systematically checks every permutation in ascending lexicographical order.
• Time Complexity: O(N! * N) — completely infeasible for N up to 300.
• Space Complexity: O(1) auxiliary space beyond storage.

---------------------------------------------------------
APPROACH 2: Greedy Prefix Matching with Backtracking (Optimal)
---------------------------------------------------------
• Intuition:
  Try to match a prefix of length L (from n down to 0) identical to target. At index L, place the smallest
  available character strictly greater than target[L], and fill the rest (L+1 to n-1) with remaining characters in ascending order.
• Approach:
  1. Count total character frequencies of s.
  2. First, verify if matching an exact prefix up to index i is feasible using character frequency counts.
  3. Iterate i from n - 1 down to 0 (the divergence point):
     - Check if we have an available character c > target[i].
     - If so, place c at index i, use the prefix target[0...i-1], and append remaining characters in sorted order.
     - This gives the valid permutation with the longest matching prefix (which guarantees it's minimal).
  4. If no such valid split index i exists, return "".
• Why it Works:
  Maximizing the common prefix with target guarantees minimal lexicographical value. Choosing the smallest valid greater character at the split index and sorting the suffix ensures optimal minimality.
• Time Complexity: O(N * 26) = O(N) where N <= 300.
• Space Complexity: O(26) = O(1) auxiliary space.
---------------------------------------------------------
*/

/*
=========================================================
FINAL APPROACH: Greedy Prefix Matching with Backtracking
=========================================================
• We choose this approach because N <= 300 makes O(N!) impossible, while O(N * 26) runs in < 1ms.
• It directly constructs the optimal answer without exploring invalid permutations.
*/

#include <string>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.length();
        vector<int> total_freq(26, 0);
        for (char c : s) {
            total_freq[c - 'a']++;
        }

        // Check if a full identical prefix exists up to each length
        // pref_count[i] stores available characters after matching target[0...i-1]
        vector<vector<int>> pref_freq(n + 1, vector<int>(26, 0));
        pref_freq[0] = total_freq;

        int match_len = 0;
        for (int i = 0; i < n; i++) {
            int ch = target[i] - 'a';
            if (pref_freq[i][ch] > 0) {
                pref_freq[i + 1] = pref_freq[i];
                pref_freq[i + 1][ch]--;
                match_len++;
            } else {
                break;
            }
        }

        // Iterate from the maximum possible split point down to 0
        for (int i = match_len; i >= 0; i--) {
            if (i == n) {
                // If it completely matches target, we cannot make it strictly greater without diverging earlier
                continue;
            }

            int target_char = target[i] - 'a';
            // Find the smallest character strictly greater than target[i]
            for (int c = target_char + 1; c < 26; c++) {
                if (pref_freq[i][c] > 0) {
                    // Valid split found at index i with character c
                    string result = target.substr(0, i);
                    result.push_back((char)('a' + c));

                    vector<int> rem = pref_freq[i];
                    rem[c]--;

                    // Append all remaining characters in ascending order
                    for (int ch = 0; ch < 26; ch++) {
                        while (rem[ch] > 0) {
                            result.push_back((char)('a' + ch));
                            rem[ch]--;
                        }
                    }
                    return result;
                }
            }
        }

        return "";
    }
};
