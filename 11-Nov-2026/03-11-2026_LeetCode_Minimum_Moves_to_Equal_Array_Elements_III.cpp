/*
=========================================================
Date        : 03-11-2026
Problem Name: 3736. Minimum Moves to Equal Array Elements III
Platform    : LeetCode
Difficulty  : Easy
Tags        : Array, Math

Problem Summary:
- Given an integer array nums.
- In one move, we can increase any element by 1.
- Find the minimum moves required to make all elements equal.

Key Observation:
- Since we can only increase elements, the final target
  must be the maximum element in the array.
- Each element needs (maximum - nums[i]) increments.
=========================================================

1. BRUTE FORCE (Simulation)

Intuition:
- Increase the smallest elements until all become equal.

Approach:
- Repeatedly find the minimum element and increment it.
- Count every increment until all elements are equal.

Why it Works:
- Every element eventually reaches the maximum value.

Time Complexity: O(n * max(nums))
Space Complexity: O(1)

2. OPTIMIZED (Single Traversal)

Intuition:
- The maximum element is the only possible optimal target.

Approach:
- Find the maximum element.
- Calculate the difference between maximum and every element.
- Add all differences to get the minimum moves.

Why it Works:
- Every element must reach at least the maximum value.
- Choosing the maximum minimizes the total increments.

Time Complexity: O(n)
Space Complexity: O(1)

FINAL APPROACH:
- Use a single traversal to find the maximum element.
- Calculate the total difference in another traversal.
- This avoids unnecessary sorting and simulation.
- It achieves optimal O(n) time and O(1) extra space.
=========================================================
*/

class Solution {
public:
    int minMoves(vector<int>& nums) {
        int maxElement = *max_element(nums.begin(), nums.end());

        int totalMoves = 0;

        for (int num : nums) {
            totalMoves += maxElement - num;
        }

        return totalMoves;
    }
};

/*
=========================================================
Filename:
03-11-2026_LeetCode_Minimum_Moves_to_Equal_Array_Elements_III.cpp
=========================================================
*/
