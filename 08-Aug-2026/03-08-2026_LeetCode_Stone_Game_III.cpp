#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/*
=========================================================
Date        : 03-08-2026
Problem Name: 1406. Stone Game III
Platform    : LeetCode
Difficulty  : Hard
Tags        : Array, Math, Dynamic Programming, Game Theory

Problem Summary:
- Alice and Bob take 1, 2, or 3 stones from the front of a row.
- They play optimally to maximize their respective scores.
- Determine if Alice wins, Bob wins, or if it is a Tie.

Key Observation:
- This is a zero-sum game. The current player's objective is to maximize their collected score minus the opponent's future maximum relative score.
=========================================================

1. Top-Down DP (Memoization)
- Intuition: At each step, a player has up to 3 choices. We calculate the max relative score difference for each.
- Approach: Use a recursive function with memoization `dp[i]` tracking the max difference starting from index `i`.
- Why it Works: It comprehensively explores all valid moves and caches overlapping subproblems optimally.
- Time Complexity (TC): O(N), as each index is evaluated once with at most 3 transitions.
- Space Complexity (SC): O(N) due to the recursion stack and memoization array.

2. Bottom-Up DP (Tabulation)
- Intuition: Eliminate recursion overhead by calculating from the end of the array to the start.
- Approach: Use a `dp` array where `dp[i]` is the max relative score from index `i`.
- Why it Works: Base case is `dp[n] = 0`. We iterate backward, checking picks of 1, 2, or 3 stones.
- Time Complexity (TC): O(N), consisting of a single loop with 3 inner steps.
- Space Complexity (SC): O(N), to maintain the `dp` array for all states.

3. Space-Optimized DP (Most Optimal)
- Intuition: To calculate `dp[i]`, we strictly only need the states of `dp[i+1]`, `dp[i+2]`, and `dp[i+3]`.
- Approach: Instead of an array of size N, use 3 variables to track the last 3 states.
- Why it Works: It preserves the tabulation logic but discards unneeded historical data.
- Time Complexity (TC): O(N), iterating exactly N times.
- Space Complexity (SC): O(1), utilizing only a few constant tracking variables.

=========================================================
FINAL APPROACH
- We use the Space-Optimized DP (Approach 3).
- It is chosen because it achieves O(N) time with O(1) space, avoiding overhead and large array allocations.
- It strictly dominates the prior approaches by being the most optimal for memory in competitive programming.
=========================================================
*/

class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {
        int n = stoneValue.size();
        
        // Track the relative scores of the next 3 steps.
        int dp1 = 0, dp2 = 0, dp3 = 0;
        
        for (int i = n - 1; i >= 0; --i) {
            int take = 0;
            int best = -1e9; // Treat as negative infinity
            
            for (int k = 0; k < 3 && i + k < n; ++k) {
                take += stoneValue[i + k];
                
                // Identify opponent's score based on k stones taken
                int opponent_score = (k == 0) ? dp1 : (k == 1) ? dp2 : dp3;
                best = max(best, take - opponent_score);
            }
            
            // Shift the state window down
            dp3 = dp2;
            dp2 = dp1;
            dp1 = best;
        }
        
        if (dp1 > 0) return "Alice";
        if (dp1 < 0) return "Bob";
        return "Tie";
    }
};

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    Solution sol;
    
    vector<int> stoneValue1 = {1, 2, 3, 7};
    cout << "Example 1: " << sol.stoneGameIII(stoneValue1) << "\n";
    
    vector<int> stoneValue2 = {1, 2, 3, -9};
    cout << "Example 2: " << sol.stoneGameIII(stoneValue2) << "\n";
    
    vector<int> stoneValue3 = {1, 2, 3, 6};
    cout << "Example 3: " << sol.stoneGameIII(stoneValue3) << "\n";
    
    return 0;
}
