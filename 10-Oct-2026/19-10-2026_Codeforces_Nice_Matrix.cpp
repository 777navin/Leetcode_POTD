/*
=========================================================
Date        : 19-10-2026
Problem Name: Find Target Indices After Sorting Array
Platform    : LeetCode
Difficulty  : Easy
Tags        : Array, Sorting, Binary Search

Problem Summary:
- Given an integer array `nums` and a target element `target`.
- Return a list of the target indices of `nums` after sorting it in non-decreasing order.
- If there are no target indices, return an empty list sorted in increasing order.

Key Observation:
- We do not actually need to sort the array; counting the elements strictly smaller than the target and the elements equal to the target gives us the exact range of indices.
=========================================================
*/

/*
---------------------------------------------------------
APPROACH EXPLANATION
---------------------------------------------------------

1. Sorting Approach (Brute Force / Standard)
   • Intuition: Follow the exact problem instructions by sorting the array first and iterating to find matches.
   • Approach: Sort `nums` in non-decreasing order, then iterate through to collect all indices where `nums[i] == target`.
   • Why it Works: Direct simulation of the problem statement.
   • Time Complexity (TC): O(N log N) due to sorting, where N is the length of `nums`.
   • Space Complexity (SC): O(1) or O(N) depending on the sorting algorithm's auxiliary space.

2. Counting Approach (Most Optimal)
   • Intuition: The final sorted position of the target depends entirely on how many numbers are smaller than it.
   • Approach: Count how many elements are strictly less than `target` (`less_count`) and how many elements are equal to `target` (`equal_count`). The indices will be from `less_count` to `less_count + equal_count - 1`.
   • Why it Works: Elements smaller than `target` must appear before it in the sorted array, and equal elements occupy consecutive slots right after.
   • Time Complexity (TC): O(N), as we only need a single pass to count.
   • Space Complexity (SC): O(K) where K is the number of target occurrences used for the output vector.

---------------------------------------------------------
FINAL APPROACH CHOSEN
---------------------------------------------------------
- The Counting Approach is chosen because it avoids the O(N log N) sorting overhead entirely, reducing the time complexity to O(N) with optimal space usage.
*/

#include <vector>

class Solution {
public:
    std::vector<int> targetIndices(std::vector<int>& nums, int target) {
        int less_count = 0;
        int equal_count = 0;

        // Count elements strictly smaller than target and elements equal to target
        for (int num : nums) {
            if (num < target) {
                less_count++;
            } else if (num == target) {
                equal_count++;
            }
        }

        // Generate the result indices in increasing order
        std::vector<int> result;
        for (int i = 0; i < equal_count; ++i) {
            result.push_back(less_count + i);
        }

        return result;
    }
};
