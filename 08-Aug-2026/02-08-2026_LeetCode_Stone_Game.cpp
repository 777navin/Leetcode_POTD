/*
=========================================================
Date        : 02-08-2026
Problem Name: Stone Game
Platform: LeetCode
Difficulty: Medium
Tags: Array, Math, Dynamic Programming, Game Theory

Problem Summary:
Alice and Bob take turns picking stone piles from either end of a row.
There are an even number of piles and an odd total number of stones.
The goal is to determine if Alice (the first player) can guarantee a win.

Key Observation:
Alice can always force a win by exclusively picking either all even-indexed or all odd-indexed piles.
=========================================================
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
1. Dynamic Programming
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition: Both players play optimally, so we need to calculate the maximum score difference.
• Approach: Define a 2D state dp[i][j] representing the max score difference for subarray piles[i..j].
            A player takes piles[i] (losing dp[i+1][j]) or piles[j] (losing dp[i][j-1]).
• Why it Works: It recursively evaluates all possible valid game states and optimal choices for both.
• Time Complexity (TC): O(N^2), where N is the number of piles.
• Space Complexity (SC): O(N^2), for the 2D DP table.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
2. Mathematical / Game Theory (Most Optimal)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition: The constraints (even number of piles, odd total stones) create a guaranteed winning strategy.
• Approach: Just return true.
• Why it Works: Alice can color piles as even or odd. Since the sum is odd, one group has a larger sum. 
                By picking the first pile, she forces Bob into the other group, ensuring she collects the larger sum.
• Time Complexity (TC): O(1)
• Space Complexity (SC): O(1)

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
FINAL APPROACH
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• The mathematical / game theory approach is chosen for the final code.
• It is O(1) time and space, completely bypassing the need for O(N^2) dynamic programming.
• It perfectly leverages the specific problem constraints where ties are impossible and piles are even.
*/

#include <vector>
using namespace std;

class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        // Since there is an even number of piles and an odd total sum,
        // Alice can always choose to take all even-indexed or all odd-indexed piles.
        // One of these sets will always have a greater sum, guaranteeing her win.
        return true;
    }
};
