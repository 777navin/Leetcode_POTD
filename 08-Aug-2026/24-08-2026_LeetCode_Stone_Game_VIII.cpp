/*
=========================================================
Date        : 24-08-2026
Problem Name: 1872. Stone Game VIII
Platform    : LeetCode
Difficulty  : Hard
Tags        : Array, Math, Dynamic Programming, Prefix Sum, Game Theory

Problem Summary:
Alice and Bob play a turn-based game removing the leftmost x (x > 1) stones.
The player adds the sum of removed stones to their score and places a new stone with that sum on the left.
Both play optimally; Alice wants to maximize (Alice - Bob) score difference, and Bob wants to minimize it.

Key Observation:
Replacing prefix elements with their sum means any move to index i gives a score equal to prefix_sum[i], 
leaving the next player to pick from index j > i on the exact same prefix sums.
=========================================================
*/

#include <vector>
#include <numeric>
#include <algorithm>

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH EXPLANATION
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

1. Top-Down Dynamic Programming (Memoization)
• Intuition:
  - Any player picking up to index i gains prefix[i] and leaves the opponent to maximize their difference from i + 1 to n - 1.
• Approach:
  - Let dp(i) be the max score difference a player can get starting choice from index i.
  - At each index i, player can take stone i (gaining prefix[i] - dp(i + 1)) or skip to i + 1 (getting dp(i + 1)).
• Why it Works:
  - Game theory zero-sum structure ensures optimal alternating play over remaining choices.
• Time Complexity (TC): O(N)
• Space Complexity (SC): O(N) due to recursion stack and memo table.

2. Bottom-Up Dynamic Programming (Space-Optimized) - [Most Optimal]
• Intuition:
  - dp[i] only depends on dp[i + 1], allowing backward transition with a single variable.
• Approach:
  - Compute prefix sums in-place.
  - Base case: at the last index n - 1, the player has no further choices, so dp = prefix[n - 1].
  - Iterate backwards from n - 2 down to 1: dp = max(dp, prefix[i] - dp).
• Why it Works:
  - Correctly propagates the optimal decision at each step while eliminating array allocations.
• Time Complexity (TC): O(N)
• Space Complexity (SC): O(1) auxiliary space (in-place modification).
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
FINAL APPROACH
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Bottom-Up Space-Optimized DP is selected.
• It computes the answer in a single backward pass after in-place prefix summation.
• Achieves optimal O(N) time and O(1) auxiliary space without recursion overhead.
*/

class Solution {
public:
    int stoneGameVIII(std::vector<int>& stones) {
        int n = stones.size();
        
        // Compute prefix sums in-place
        for (int i = 1; i < n; ++i) {
            stones[i] += stones[i - 1];
        }
        
        // Base case: at index n - 1, must take all stones
        int max_diff = stones[n - 1];
        
        // Iterate backwards to find the optimal decision for each state
        for (int i = n - 2; i > 0; --i) {
            max_diff = std::max(max_diff, stones[i] - max_diff);
        }
        
        return max_diff;
    }
};
