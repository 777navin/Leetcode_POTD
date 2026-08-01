/*
=========================================================
Date        : 01-08-2026
Problem Name: Predict the Winner
Platform    : LeetCode
Difficulty  : Medium
Tags        : Array, Math, Dynamic Programming, Recursion, Game Theory

Problem Summary:
Two players play a game with an array of numbers, taking turns to pick 
from either end. Each player adds the chosen number to their total score. 
Determine if Player 1 can guarantee a win or tie, assuming both play optimally.

Key Observation:
Since it's a zero-sum game, instead of tracking two separate scores, we 
can track the relative score difference (Player 1 score - Player 2 score).
=========================================================
*/

#include <vector>
#include <algorithm>

using namespace std;

/*
=========================================================
APPROACH 1: Pure Recursion (Brute Force)
=========================================================
• Intuition:
  Simulate every possible pick (left or right) for both players and 
  evaluate the maximum score difference Player 1 can achieve.

• Approach:
  A recursive function return max relative score difference for subarray nums[i..j].
  Player chooses max(nums[i] - solve(i+1, j), nums[j] - solve(i, j-1)).

• Why it Works:
  By subtracting the opponent's optimal gain from the current pick, we correctly 
  model the optimal strategy for both players.

• Time Complexity (TC) : O(2^n)
• Space Complexity (SC): O(n) - recursion call stack depth
*/

/*
=========================================================
APPROACH 2: Top-Down Dynamic Programming (Memoization)
=========================================================
• Intuition:
  The recursive approach recomputes results for the same subarray multiple times.
  Caching computed state results eliminates redundant work.

• Approach:
  Use a 2D memoization table memo[i][j] to store the maximum score difference for 
  the subarray nums[i..j].

• Why it Works:
  Overlapping subproblems are computed only once and retrieved in O(1) time.

• Time Complexity (TC) : O(n^2)
• Space Complexity (SC): O(n^2) - memoization table and stack space
*/

/*
=========================================================
APPROACH 3: Bottom-Up DP (1D Space Optimized)
=========================================================
• Intuition:
  Subarray lengths build up incrementally. State transition for length L only 
  depends on states of length L - 1, allowing 1D space compression.

• Approach:
  Iterate array from right to left and update a 1D DP table representing the 
  best score difference for subarrays starting at index i and ending at index j.

• Why it Works:
  Evaluates all base cases (length 1) and iteratively expands range to cover the 
  entire array using optimal state updates.

• Time Complexity (TC) : O(n^2)
• Space Complexity (SC): O(n) - 1D array space
*/

/*
=========================================================
FINAL APPROACH CHOICE
=========================================================
• Chosen Approach: Bottom-Up 1D Dynamic Programming.
• Why Chosen     : It avoids recursion overhead, achieves optimal O(n^2) time complexity,
                   and reduces memory usage to O(n) space complexity.
=========================================================
*/

class Solution {
public:
    bool predictTheWinner(vector<int>& nums) {
        int n = nums.size();
        
        // Arrays with an even number of elements can always be won/tied by Player 1
        if (n % 2 == 0) return true;

        vector<int> dp(n, 0);

        // Base cases and bottom-up DP computation
        for (int i = n - 1; i >= 0; i--) {
            dp[i] = nums[i];
            for (int j = i + 1; j < n; j++) {
                dp[j] = max(nums[i] - dp[j], nums[j] - dp[j - 1]);
            }
        }

        // Player 1 wins or ties if score difference is non-negative
        return dp[n - 1] >= 0;
    }
};
