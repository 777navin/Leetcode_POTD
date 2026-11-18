/*
=========================================================
Date        : 18-11-2026
Problem Name: 2914. Minimum Number of Changes to Make Binary String Beautiful
Platform    : LeetCode
Difficulty  : Medium
Tags        : String, Greedy

Problem Summary:
Given a 0-indexed binary string s of even length, partition it into one or more
substrings where each substring has an even length and contains only '0's or only '1's.
Return the minimum number of character flips needed to make such a partition possible.

Key Observation:
Any even-length uniform substring can be further divided into adjacent pairs of length 2.
Thus, the entire string is beautiful if and only if every adjacent pair (s[2i], s[2i+1]) is identical.
=========================================================
*/

/*
=========================================================
APPROACH 1: Dynamic Programming (Better)
=========================================================
• Intuition:
  We can decide at each even index whether to make the current length-2 block all '0's or all '1's,
  building up the minimum changes needed from left to right.

• Approach:
  Maintain dp[i] as the minimum changes required to make the prefix s[0...i-1] beautiful.
  For every step of 2, add the cost of making s[i] and s[i+1] equal (0 if same, 1 if different).

• Why it Works:
  Since any valid even-length partition decomposes into blocks of size 2, optimal subproblems
  at even boundaries combine independently without affecting adjacent blocks.

• Time Complexity (TC): O(N)
• Space Complexity (SC): O(N)
*/

/*
=========================================================
APPROACH 2: Greedy Pairwise Comparison (Most Optimal)
=========================================================
• Intuition:
  Each adjacent pair of characters (s[i], s[i+1]) at even indices i can be fixed independently
  without needing to store previous states.

• Approach:
  Iterate through the string with a step size of 2 (i = 0, 2, 4, ...).
  If s[i] != s[i+1], increment the change counter by 1.

• Why it Works:
  Every even-length uniform substring is a concatenation of identical pairs ("00" or "11").
  Fixing each mismatched pair with 1 flip guarantees a valid partition and is provably minimal.

• Time Complexity (TC): O(N)
• Space Complexity (SC): O(1)
*/

/*
=========================================================
FINAL APPROACH
=========================================================
Greedy Pairwise Comparison is chosen as the final solution.
It achieves optimal O(N) time complexity in a single pass while reducing auxiliary
space from O(N) to O(1) compared to Dynamic Programming, resulting in cleaner code.
=========================================================
*/

#include <string>

using namespace std;

class Solution {
public:
    int minChanges(string s) {
        int changes = 0;
        int n = s.length();

        // Check every disjoint adjacent pair of size 2
        for (int i = 0; i < n; i += 2) {
            if (s[i] != s[i + 1]) {
                changes++;
            }
        }

        return changes;
    }
};
