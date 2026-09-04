/*
=========================================================
Date        : 04-09-2026
Problem Name: Smallest Stable Index I
Platform    : LeetCode
Difficulty  : Easy
Tags        : Array, Prefix Sum

Problem Summary:
Given an integer array nums of length n and an integer k, find the 
smallest index i such that its instability score is at most k.
The instability score at index i is max(nums[0..i]) - min(nums[i..n-1]).
If no such index exists, return -1.

Key Observation:
Precomputing suffix minimums allows evaluating the instability score 
in O(1) time at each index while maintaining a running prefix maximum.
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Brute Force
---------------------------------------------------------
• Intuition:
  Compute the maximum of the prefix nums[0..i] and the minimum of the
  suffix nums[i..n-1] directly for each index i from 0 to n - 1.

• Approach:
  Iterate through each index i from 0 to n - 1. For each i, run two inner
  loops to determine max(nums[0..i]) and min(nums[i..n-1]). Return the first
  i where max_val - min_val <= k.

• Why it Works:
  Directly checks the condition for each index sequentially, ensuring the
  smallest valid index is returned first.

• Time Complexity (TC) : O(n^2)
• Space Complexity (SC): O(1)

---------------------------------------------------------
APPROACH 2: Optimized (Prefix Max + Suffix Min Array)
---------------------------------------------------------
• Intuition:
  To avoid recalculating suffix minimums repeatedly, precalculate them from
  right to left. Maintain the prefix maximum on the fly while scanning left to right.

• Approach:
  1. Build a suffix minimum array `suffMin` of size n where `suffMin[i] = min(nums[i..n-1])`.
  2. Iterate i from 0 to n - 1 while tracking `prefMax = max(prefMax, nums[i])`.
  3. The first index satisfying `prefMax - suffMin[i] <= k` is the answer.
  4. If no such index satisfies the condition, return -1.

• Why it Works:
  Suffix minimums can be queried in O(1) time, allowing every index to be
  evaluated in linear time.

• Time Complexity (TC) : O(n)
• Space Complexity (SC): O(n)
---------------------------------------------------------
*/

/*
FINAL APPROACH:
We choose the Optimized (Prefix Max + Suffix Min Array) approach.
It reduces the time complexity from O(n^2) down to O(n) using a single 
precomputed suffix array and a running prefix maximum variable, making 
it optimal in execution speed and simple to implement.
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();
        if (n == 0) return -1;

        // suffMin[i] stores the minimum element in nums[i..n-1]
        vector<int> suffMin(n);
        suffMin[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            suffMin[i] = min(nums[i], suffMin[i + 1]);
        }

        int prefMax = nums[0];
        for (int i = 0; i < n; ++i) {
            prefMax = max(prefMax, nums[i]);
            if (prefMax - suffMin[i] <= k) {
                return i;
            }
        }

        return -1;
    }
};
