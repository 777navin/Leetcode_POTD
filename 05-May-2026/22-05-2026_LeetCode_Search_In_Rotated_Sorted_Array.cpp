/*
Date: 22-05-2026
Problem Name: Search in Rotated Sorted Array
Platform: LeetCode (Problem #33)
Difficulty: Medium
Tags: Array, Binary Search

Problem Summary:
Given an integer array 'nums' that is sorted in ascending order with distinct values, 
and is possibly rotated at an unknown pivot index, locate the index of a given 'target'. 
If the target exists in the array, return its 0-indexed position; otherwise, return -1.
The solution must run in O(log n) time complexity.

Methods to Solve:
1. Brute Force (Linear Search)
2. Optimal Approach (Modified Binary Search)

--------------------------------------------------------------------------------
1. Brute Force Approach
- Intuition: Scan the array from left to right until the target element is found.
- Approach: Iterate through the vector using a simple for-loop and check if nums[i] == target.
- Dry Run: 
  nums = [4,5,6,7,0,1,2], target = 0
  i=0: 4!=0 | i=1: 5!=0 | i=2: 6!=0 | i=3: 7!=0 | i=4: 0==0 -> return 4
- Time Complexity: O(n) because we potentially traverse the entire array of size n.
- Space Complexity: O(1) as no auxiliary space is utilized.
- Why better than previous method: N/A (Baseline method).
- When to use: Only useful if the array is completely unsorted or constraints are extremely small (n <= 100). Failing the O(log n) constraint rule here.

--------------------------------------------------------------------------------
2. Optimal Approach (Modified Binary Search)
- Intuition: In a rotated sorted array, splitting the array at any midpoint will always 
  leave at least one half completely sorted. We can look at the sorted half to check 
  if the target lies within its bounds. If it does, we narrow our search to that half; 
  otherwise, we eliminate it and search the other half.
- Approach:
  - Maintain 'low' and 'high' pointers.
  - Calculate 'mid'. If nums[mid] == target, return mid.
  - Check if the left half (nums[low] to nums[mid]) is sorted:
    - If sorted, check if target lies between nums[low] and nums[mid]. 
      If yes, shrink search space to left (high = mid - 1); else go right (low = mid + 1).
  - Otherwise, the right half (nums[mid] to nums[high]) must be sorted:
    - Check if target lies between nums[mid] and nums[high]. 
      If yes, shrink search space to right (low = mid + 1); else go left (high = mid - 1).
- Dry Run:
  nums = [4,5,6,7,0,1,2], target = 0
  Iteration 1: low = 0, high = 6, mid = 3 (nums[mid] = 7)
               Left half [4 to 7] is sorted (nums[low] <= nums[mid]).
               Is target (0) inside [4, 7]? No. -> low = mid + 1 = 4.
  Iteration 2: low = 4, high = 6, mid = 5 (nums[mid] = 1)
               Left half [0 to 1] is sorted (nums[low] <= nums[mid]).
               Is target (0) inside [0, 1]? Yes. -> high = mid - 1 = 4.
  Iteration 3: low = 4, high = 4, mid = 4 (nums[mid] = 0)
               nums[mid] == target -> return 4.
- Time Complexity: O(log n) as the search space is halved in every single step.
- Space Complexity: O(1) keeping iteration pointer variables only.
- Why better than previous method: Drastically reduces execution steps from linear scaling to logarithmic scaling, fully satisfying the constraints.
- When to use: Ideal and mandatory requirement for searching key elements in any rotated sorted variant arrays under strict performance bounds.

Comparison Table:
Method         | TC       | SC   | Best Use Case
--------------------------------------------------------------------------------
Brute Force    | O(n)     | O(1) | Small arrays where code simplicity is prioritized.
Optimal Search | O(log n) | O(1) | Large scale datasets needing fast lookup speeds.

Final Recommended Solution: Optimal Approach (Modified Binary Search)
*/

#include <vector>

class Solution {
public:
    int search(std::vector<int>& nums, int target) {
        int low = 0;
        int high = nums.size() - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            // Target located successfully
            if (nums[mid] == target) {
                return mid;
            }

            // Identify which half of the array is normally sorted
            if (nums[low] <= nums[mid]) {
                // Left half is sorted cleanly
                if (target >= nums[low] && target < nums[mid]) {
                    high = mid - 1; // Target lies within left sorted zone
                } else {
                    low = mid + 1;  // Target lies outside left sorted zone
                }
            } else {
                // Right half must be sorted cleanly
                if (target > nums[mid] && target <= nums[high]) {
                    low = mid + 1;  // Target lies within right sorted zone
                } else {
                    high = mid - 1; // Target lies outside right sorted zone
                }
            }
        }

        // Element not found within the bounds
        return -1;
    }
};
