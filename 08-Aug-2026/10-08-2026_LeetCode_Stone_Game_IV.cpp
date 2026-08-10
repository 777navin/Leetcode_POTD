/*
=========================================================
Date        : 10-08-2026
Problem Name: Stone Game IV
Platform: LeetCode
Difficulty: Hard
Tags: Math, Dynamic Programming, Game Theory

Problem Summary:
Given 'n' stones, Alice and Bob take turns removing a non-zero square number of stones.
The player who cannot make a move loses. Return true if Alice wins playing optimally.

Key Observation:
A player wins if they can reach a state where the other player is forced into a losing state.
We can use Dynamic Programming to precalculate the winning/losing state for every number of stones up to 'n'.
=========================================================
*/

/*
APPROACH 1: DFS with Memoization (Top-Down DP)
- Intuition: At any state 'i', try removing all possible square numbers (1, 4, 9, ...). If any move leaves the opponent in a losing state, the current state is a winning state.
- Approach: Recursively check states. Cache the results in an array to avoid redundant calculations.
- Why it Works: Both players play optimally, so finding at least one losing state for the opponent guarantees a win.
- Time Complexity (TC): O(N * sqrt(N)) since for each state 'i', we iterate up to sqrt(i).
- Space Complexity (SC): O(N) for the recursion stack and memoization array.

APPROACH 2: Tabulation (Bottom-Up DP)
- Intuition: Instead of recursion, we can iteratively build up the results from 0 stones up to 'n' stones.
- Approach: Use a boolean DP array where dp[i] is true if the player starting with 'i' stones wins. For each 'i', check if there is some k*k <= i such that dp[i - k*k] is false.
- Why it Works: It strictly computes smaller subproblems first, completely eliminating recursion overhead.
- Time Complexity (TC): O(N * sqrt(N)).
- Space Complexity (SC): O(N) for the DP array.

FINAL APPROACH:
- The Bottom-Up DP (Tabulation) approach is chosen as the final implementation.
- It is better than the Top-Down DFS because it avoids recursion stack overhead and potential deep recursion limits, leading to faster execution and constant space for the call stack.
*/

#include <vector>

using namespace std;

class Solution {
public:
    bool winnerSquareGame(int n) {
        // dp[i] will be true if the current player can win starting with i stones
        vector<bool> dp(n + 1, false);
        
        for (int i = 1; i <= n; i++) {
            // Check all possible square numbers we can remove
            for (int k = 1; k * k <= i; k++) {
                // If there's a move that leaves the opponent in a losing state, we win
                if (!dp[i - k * k]) {
                    dp[i] = true;
                    break;
                }
            }
        }
        
        return dp[n];
    }
};
