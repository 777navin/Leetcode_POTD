/*
=========================================================
Date        : 15-08-2026
Problem Name: 3702. Longest Subsequence With Non-Zero Bitwise XOR
Platform: LeetCode
Difficulty: Medium
Tags: Array, Bit Manipulation

Problem Summary:
Find the length of the longest subsequence in an array such that
the bitwise XOR of its elements is not equal to zero.

Key Observation:
If the total XOR is non-zero, the answer is the entire array length.
If the total XOR is zero, removing any single non-zero element makes the remaining XOR non-zero.
=========================================================
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
1. Optimal (Mathematical Observation)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition
  The XOR of the entire array dictates our starting point. If it's already non-zero,
  we can take all elements. If it's zero, we just need to drop one non-zero element.

• Approach
  1. Traverse the array to calculate the total XOR of all elements.
  2. Simultaneously, track if there is at least one non-zero element in the array.
  3. If total XOR != 0, return n.
  4. If total XOR == 0 but there is a non-zero element, return n - 1.
  5. If all elements are 0, return 0.

• Why it Works
  If total XOR is 0, removing a non-zero element `x` changes the XOR of the remaining
  elements to `0 ^ x = x`, which is non-zero. Thus, we only ever need to remove at most
  one element to achieve a non-zero XOR, unless all elements are zero.

• Time Complexity (TC)
  O(N) - Single pass through the array.

• Space Complexity (SC)
  O(1) - Only a few variables used for tracking.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
FINAL APPROACH
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• This approach is chosen because it perfectly solves the problem in a single pass.
• It operates in linear time O(N) and constant space O(1), making it the most optimal solution.
*/

#include <vector>

using namespace std;

class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int total_xor = 0;
        bool has_nonzero = false;
        int n = nums.size();

        for (int num : nums) {
            total_xor ^= num;
            if (num != 0) {
                has_nonzero = true;
            }
        }

        if (total_xor != 0) {
            return n;
        }

        if (has_nonzero) {
            return n - 1;
        }

        return 0;
    }
};
