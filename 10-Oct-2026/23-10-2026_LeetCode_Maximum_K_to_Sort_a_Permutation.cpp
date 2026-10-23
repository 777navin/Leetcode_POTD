/*
=========================================================
Date        : 23-10-2026
Problem Name: 3644. Maximum K to Sort a Permutation
Platform    : LeetCode
Difficulty  : Medium
Tags        : Array, Bit Manipulation

Problem Summary:
Given a permutation of [0, n - 1], swap two values only when
their bitwise AND is exactly k. Return the maximum k that
allows the permutation to be sorted; return 0 if already sorted.

Key Observation:
Every value currently at an incorrect index must be moved, so
k must be a bitwise subset of every misplaced value. AND them all.
=========================================================

Approach 1: Optimized Bitwise AND
- Intuition: Every misplaced value must participate in swaps, so
  every set bit of a valid k must be present in all such values.
- Approach: Compute the bitwise AND of nums[i] for every i where
  nums[i] != i. If no index is misplaced, return 0.
- Why it Works: The AND is the largest bitmask shared by all
  misplaced values; using it as the swap pivot permits sorting.
- Time Complexity (TC): O(n), one pass through the array.
- Space Complexity (SC): O(1), only constant extra variables.

Final Approach:
Use the one-pass bitwise-AND observation. It avoids simulating
swaps or testing candidate values, achieving optimal O(n) time
and O(1) auxiliary space.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int sortPermutation(vector<int>& nums) {
        int k = -1;
        bool hasMisplacedValue = false;

        for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
            if (nums[i] == i) {
                continue;
            }

            if (!hasMisplacedValue) {
                k = nums[i];
                hasMisplacedValue = true;
            } else {
                k &= nums[i];
            }
        }

        // Return 0 when the permutation is already sorted.
        return hasMisplacedValue ? k : 0;
    }
};
