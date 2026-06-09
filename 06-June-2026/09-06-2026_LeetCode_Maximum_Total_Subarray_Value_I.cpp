/*
Date: 09-06-2026
Problem Name: Maximum Total Subarray Value I
Platform: LeetCode
Difficulty: Medium
Tags: Array, Greedy

Problem Summary:
Given an array `nums` of length `n` and an integer `k`, we need to choose exactly `k` non-empty 
subarrays `nums[l..r]`. Subarrays may overlap, and the same indices can be reused. The value of 
a subarray is defined as `max(nums[l..r]) - min(nums[l..r])`. We need to maximize the sum of 
values of these `k` chosen subarrays.

Methods to Solve:
1. Optimal Greedy Approach:
   - Intuition: To maximize the total value, we need to choose a subarray that contains both the 
     global maximum and the global minimum of the array `nums` as many times as possible. 
     The value of this subarray is `max(nums) - min(nums)`.
   - Approach: Find the maximum element (`max_val`) and the minimum element (`min_val`) in the 
     given array. The value of a subarray spanning the entire array is `max_val - min_val`. 
     Since we can choose the same subarray `k` times, the maximum total value is `k * (max_val - min_val)`.
   - Time Complexity: O(n) to find the max and min elements.
   - Space Complexity: O(1).
   - Why better: This is the mathematically optimal construction based on the property that 
     a larger range (the whole array) covers all possible min/max pairs.

Comparison Table:
Method | TC | SC | Best Use Case
-------|----|----|-------------
Greedy | O(n) | O(1) | Optimal for this specific problem

Final Recommended Solution: The Greedy approach finding global min and max.
*/

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    /**
     * Calculates the maximum total value by selecting k subarrays.
     * * @param nums The input array of integers.
     * @param k The number of subarrays to choose.
     * @return The maximum possible total value.
     */
    long long maxTotalValue(vector<int>& nums, int k) {
        if (nums.empty()) return 0;
        
        int min_val = nums[0];
        int max_val = nums[0];
        
        // Find the global minimum and maximum in O(n)
        for (int num : nums) {
            if (num < min_val) min_val = num;
            if (num > max_val) max_val = num;
        }
        
        // The optimal strategy is to pick the full array range [0, n-1] 
        // as our subarray k times.
        long long diff = (long long)max_val - min_val;
        return (long long)k * diff;
    }
};
