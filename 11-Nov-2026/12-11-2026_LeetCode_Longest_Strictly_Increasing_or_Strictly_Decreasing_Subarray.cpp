/*
=========================================================
Date        : 12-11-2026
Problem Name: Longest Strictly Increasing or Strictly Decreasing Subarray
Platform    : LeetCode
Difficulty  : Easy
Tags        : Array, Simulation, Greedy

Problem Summary:
- Given an integer array nums.
- Find the length of the longest contiguous subarray
  that is either strictly increasing or strictly decreasing.
- Return the maximum such length.

Key Observation:
- We only need to track the current increasing and
  decreasing streak lengths while traversing once.
=========================================================
*/

class Solution {
public:

    /*
    =========================================================
    Approach 1: Brute Force

    • Intuition:
      - Check every possible subarray.

    • Approach:
      - Generate all subarrays.
      - Verify whether each is strictly increasing
        or strictly decreasing.

    • Why it Works:
      - Examines every valid candidate explicitly.

    • TC: O(N^3)
    • SC: O(1)
    =========================================================
    */

    /*
    =========================================================
    Approach 2: One-Pass Greedy (Optimal)

    • Intuition:
      - Maintain current increasing and decreasing lengths.

    • Approach:
      - If nums[i] > nums[i-1]:
            increase increasing length,
            reset decreasing length.
      - If nums[i] < nums[i-1]:
            increase decreasing length,
            reset increasing length.
      - Otherwise reset both to 1.
      - Track maximum answer.

    • Why it Works:
      - Every strictly monotonic subarray ending at i
        can be represented by current streak lengths.

    • TC: O(N)
    • SC: O(1)
    =========================================================
    */

    /*
    =========================================================
    Final Approach Chosen:
    - One-pass greedy solution.
    - Uses constant extra memory.
    - Faster and simpler than checking all subarrays.
    - Directly tracks valid increasing/decreasing streaks.
    =========================================================
    */

    int longestMonotonicSubarray(vector<int>& nums) {

        int increasing = 1;
        int decreasing = 1;
        int answer = 1;

        for (int i = 1; i < (int)nums.size(); i++) {

            if (nums[i] > nums[i - 1]) {
                increasing++;
                decreasing = 1;
            }
            else if (nums[i] < nums[i - 1]) {
                decreasing++;
                increasing = 1;
            }
            else {
                increasing = 1;
                decreasing = 1;
            }

            answer = max(answer, max(increasing, decreasing));
        }

        return answer;
    }
};
