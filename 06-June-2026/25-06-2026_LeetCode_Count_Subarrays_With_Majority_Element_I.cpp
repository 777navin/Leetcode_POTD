/*
Date: 25-06-2026
Problem Name: Count Subarrays With Majority Element I
Platform: LeetCode
Difficulty: Medium
Tags: Array, Hash Table, Prefix Sum

Problem Summary:
Given an integer array `nums` and an integer `target`, return the number of 
subarrays in which `target` is the majority element. A majority element is 
defined as an element appearing strictly more than half the times in the subarray.

Methods to Solve:
1. Brute Force
2. Optimal Sliding Window / Frequency Map Approach

For EACH method include:

- Method 1: Brute Force
    - Intuition: Iterate through all possible subarrays, count occurrences of `target`, 
      and check the majority condition.
    - Approach: Use nested loops to define all subarrays [i, j]. Keep a counter.
    - Time Complexity: O(N^2)
    - Space Complexity: O(1)
    - Why better: Simple to implement for small constraints.

- Method 2: Frequency Map (Optimal for N <= 1000)
    - Intuition: Since we need target to be strictly more than half, for any 
      subarray of length `L`, we need `count(target) > L/2`.
    - Approach: Use nested loops, but maintain a running count of `target`. 
      If `2 * current_count > current_length`, add to the answer.
    - Time Complexity: O(N^2) - Given constraints N <= 1000, O(N^2) is acceptable.
    - Space Complexity: O(1)

Comparison Table:
Method      | TC    | SC    | Best Use Case
------------|-------|-------|--------------
Brute Force | O(N^2)| O(1)  | Small N
Frequency   | O(N^2)| O(1)  | N <= 1000

Final Recommended Solution: Method 2 (Optimized iteration)
*/

#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    /**
     * @brief Counts subarrays where 'target' is the majority element.
     * * @param nums The input array of integers.
     * @param target The element to check for majority.
     * @return int Number of valid subarrays.
     */
    int countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();
        int totalSubarrays = 0;

        // Iterate through all possible starting points
        for (int i = 0; i < n; ++i) {
            int count = 0;
            // Iterate through all possible ending points
            for (int j = i; j < n; ++j) {
                if (nums[j] == target) {
                    count++;
                }
                
                int length = j - i + 1;
                
                // Condition: count > length / 2
                // Equivalent to: 2 * count > length
                if (2 * count > length) {
                    totalSubarrays++;
                }
            }
        }

        return totalSubarrays;
    }
};

/*
Example Usage:
Solution sol;
vector<int> nums = {1, 2, 2, 3};
int target = 2;
int result = sol.countMajoritySubarrays(nums, target); 
// Output: 5
*/
