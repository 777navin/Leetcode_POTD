/*
=========================================================
Date        : 15-10-2026
Problem Name: Subarrays Distinct Element Sum of Squares I
Platform    : LeetCode
Difficulty  : Easy
Tags        : Array, Hash Table

Problem Summary:
- Given an integer array nums, calculate the sum of squares of the count of distinct elements in all possible contiguous subarrays.
- Return the final total sum.

Key Observation:
- Since the array length is very small (n <= 100), we can evaluate every possible subarray using nested loops without exceeding time limits.
=========================================================
*/

class Solution {
public:
    /*
    =====================================================
    Approach: Brute Force with Hash Set
    
    • Intuition: Generate every possible contiguous subarray, track unique elements using a hash set, and compute the sum of squares of their distinct counts.
    • Approach: Run an outer loop for the left boundary, an inner loop for the right boundary, and maintain a hash set and counter for unique elements.
    • Why it Works: Direct simulation ensures all subarrays are visited and their distinct counts are correctly squared and accumulated.
    • Time Complexity (TC): O(n^2) where n is the size of the nums array.
    • Space Complexity (SC): O(n) to store distinct elements in the unordered set for each subarray.
    =====================================================
    */
    int sumCounts(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        
        for (int l = 0; l < n; ++l) {
            unordered_set<int> seen;
            int cnt = 0;
            for (int r = l; r < n; ++r) {
                // If element is seen for the first time in the current subarray, increment distinct count
                if (seen.find(nums[r]) == seen.end()) {
                    seen.insert(nums[r]);
                    cnt++;
                }
                // Add the square of the distinct count to the total sum
                ans += cnt * cnt;
            }
        }
        return ans;
    }
};
