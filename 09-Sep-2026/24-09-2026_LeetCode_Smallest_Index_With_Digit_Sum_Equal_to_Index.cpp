/*
=========================================================
Date        : 24-09-2026
Problem Name: 3550. Smallest Index With Digit Sum Equal to Index
Platform    : LeetCode
Difficulty  : Easy
Tags        : Array, Math, Simulation

Problem Summary:
Given an integer array nums, find the smallest index i such that 
the sum of the digits of nums[i] equals i. If no such index 
exists, return -1.

Key Observation:
Iterate sequentially from index 0 to n - 1. The first index that 
satisfies the condition is guaranteed to be the smallest valid index.
=========================================================
*/

/*
=========================================================
APPROACH 1: Linear Scan with Digit Sum Simulation (Most Optimal)
=========================================================

• Intuition:
  Since we need the smallest index i, scanning from left to right 
  allows us to return immediately upon finding the first valid match.

• Approach:
  1. Traverse each index i from 0 up to nums.size() - 1.
  2. For nums[i], compute the sum of its decimal digits using modulo 10 arithmetic.
  3. If digit_sum == i, return i immediately.
  4. If the loop completes without a match, return -1.

• Why it Works:
  Linear traversal guarantees we inspect candidate indices in strictly 
  increasing order, ensuring minimum index optimality without extra sorting or storage.

• Time Complexity (TC):
  O(n * log10(max_val)) - Where n is nums.length and max_val <= 1000 (at most 4 digits per number).
• Space Complexity (SC):
  O(1) - Uses only constant auxiliary variables.
=========================================================
*/

/*
=========================================================
FINAL APPROACH DECISION:
Approach 1 is the most direct and optimal method.
It achieves O(n) time and O(1) auxiliary space, which runs well within
the constraints (n <= 100, nums[i] <= 1000) and terminates early.
=========================================================
*/

#include <vector>

class Solution {
public:
    int smallestIndex(std::vector<int>& nums) {
        int n = static_cast<int>(nums.size());

        for (int i = 0; i < n; ++i) {
            int val = nums[i];
            int digitSum = 0;

            // Compute sum of digits of nums[i]
            while (val > 0) {
                digitSum += val % 10;
                val /= 10;
            }

            // Check if digit sum matches current index
            if (digitSum == i) {
                return i;
            }
        }

        return -1;
    }
};
