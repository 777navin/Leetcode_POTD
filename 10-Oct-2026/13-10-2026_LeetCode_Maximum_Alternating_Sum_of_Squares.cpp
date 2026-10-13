/*
=========================================================
Date        : 13-10-2026
Problem Name: Maximum Alternating Sum of Squares
Platform    : LeetCode
Difficulty  : Medium
Tags        : Array, Greedy, Sorting

Problem Summary:
Given an integer array nums, rearrange its elements to maximize the alternating score.
The score is defined as arr[0]^2 - arr[1]^2 + arr[2]^2 - arr[3]^2 + ...

Key Observation:
Since we square each element, signs don't matter. To maximize the score, we should add the largest squared elements at even indices and subtract the smallest squared elements at odd indices.
=========================================================
*/

#include <vector>
#include <algorithm>
#include <cmath>

class Solution {
public:
    /*
    =========================================================
    Approach: Optimized Greedy with Sorting
    
    • Intuition:
      Squaring any number makes it non-negative. Since even indices contribute 
      positively and odd indices negatively, we should pair the largest available 
      squares with positive signs and smallest available squares with negative signs.
      
    • Approach:
      1. Take the absolute value of all elements and square them (or sort them by absolute value).
      2. Sort the array in ascending order.
      3. Iterate using a greedy two-pointer or index-based approach where smaller elements 
         are subtracted and larger elements are added.
         
    • Why it Works:
      Sorting ensures that the largest possible values are assigned to positive contributions 
      and the smallest values to negative contributions, maximizing the net sum.
      
    • Time Complexity (TC): O(N log N) due to sorting.
    • Space Complexity (SC): O(1) extra space (or O(N) depending on sorting implementation).
    =========================================================
    
    Why this approach is chosen:
    Sorting combined with greedy selection provides the optimal distribution of squared values 
    to maximize alternating additions and subtractions without needing complex dynamic programming.
    */
    long long maxAlternatingSum(std::vector<int>& nums) {
        int n = nums.size();
        
        // Transform elements to their squared absolute values
        std::vector<long long> squared;
        for (int x : nums) {
            long long val = 1LL * x * x;
            squared.push_back(val);
        }
        
        // Sort in ascending order
        std::sort(squared.begin(), squared.end());
        
        long long score = 0;
        int l = 0, r = n - 1;
        
        // Greedily assign smaller elements to odd positions (subtracted) 
        // and larger elements to even positions (added)
        bool add = true;
        while (l <= r) {
            if (n % 2 != 0) {
                // If odd length, the very first/smallest element added/subtracted follows pattern
                // Alternating from ends in sorted array: subtract smallest, add largest, etc.
            }
            // Standard optimal pairing for alternating sum of sorted squares:
            // Subtract the first n/2 elements, add the remaining.
        }
        
        // Clean implementation:
        // First n/2 elements are subtracted, remaining n - n/2 elements are added.
        long long total = 0;
        int mid = n / 2;
        for (int i = 0; i < mid; ++i) {
            total -= squared[i];
        }
        for (int i = mid; i < n; ++i) {
            total += squared[i];
        }
        
        return total;
    }
};
