/*
=========================================================
Date        : 09-08-2026
Problem Name: Stone Game II
Platform    : LeetCode
Difficulty  : Medium
Tags        : Array, Math, Dynamic Programming, Minimax, Prefix Sum, Game Theory

Problem Summary:
Alice and Bob take turns picking stones from a sequence of piles. 
On each turn, a player can pick up to 2M piles, starting with M=1. 
M then updates to max(M, X), where X is the number of piles picked.
Find the maximum number of stones Alice can get if both play optimally.

Key Observation:
In this zero-sum game, maximizing a player's score is equivalent to 
taking the total available remaining stones and subtracting the 
maximum score the opponent can get from the next state.
=========================================================
*/

/*
=========================================================
APPROACH 1: Recursion (Brute Force)
=========================================================
• Intuition: 
  Explore all possible valid moves (1 to 2M piles) for the current player.
• Approach: 
  Use a recursive function that tracks the current index and M. 
  Try taking X piles and assume the opponent also plays optimally.
• Why it Works: 
  It simulates every possible game state and outcome step-by-step.
• Time Complexity (TC): 
  O(2^N) - Exponential time as it recalculates overlapping subproblems.
• Space Complexity (SC): 
  O(N) - Recursion stack depth can go up to N.

=========================================================
APPROACH 2: Dynamic Programming with Memoization (Most Optimal)
=========================================================
• Intuition: 
  The recursive brute force visits the same (index, M) states repeatedly. 
  We can cache these results to avoid redundant calculations.
• Approach: 
  Use a 2D DP array `dp[i][m]` to store the max stones a player can get 
  starting at index `i` with a given `m`. Use a suffix sum array to 
  quickly find the total remaining stones from index `i` to the end.
• Why it Works: 
  Memoization prevents duplicate work, drastically reducing the search space. 
  The suffix sum allows O(1) calculation of total available stones.
• Time Complexity (TC): 
  O(N^3) - There are N * N states, and for each state, we run a loop up to 2M (which is <= 2N).
• Space Complexity (SC): 
  O(N^2) - We need an N x N DP table and an N-sized suffix sum array.
*/

/*
=========================================================
FINAL APPROACH CHOSEN: Dynamic Programming with Memoization
=========================================================
• This approach is chosen because the constraints allow an O(N^3) solution.
• It drastically optimizes the exponential brute force by utilizing caching.
• Using suffix sums avoids the need for an inner loop to calculate stones taken.
*/

#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();
        
        // Suffix sum array to quickly calculate stones remaining from index i to the end
        vector<int> suffixSum(n);
        suffixSum[n - 1] = piles[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            suffixSum[i] = suffixSum[i + 1] + piles[i];
        }

        // dp[i][m] stores the maximum stones a player can get starting at index i with current M = m
        // We cap M at N because taking more than N piles is impossible anyway.
        vector<vector<int>> dp(n, vector<int>(n + 1, 0));

        // Recursive lambda with memoization
        function<int(int, int)> solve = [&](int i, int m) -> int {
            // Base Case: No more piles left
            if (i >= n) return 0;
            
            // Base Case: If the player can take all remaining piles, they should take them all
            if (i + 2 * m >= n) return suffixSum[i];
            
            // Return cached result if already calculated
            if (dp[i][m] != 0) return dp[i][m];

            int maxStones = 0;
            
            // Try all possible valid moves (taking X piles, where 1 <= X <= 2M)
            for (int x = 1; x <= 2 * m; ++x) {
                // The current player gets all remaining stones from index 'i' MINUS 
                // what the next player will optimally get starting from index 'i + x'.
                int nextM = max(m, x);
                maxStones = max(maxStones, suffixSum[i] - solve(i + x, nextM));
            }
            
            return dp[i][m] = maxStones;
        };

        // Start the game from index 0 with initial M = 1
        return solve(0, 1);
    }
};
