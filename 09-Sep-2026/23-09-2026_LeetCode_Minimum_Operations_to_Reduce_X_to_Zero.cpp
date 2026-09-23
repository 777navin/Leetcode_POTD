/*
=========================================================
Date        : 23-09-2026
Problem Name: Minimum Operations to Reduce X to Zero
Platform    : LeetCode
Difficulty  : Medium
Tags        : Array, Hash Table, Sliding Window, Prefix Sum

Problem Summary:
Given an integer array nums and an integer x, remove either the leftmost 
or rightmost element in each step and subtract its value from x.
Determine the minimum number of operations required to reduce x to exactly 0,
or return -1 if it is impossible.

Key Observation:
Removing prefix and suffix elements that sum to x is equivalent to finding 
the longest contiguous subarray whose elements sum to (totalSum - x).
=========================================================
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 1: Prefix Sum + Hash Map
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  We need to find the maximum length of a subarray whose sum equals target = sum(nums) - x.
  This can be solved by storing prefix sums and their earliest seen indices in a hash map.

• Approach:
  Compute total sum of nums. Set target = totalSum - x.
  Traverse the array maintaining running sum, store the first occurrence of each prefix sum, 
  and check if (runningSum - target) exists in the map to update the maximum length.

• Why it Works:
  If prefixSum[j] - prefixSum[i] == target, the subarray between indices i and j sums to target.
  Tracking the earliest index gives the maximum subarray length.

• Time Complexity (TC):
  O(n) - Single pass over the array with O(1) average lookup in an unordered_map.

• Space Complexity (SC):
  O(n) - Storing prefix sums in the hash map.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 2: Sliding Window / Two Pointers (Most Optimal)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  Since all elements in nums are strictly positive (nums[i] >= 1), the subarray sum is 
  monotonically non-decreasing as the window expands. This allows an O(1) space two-pointer approach.

• Approach:
  Calculate total sum. If totalSum < x, return -1; if totalSum == x, return n.
  Use two pointers (left and right) defining a window. Expand right and add nums[right].
  While the window sum exceeds target = totalSum - x, increment left and subtract nums[left].
  Whenever currentSum == target, record the maximum length: maxLen = max(maxLen, right - left + 1).
  The answer is n - maxLen (or -1 if maxLen was never updated).

• Why it Works:
  Positive elements ensure shrinking from the left strictly decreases the sum, 
  while expanding right strictly increases it, guaranteeing that every candidate window is checked.

• Time Complexity (TC):
  O(n) - Each pointer advances from 0 to n at most once.

• Space Complexity (SC):
  O(1) - Uses only constant auxiliary variables.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
FINAL APPROACH:
The Sliding Window approach is selected because all elements in nums are positive integers.
It achieves optimal O(n) runtime while cutting down extra space from O(n) to O(1),
avoiding hash map overhead and potential hash collisions.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
*/

#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int n = nums.size();
        long long totalSum = 0;
        for (int val : nums) {
            totalSum += val;
        }

        long long target = totalSum - x;

        // If target is negative, sum of all elements is less than x
        if (target < 0) {
            return -1;
        }

        // If target is 0, we must remove all elements
        if (target == 0) {
            return n;
        }

        int left = 0;
        long long currentSum = 0;
        int maxLen = -1;

        for (int right = 0; right < n; ++right) {
            currentSum += nums[right];

            while (left <= right && currentSum > target) {
                currentSum -= nums[left];
                ++left;
            }

            if (currentSum == target) {
                maxLen = max(maxLen, right - left + 1);
            }
        }

        return (maxLen == -1) ? -1 : (n - maxLen);
    }
};
