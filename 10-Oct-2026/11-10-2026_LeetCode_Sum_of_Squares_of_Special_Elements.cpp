/*
=========================================================
Date        : 11-10-2026
Problem Name: Sum of Squares of Special Elements
Platform    : LeetCode
Difficulty  : Easy
Tags        : Array, Enumeration

Problem Summary:
Given a 1-indexed array of integers of length n, find the sum of the squares of all elements whose 1-based index divides n.

Key Observation:
An element at 0-based index `i` corresponds to 1-based index `i + 1`. We check if `n % (i + 1) == 0`.
=========================================================
*/

#include <vector>

class Solution {
public:
    int sumOfSquares(std::vector<int>& nums) {
        /*
        1. Single Pass Enumeration
           • Intuition: Iterate through every element in the array while keeping track of its 1-based index.
           • Approach: Loop `i` from 0 to `n - 1`, check if `n % (i + 1) == 0`, and add `nums[i] * nums[i]` to the sum if true.
           • Why it Works: Directly mirrors the problem definition of a "special" element based on divisibility of indices.
           • Time Complexity (TC): O(n) where n is the size of the nums array.
           • Space Complexity (SC): O(1) as no extra auxiliary space is used.
        */
        
        // Why this approach is chosen:
        // A single pass linear scan is the most straightforward and optimal way to check all elements 
        // since every element must be inspected at least once to determine if its index divides n.
        
        int n = nums.size();
        int totalSum = 0;
        
        for (int i = 0; i < n; ++i) {
            int oneBasedIndex = i + 1;
            if (n % oneBasedIndex == 0) {
                totalSum += nums[i] * nums[i];
            }
        }
        
        return totalSum;
    }
};
