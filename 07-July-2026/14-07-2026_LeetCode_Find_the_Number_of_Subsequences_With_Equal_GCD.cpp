/*
=========================================================
Date        : 14-07-2026
Problem Name: Find the Number of Subsequences With Equal GCD
Platform    : LeetCode
Difficulty  : Hard
Tags        : Array, Math, Dynamic Programming, Number Theory

Problem Summary:
Given an array `nums`, find the number of pairs of non-empty, index-disjoint
subsequences (seq1, seq2) such that the Greatest Common Divisor (GCD) of 
the elements in seq1 equals the GCD of the elements in seq2. Return the 
answer modulo 10^9 + 7.

Key Observation:
Since the length of the array and the maximum value of any element are both 
bounded by 200, we can use Dynamic Programming to track the current index 
and the running GCDs of both subsequences.
=========================================================
*/

#include <vector>
#include <numeric>
#include <cstring>

using namespace std;

/*
---------------------------------------------------------
Approach 1: 3D Dynamic Programming (Take/Skip DP)
---------------------------------------------------------
• Intuition:
  For each element in the array, we have three choices: include it in the first 
  subsequence, include it in the second subsequence, or skip it entirely. Since 
  we need the final GCDs to match, we can track the state using the current 
  index and the running GCDs of both subsequences.

• Approach:
  Define a DP state `dp[i][g1][g2]` representing the number of ways to distribute 
  elements from index `i` onwards such that `seq1` has a running GCD of `g1` and 
  `seq2` has a running GCD of `g2`. We use 0 to represent an empty subsequence.
  For `nums[i]`, we transition by branching into three possibilities:
  1. Skip: `dp[i+1][g1][g2]`
  2. Add to seq1: `dp[i+1][gcd(g1, nums[i])][g2]`
  3. Add to seq2: `dp[i+1][g1][gcd(g2, nums[i])]`

• Why it Works:
  The constraints are exceptionally small ($N \le 200$, $nums[i] \le 200$). The 
  maximum possible GCD is 200. This makes a state space of $200 \times 201 \times 201$ 
  completely viable and fast enough to run within limits.

• Time Complexity (TC): 
  $O(N \times M^2 \times \log(M))$, where $N$ is the size of `nums` ($N \le 200$) and 
  $M$ is the maximum value in `nums` ($M \le 200$). The log factor comes from the 
  GCD computation.
  
• Space Complexity (SC): 
  $O(N \times M^2)$ to store the DP table.
---------------------------------------------------------
*/

/*
=========================================================
FINAL APPROACH CHOICE
=========================================================
The 3D DP approach is chosen because the state space ($200 \times 201 \times 201 \approx 8 \times 10^6$ entries) 
fits easily within standard execution time and memory limits. Iterating from back to 
front allows a clean iterative implementation or a memoized recursive structure.
=========================================================
*/

class Solution {
private:
    const int MOD = 1e9 + 7;
    int memo[201][201][201];

    int solve(int idx, int g1, int g2, const vector<int>& nums) {
        // Base Case: If we processed all elements
        if (idx == nums.size()) {
            // Both subsequences must be non-empty (g1 > 0, g2 > 0) and have equal GCD
            return (g1 > 0 && g2 > 0 && g1 == g2) ? 1 : 0;
        }

        // Return cached result if already computed
        if (memo[idx][g1][g2] != -1) {
            return memo[idx][g1][g2];
        }

        // Choice 1: Skip the current element
        long long ans = solve(idx + 1, g1, g2, nums);

        // Choice 2: Include in the first subsequence
        int next_g1 = (g1 == 0) ? nums[idx] : std::gcd(g1, nums[idx]);
        ans = (ans + solve(idx + 1, next_g1, g2, nums)) % MOD;

        // Choice 3: Include in the second subsequence
        int next_g2 = (g2 == 0) ? nums[idx] : std::gcd(g2, nums[idx]);
        ans = (ans + solve(idx + 1, g1, next_g2, nums)) % MOD;

        return memo[idx][g1][g2] = ans;
    }

public:
    int subsequencePairCount(vector<int>& nums) {
        // Initialize memoization table with -1
        memset(memo, -1, sizeof(memo));
        return solve(0, 0, 0, nums);
    }
};
