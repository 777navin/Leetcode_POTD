/*
=========================================================
Date        : 06-09-2026
Problem Name: Distinct Subsequences
Platform    : LeetCode
Difficulty  : Hard
Tags        : String, Dynamic Programming

Problem Summary:
Given two strings s and t, return the number of distinct subsequences
of s that equal t. The result is guaranteed to fit inside a 32-bit
signed integer.

Key Observation:
For each character match s[i - 1] == t[j - 1], we can either include
it in matching t[j - 1] or ignore it and find t[j - 1] in the prefix
of s. If they do not match, we must ignore s[i - 1].
=========================================================
*/

/*
APPROACH 1: Recursive with Memoization (Top-Down DP)
• Intuition:
  - Try matching from left-to-right (or right-to-left); if characters match,
    we branch into two choices: take or skip. If they don't, skip.
• Approach:
  - Define memo(i, j) as ways to form t[j...] using s[i...].
  - Transition: memo(i, j) = memo(i + 1, j) + (s[i] == t[j] ? memo(i + 1, j + 1) : 0).
• Why it Works:
  - Explores all valid subsequence index combinations while caching overlapping subproblems.
• Time Complexity (TC) : O(M * N), where M = s.length() and N = t.length().
• Space Complexity (SC): O(M * N) for the DP table + O(M + N) recursion call stack.

APPROACH 2: 2D Dynamic Programming (Bottom-Up)
• Intuition:
  - Iteratively compute subproblem results starting from base cases of empty strings.
• Approach:
  - Let dp[i][j] be the number of distinct subsequences of s[0...i-1] equal to t[0...j-1].
  - Base case: dp[i][0] = 1 (empty t can always be formed once).
  - If s[i - 1] == t[j - 1]: dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j].
  - Else: dp[i][j] = dp[i - 1][j].
• Why it Works:
  - Systematically builds up answers without recursion stack overhead.
• Time Complexity (TC) : O(M * N).
• Space Complexity (SC): O(M * N) for the 2D table.

APPROACH 3: 1D Space-Optimized Dynamic Programming (Most Optimal)
• Intuition:
  - Notice dp[i][j] only depends on values from the previous row dp[i - 1].
• Approach:
  - Compress the table into a single 1D array dp of size N + 1, with dp[0] = 1.
  - Traverse s from left to right, and update dp backwards from N down to 1.
  - If s[i - 1] == t[j - 1], dp[j] += dp[j - 1].
• Why it Works:
  - Iterating backwards ensures dp[j - 1] represents the state from the previous row
    before being overwritten in the current iteration.
• Time Complexity (TC) : O(M * N).
• Space Complexity (SC): O(N) space, where N = t.length().
*/

/*
FINAL APPROACH: 1D Space-Optimized DP
• Chosen because it runs in optimal O(M * N) time while reducing memory to O(N).
• Iterating j backwards avoids copying previous rows, minimizing memory footprint and cache misses.
• Uses an unsigned type internally to prevent intermediate signed overflow before modulo/casting.
*/

#include <string>
#include <vector>

class Solution {
public:
    int numDistinct(std::string s, std::string t) {
        int m = s.length();
        int n = t.length();

        if (m < n) {
            return 0;
        }

        // dp[j] stores the count of distinct subsequences of s that form t[0...j-1]
        // Use unsigned long long to safely avoid intermediate 32-bit overflow
        std::vector<unsigned long long> dp(n + 1, 0);
        dp[0] = 1;

        for (int i = 1; i <= m; ++i) {
            for (int j = n; j >= 1; --j) {
                if (s[i - 1] == t[j - 1]) {
                    dp[j] += dp[j - 1];
                }
            }
        }

        return static_cast<int>(dp[n]);
    }
};
