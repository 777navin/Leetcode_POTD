/*
=========================================================
Date        : 05-09-2026
Problem Name: Smallest Stable Index II
Platform    : LeetCode
Difficulty  : Medium
Tags        : Array, Prefix Sum

Problem Summary:
Given an array `nums` and an integer `k`, find the smallest index `i` such that
the instability score `max(nums[0..i]) - min(nums[i..n-1]) <= k`.
If no such index exists, return -1.

Key Observation:
Prefix maximums can be tracked while traversing left-to-right, and suffix minimums
can be precomputed right-to-left in linear time.
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Brute Force
---------------------------------------------------------
• Intuition:
  For each candidate index `i`, find the maximum in `nums[0..i]` and the minimum in `nums[i..n-1]` directly.
• Approach:
  Iterate `i` from `0` to `n - 1`. In each iteration, use nested loops or `std::max_element`/`std::min_element` to compute prefix max and suffix min, check if difference <= k, and return the first valid index.
• Why it Works:
  Directly simulates the problem definition.
• Time Complexity (TC):
  O(n^2) - Subarray scanning takes O(n) per index.
• Space Complexity (SC):
  O(1) - No extra auxiliary memory needed.

---------------------------------------------------------
APPROACH 2: Suffix Minimum Array + Prefix Running Maximum (Optimal)
---------------------------------------------------------
• Intuition:
  Precompute all suffix minimums so that querying `min(nums[i..n-1])` takes O(1) time, while computing prefix max on the fly.
• Approach:
  1. Build an array `suffMin` of size `n`, where `suffMin[i] = min(nums[i], suffMin[i + 1])`.
  2. Iterate `i` from `0` to `n - 1`, updating a running variable `prefMax = max(prefMax, nums[i])`.
  3. At the first index `i` where `prefMax - suffMin[i] <= k`, return `i`.
  4. If no such index satisfies the condition, return `-1`.
• Why it Works:
  Suffix minimums depend only on elements to the right, precomputing them eliminates repeated traversals.
• Time Complexity (TC):
  O(n) - One pass from right-to-left for suffix minimums and one pass left-to-right to find the answer.
• Space Complexity (SC):
  O(n) - Auxiliary array of size `n` to store suffix minimums.
*/

/*
=========================================================
FINAL APPROACH: Suffix Minimum Array + Prefix Running Maximum
=========================================================
• This approach achieves optimal O(n) time complexity, handling n up to 10^5 comfortably within the time limit.
• It reduces the O(n^2) brute force to two linear scans, using minimal auxiliary memory.
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();
        if (n == 0) return -1;

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
