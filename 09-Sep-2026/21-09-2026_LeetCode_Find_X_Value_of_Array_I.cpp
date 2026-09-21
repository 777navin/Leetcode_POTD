/*
=========================================================
Date        : 21-09-2026
Problem Name: 3524. Find X Value of Array I
Platform    : LeetCode
Difficulty  : Medium
Tags        : Array, Math, Dynamic Programming

Problem Summary:
Given an array `nums` of positive integers and an integer `k`.
An operation consists of removing non-overlapping prefix and suffix such that the array remains non-empty.
Find the number of ways to perform this operation such that the product of the remaining elements modulo k equals x, for all 0 <= x <= k - 1.

Key Observation:
Removing an arbitrary prefix and suffix leaves an arbitrary non-empty contiguous subarray.
The problem is equivalent to counting non-empty contiguous subarrays whose product modulo k equals x.
=========================================================
*/

#include <vector>

using namespace std;

/*
---------------------------------------------------------
APPROACH 1: Brute Force
---------------------------------------------------------
• Intuition:
  Iterate over all possible pairs of indices (i, j) where 0 <= i <= j < n, representing the remaining subarray.
• Approach:
  For each subarray from i to j, compute the product modulo k on the fly and increment the count for that remainder.
• Why it Works:
  Directly checks all O(N^2) valid non-empty subarrays.
• Time Complexity (TC):
  O(N^2) - Nested loops over all subarray start and end points.
• Space Complexity (SC):
  O(k) - For storing the counts of each remainder.

---------------------------------------------------------
APPROACH 2: Dynamic Programming (Optimal)
---------------------------------------------------------
• Intuition:
  Extending a subarray ending at index i - 1 with remainder `r` by element `nums[i]` yields a new remainder `(r * (nums[i] % k)) % k`.
• Approach:
  Maintain a frequency array `prev_dp` of size k where `prev_dp[r]` is the number of subarrays ending at the previous index with product modulo k equal to r.
  For the current index, a single-element subarray `[nums[i]]` contributes to remainder `nums[i] % k`, and each existing subarray with remainder `r` transitions to `(r * (nums[i] % k)) % k`.
  Accumulate the counts into a global answer array of 64-bit integers.
• Why it Works:
  Every subarray ending at index i is either just `[nums[i]]` or an extension of a subarray ending at index i - 1.
• Time Complexity (TC):
  O(N * k) - A single pass over the array of size N, performing at most k transitions at each step. Since k <= 5, this is effectively O(N).
• Space Complexity (SC):
  O(k) - Only the state of the previous index is kept in memory.
*/

/*
---------------------------------------------------------
FINAL APPROACH SELECTION:
We choose the O(N * k) Dynamic Programming approach because N can be up to 10^5,
making an O(N^2) brute force approach result in Time Limit Exceeded (TLE).
Space-optimized DP uses minimal auxiliary memory O(k).
---------------------------------------------------------
*/

class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> result(k, 0);
        // dp[r] stores the number of subarrays ending at the current index whose product modulo k is r
        vector<long long> dp(k, 0);

        for (int val : nums) {
            vector<long long> next_dp(k, 0);
            int current_mod = val % k;

            // Single-element subarray [nums[i]]
            next_dp[current_mod]++;

            // Extend all subarrays ending at index i - 1
            for (int r = 0; r < k; ++r) {
                if (dp[r] > 0) {
                    int new_mod = (r * current_mod) % k;
                    next_dp[new_mod] += dp[r];
                }
            }

            // Accumulate counts into the final answer
            for (int r = 0; r < k; ++r) {
                result[r] += next_dp[r];
            }

            dp = move(next_dp);
        }

        return result;
    }
};
