/*
=========================================================
Date        : 10-11-2026
Problem Name: Climbing Stairs II
Platform    : LeetCode
Difficulty  : Medium
Tags        : Array, Dynamic Programming

Problem Summary:
- You are climbing a staircase with n + 1 steps numbered from 0 to n.
- You are given a 1-indexed costs array where costs[i] is the cost of step i.
- From step i, you can jump to i + 1, i + 2, or i + 3. The cost of a jump from i to j is costs[j] + (j - i)^2.
- Find the minimum total cost to reach step n starting from step 0 with cost 0.

Key Observation:
- The problem exhibits optimal substructure. State transitions only depend on the previous 3 steps (j - 1, j - 2, j - 3).
=========================================================
*/

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int climbStairs(int n, vector<int>& costs) {
        /*
        Final Approach: Dynamic Programming (Bottom-Up)
        
        • Why this approach is chosen:
          It avoids redundant overlapping recursive subproblems and computes the exact minimum cost efficiently in linear time.
          
        • Why it is better than the previous ones:
          Unlike pure recursion with memoization (which risks stack overflow or TLE) or brute force exponential exploration, 
          bottom-up DP runs in O(n) time and O(n) space.
          
        • Intuition:
          We can reach step j from previous steps i where j - 3 <= i < j. We want to minimize total cost.
          
        • Approach:
          - Define dp[j] as the minimum total cost to reach step j.
          - Initialize dp[0] = 0 and others to infinity.
          - For each step j from 1 to n, take the minimum over all valid previous states i from max(0, j - 3) to j - 1.
          
        • Why it Works:
          Subproblem solutions combine optimally to build the result for step n.
          
        • Time Complexity (TC): O(n)
        • Space Complexity (SC): O(n)
        */
        
        vector<long long> dp(n + 1, LLONG_MAX);
        dp[0] = 0;
        
        for (int j = 1; j <= n; ++j) {
            for (int i = max(0, j - 3); i < j; ++i) {
                long long jump_cost = costs[j - 1] + (long long)(j - i) * (j - i);
                if (dp[i] != LLONG_MAX) {
                    dp[j] = min(dp[j], dp[i] + jump_cost);
                }
            }
        }
        
        return dp[n];
    }
};
