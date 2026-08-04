/*
=========================================================
Date        : 04-08-2026
Problem Name: 3731. Find Missing Elements
Platform    : LeetCode
Difficulty  : Easy
Tags        : Array, Sorting

Problem Summary:
Given an integer array, find and return all the missing elements 
that fall between the minimum and maximum values of the array.

Key Observation:
By sorting the array, all numbers are placed in ascending order. 
Any missing elements can be found by identifying gaps between 
adjacent array elements.
=========================================================

=========================================================
1. OPTIMIZED APPROACH (Sorting & Gap Finding)
=========================================================
• Intuition:
  If the elements are laid out in increasing order, any missing 
  numbers will simply be the integers strictly between `nums[i-1]` 
  and `nums[i]`.

• Approach:
  1. Sort the given `nums` array in ascending order.
  2. Iterate through the array starting from index 1.
  3. Set a tracker `missed_num` to `nums[i-1] + 1`.
  4. While `missed_num` is less than `nums[i]`, push it to the 
     answer vector and increment it.

• Why it Works:
  Sorting logically groups the bounds together. By comparing 
  adjacent elements, we ensure we seamlessly step through every 
  possible integer in the minimum-to-maximum range without 
  needing a predefined max boundary.

• Time Complexity (TC): 
  O(N log N) -> Dominated by the standard library sort function.
  
• Space Complexity (SC): 
  O(1) -> Auxiliary space is constant (excluding the space 
  required for the output vector).

=========================================================
FINAL APPROACH
=========================================================
The Sorting and Gap Finding approach is chosen here as it is highly 
intuitive, perfectly valid for the constraints, and directly matches 
the provided implementation. It runs flawlessly on LeetCode without 
requiring additional complex data structures.
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        // Sort the array to order elements from min to max
        sort(nums.begin(), nums.end());

        int n = nums.size();
        vector<int> missed;

        // Traverse to find gaps between adjacent elements
        for(int i = 1; i < n; i++) {
             int missed_num = nums[i - 1] + 1;

             // Push all numbers strictly between nums[i-1] and nums[i]
             while(missed_num < nums[i]) {
                missed.push_back(missed_num);
                missed_num++;
             }
        }
        
        return missed;
    }
};
