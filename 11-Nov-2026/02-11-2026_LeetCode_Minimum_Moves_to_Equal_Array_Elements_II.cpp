/*
=========================================================
Date        : 02-11-2026
Problem Name: Minimum Moves to Equal Array Elements II
Platform    : LeetCode
Difficulty  : Medium
Tags        : Array, Sorting, Math, Greedy, Median

Problem Summary:
Given an integer array nums, in one move we can
increment or decrement any element by 1.
Return the minimum number of moves required
to make all elements equal.

Key Observation:
The sum of absolute distances is minimized
when all elements are converted to the median.
=========================================================
*/

/*
=========================================================
APPROACH 1: Brute Force
=========================================================

Intuition:
• Try every possible target value.
• Calculate total moves needed for each target.

Approach:
• For every target, compute sum of abs(nums[i]-target).
• Return the minimum.

Why it Works:
• Checks all valid possibilities.

TC:
• O(Range * N)

SC:
• O(1)

Not feasible for large values.
*/

/*
=========================================================
APPROACH 2: Better (Sort + Check Candidates)
=========================================================

Intuition:
• The optimal value lies around the middle.

Approach:
• Sort the array.
• Evaluate possible middle elements.

Why it Works:
• The minimum absolute deviation occurs near the median.

TC:
• O(N log N)

SC:
• O(1)
*/

/*
=========================================================
APPROACH 3: Optimal (Sort + Median)
=========================================================

Intuition:
• Median minimizes total absolute distance.

Approach:
• Sort the array.
• Pick median = nums[n/2].
• Sum abs(nums[i] - median).

Why it Works:
• Mathematical property:
  Median minimizes Σ|x - target|.

TC:
• O(N log N)

SC:
• O(1) (Ignoring sort stack)
*/

/*
=========================================================
FINAL APPROACH
=========================================================

• Median gives the minimum total movement.
• After sorting, one median is enough.
• No need to try multiple target values.
• This is the standard optimal solution accepted on LeetCode.
=========================================================
*/

class Solution {
public:
    int minMoves2(vector<int>& nums) {
        sort(nums.begin(), nums.end(A);

        long long median = nums[nums.size() / 2];
        long long moves = 0;

        for (int num : nums) {
            moves += llabs((long long)num - median);
        }

        return (int)moves;
    }
};
