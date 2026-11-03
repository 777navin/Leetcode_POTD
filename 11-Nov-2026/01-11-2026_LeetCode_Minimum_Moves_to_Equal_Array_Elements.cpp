
/*
=========================================================
Date        : 01-11-2026
Problem Name: Minimum Moves to Equal Array Elements
Platform    : LeetCode
Difficulty  : Medium
Tags        : Array, Math

Problem Summary:
- Given an integer array, make all elements equal.
- In one move, increment exactly n-1 elements by 1.
- Return the minimum number of moves required.

Key Observation:
- Incrementing n-1 elements is equivalent to decrementing
  the remaining element by 1.
- Therefore, reduce every element to the minimum element.
=========================================================

APPROACH 1: Brute Force (Simulation)

- Intuition:
  Simulate each operation until all elements become equal.

- Approach:
  Increment n-1 elements in every move and repeat.

- Why it Works:
  Directly follows the problem statement.

- Time Complexity (TC): Very High
- Space Complexity (SC): O(1)

APPROACH 2: Optimized (Mathematical Observation)

- Intuition:
  Incrementing n-1 elements is equivalent to decrementing
  one element by 1.

- Approach:
  Find the minimum element and calculate the difference
  between every element and the minimum.

- Why it Works:
  Every element must effectively be reduced to the minimum.
  The total required reductions equal the minimum moves.

- Time Complexity (TC): O(n)
- Space Complexity (SC): O(1)

FINAL APPROACH:
- The mathematical approach avoids unnecessary simulation.
- A single traversal finds the minimum and calculates the sum.
- It is optimal with O(n) time and O(1) extra space.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minMoves(vector<int>& nums) {
        int minimum = *min_element(nums.begin(), nums.end());

        int moves = 0;

        for (int num : nums) {
            moves += num - minimum;
        }

        return moves;
    }
};
