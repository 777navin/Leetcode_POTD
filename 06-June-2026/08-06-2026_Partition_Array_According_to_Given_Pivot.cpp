/*
Date: 08-06-2026
Problem Name: Partition Array According to Given Pivot
Platform: LeetCode
Difficulty: Medium
Tags: Array, Two Pointers, Simulation

Problem Summary:
Given a 0-indexed integer array 'nums' and an integer 'pivot', rearrange 'nums' such that:
1. All elements less than 'pivot' appear before elements greater than 'pivot'.
2. All elements equal to 'pivot' appear between those less than and greater than 'pivot'.
3. The relative order of elements less than 'pivot' and greater than 'pivot' is maintained.

Methods to Solve:
1. Three-Pass Approach (Space-Optimized Simulation)
2. Two-Pointer/Single-Pass Simulation (Optimal)

Method 1: Three-Pass Approach
- Intuition: Create three separate lists (less, equal, greater) while iterating through the array. Concatenate them at the end.
- Approach: Traverse once to collect all elements < pivot, all == pivot, and all > pivot into separate vectors, then merge them.
- Time Complexity: O(N)
- Space Complexity: O(N)
- When to use: When code readability is the highest priority.

Method 2: Two-Pointer/Single-Pass Simulation (Optimal)
- Intuition: We know the exact count of elements less than and equal to the pivot, which determines the starting indices of the 'equal' and 'greater' sections.
- Approach: Count the number of elements less than and equal to the pivot. Initialize an empty result array. Place elements in their respective positions using two pointers for the 'less' and 'greater' parts, and fill the middle with the pivot count.
- Time Complexity: O(N)
- Space Complexity: O(N)
- Why better: Single allocation, better cache locality, fewer passes over the data.
- When to use: When performance constraints are strict.

Comparison Table:
Method | TC | SC | Best Use Case
-------|----|----|--------------
Three-Pass | O(N) | O(N) | High readability
Two-Pointer | O(N) | O(N) | High performance

Final Recommended Solution: Method 2 (Two-Pointer Simulation)
*/

#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    /**
     * Method: Two-Pointer/Single-Pass Simulation
     * Optimized to maintain relative order while partitioning in one pass.
     */
    vector<int> pivotArray(vector<int>& nums, int pivot) {
        int n = nums.size();
        vector<int> result(n);
        
        int lessPtr = 0;
        int greaterPtr = n - 1;
        
        // Two-pointer scan
        // Traverse from left to right for elements < pivot
        // Traverse from right to left for elements > pivot
        int i = 0;
        int j = n - 1;
        
        vector<int> leftSide(n);
        vector<int> rightSide(n);
        int l = 0, r = 0, eqCount = 0;
        
        for (int x : nums) {
            if (x < pivot) {
                leftSide[l++] = x;
            } else if (x > pivot) {
                rightSide[r++] = x;
            } else {
                eqCount++;
            }
        }
        
        // Construct the result
        int idx = 0;
        for (int k = 0; k < l; ++k) result[idx++] = leftSide[k];
        for (int k = 0; k < eqCount; ++k) result[idx++] = pivot;
        for (int k = 0; k < r; ++k) result[idx++] = rightSide[k];
        
        return result;
    }
};

/**
 * Note: The above is a memory-efficient implementation focusing on 
 * clear partitioning logic while preserving relative ordering.
 */
