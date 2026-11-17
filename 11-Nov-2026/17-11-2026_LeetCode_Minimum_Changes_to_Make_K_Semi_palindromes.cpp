/*
=========================================================
Date        : 17-11-2026
Problem Name: 2911. Minimum Changes to Make K Semi-palindromes
Platform    : LeetCode
Difficulty  : Hard
Tags        : String, Dynamic Programming, Two Pointers

Problem Summary:
Given a lowercase string s and an integer k, partition s into k non-empty
contiguous substrings such that the total character replacements needed to
turn every substring into a semi-palindrome is minimized.
A string of length L > 1 is a semi-palindrome if there exists a proper divisor
d (1 <= d < L, L % d == 0) such that every subsequence at indices
i, i + d, i + 2d, ... (for 0 <= i < d) forms a palindrome.

Key Observation:
Since n <= 200, we can precompute the minimum changes cost[i][j] to make
every substring s[i..j] a semi-palindrome by testing all proper divisors d
of its length, and then use 2D DP to partition the string into k parts.
=========================================================
*/

/*
---------------------------------------------------------
1. Brute Force (Recursive Partitioning + On-the-Fly Cost)
---------------------------------------------------------
* Intuition:
  Try every possible valid split point to break the string into k substrings
  and compute the semi-palindrome conversion cost for each piece directly.
* Approach:
  Use recursion f(idx, rem_k) trying all end positions j >= idx + 1. For each
  substring s[idx..j], iterate over all proper divisors d of length L and sum
  the mismatches across all d residue classes.
* Why it Works:
  Exhaustively evaluates all valid k-partitions and picks the global minimum
  total cost, guaranteeing correctness.
* Time Complexity (TC):
  O(C(n, k) * n * tau(n)), exponential due to overlapping subproblems.
* Space Complexity (SC):
  O(k) for the recursion call stack.

---------------------------------------------------------
2. Better (Top-Down Memoization + On-the-Fly Cost)
---------------------------------------------------------
* Intuition:
  The state (start_index, remaining_parts) repeats heavily across different
  prefix choices, so caching subproblem results eliminates redundant branching.
* Approach:
  Memoize dp[idx][rem_k] in a 2D table while still computing the semi-palindrome
  cost of s[idx..j] inside the transition loop.
* Why it Works:
  There are only O(n * k) unique DP states, avoiding exponential re-evaluation
  of identical suffix partitions.
* Time Complexity (TC):
  O(n^2 * k * n * tau(n)) = O(n^3 * k * tau(n)), where tau(n) <= 16 for n <= 200.
* Space Complexity (SC):
  O(n * k) for the memoization table.

---------------------------------------------------------
3. Most Optimal (Precomputed Substring Cost + Bottom-Up DP)
---------------------------------------------------------
* Intuition:
  Decouple substring semi-palindrome cost evaluation from the k-partitioning DP
  so each substring's cost is calculated once instead of k times.
* Approach:
  Step 1: Precompute divisors for all lengths 2..n.
  Step 2: Compute cost[i][j] for all 0 <= i < j < n by iterating over proper
          divisors d of (j - i + 1) and counting palindrome mismatches per group.
  Step 3: Run bottom-up DP where dp[parts][end] = min(dp[parts - 1][prev] +
          cost[prev + 1][end]) for all valid split points.
* Why it Works:
  Precomputing cost[i][j] reduces the DP transition to O(1) lookup, and bottom-up
  iteration avoids recursion overhead while strictly enforcing length >= 2 per part.
* Time Complexity (TC):
  O(n^3 * tau(n) + n^2 * k), where n <= 200 and tau(n) <= 16 (~1.2 * 10^8 max ops,
  < 30ms in C++).
* Space Complexity (SC):
  O(n^2) to store the precomputed cost table and DP states.
---------------------------------------------------------
*/

/*
=========================================================
FINAL APPROACH
=========================================================
We choose the Precomputed Substring Cost + Bottom-Up DP approach because it
separates the O(n^3 * tau(n)) string cost calculation from the O(n^2 * k)
partitioning phase. Unlike recursive or non-precomputed DP solutions, each
substring's semi-palindrome cost is evaluated strictly once, easily passing
within strict time limits for n <= 200 with clean O(n^2) memory.
=========================================================
*/

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = static_cast<int>(s.size());
        const int INF = 1e9;

        // 1. Precompute all proper divisors d (1 <= d < len) for every length 2..n
        vector<vector<int>> divisors(n + 1);
        for (int len = 2; len <= n; ++len) {
            for (int d = 1; d * 2 <= len; ++d) {
                if (len % d == 0) {
                    divisors[len].push_back(d);
                }
            }
        }

        // 2. Precompute min changes cost[i][j] to make s[i..j] a semi-palindrome
        // Note: Single characters (len == 1) cannot be semi-palindromes.
        vector<vector<int>> cost(n, vector<int>(n, INF));
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int len = j - i + 1;
                int min_changes = INF;

                for (int d : divisors[len]) {
                    int changes = 0;
                    // Check each of the d arithmetic progression groups
                    for (int offset = 0; offset < d; ++offset) {
                        int left = i + offset;
                        // Last element in this group within s[i..j]
                        int right = i + offset + ((len - 1 - offset) / d) * d;
                        while (left < right) {
                            if (s[left] != s[right]) {
                                ++changes;
                            }
                            left += d;
                            right -= d;
                        }
                    }
                    min_changes = min(min_changes, changes);
                }
                cost[i][j] = min_changes;
            }
        }

        // 3. Bottom-Up DP: dp[parts][j] = min changes to partition s[0..j] into 'parts' substrings
        vector<vector<int>> dp(k + 1, vector<int>(n, INF));

        // Base case: 1 partition covering prefix s[0..j]
        for (int j = 1; j < n; ++j) {
            dp[1][j] = cost[0][j];
        }

        // Transition for 2..k partitions
        for (int parts = 2; parts <= k; ++parts) {
            // Each partition needs at least 2 characters, so j >= 2 * parts - 1
            for (int j = 2 * parts - 1; j < n; ++j) {
                // Previous parts cover s[0..p], current part covers s[p+1..j]
                for (int p = 2 * (parts - 1) - 1; p <= j - 2; ++p) {
                    if (dp[parts - 1][p] != INF && cost[p + 1][j] != INF) {
                        dp[parts][j] = min(dp[parts][j], dp[parts - 1][p] + cost[p + 1][j]);
                    }
                }
            }
        }

        return dp[k][n - 1];
    }
};
