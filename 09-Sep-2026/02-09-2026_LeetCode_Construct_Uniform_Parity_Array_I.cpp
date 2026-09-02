/*
=========================================================
Date        : 02-09-2026
Problem Name: Construct Uniform Parity Array I
Platform    : LeetCode
Difficulty  : Easy
Tags        : Array, Math

Problem Summary:
Given an array nums1 of n distinct integers, construct an array
nums2 of length n such that all elements are either all odd or all even.
For each index i, set nums2[i] = nums1[i] or nums2[i] = nums1[i] - nums1[j] (j != i).
Determine whether it is always possible to form such an array.

Key Observation:
If any odd number exists, any even number can be transformed into an odd number
via (even - odd = odd), while odd numbers stay odd. If no odd numbers exist,
all numbers are already even. Thus, a valid array can always be formed.
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Mathematical Invariance / Parity Analysis (Optimal)
---------------------------------------------------------
• Intuition:
  - Parity arithmetic shows: even - odd = odd, and odd numbers can remain as they are.
  - If the array contains at least one odd number, we can make all elements odd.
  - If the array contains zero odd numbers, all elements are already even.

• Approach:
  - Since every possible configuration of numbers can always be transformed into
    an all-odd or an all-even array, the answer is unconditionally true.
  - Directly return true.

• Why it Works:
  - All integers are either even or odd; if odd count == 0, parity is already uniform (even).
  - If odd count >= 1, any even number nums1[i] can subtract that odd element to become odd.

• Time Complexity (TC):
  - O(1)

• Space Complexity (SC):
  - O(1)
---------------------------------------------------------
*/

/*
---------------------------------------------------------
FINAL APPROACH:
---------------------------------------------------------
• Directly return true based on parity invariance.
• Avoids unnecessary traversals or allocations, achieving O(1) time and space.
---------------------------------------------------------
*/

class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        return true;
    }
};
