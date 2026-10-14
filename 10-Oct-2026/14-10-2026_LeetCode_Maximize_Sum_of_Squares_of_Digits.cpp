/*
=========================================================
Date        : 14-10-2026
Problem Name: Maximize Sum of Squares of Digits
Platform    : LeetCode
Difficulty  : Medium
Tags        : Greedy, Math

Problem Summary:
- Given number of digits 'num' and digit sum 'sum'.
- Find a valid number of length 'num' whose digits sum to 'sum' and maximize sum of squared digits.
- If multiple valid numbers share the maximum sum of squares, return the largest string representation.

Key Observation:
- To get the largest string representation lexicographically, we must prioritize placing the largest possible digits at the leftmost positions while ensuring the remaining sum can be validly distributed.
=========================================================
*/

#include <string>
#include <algorithm>

class Solution {
public:
    std::string maxSumOfSquares(int num, int sum) {
        // Approach: Greedy Lexicographical Maximization
        // • Intuition: To maximize the string representation lexicographically while achieving the target digit sum, we should greedily assign the largest possible valid digit at each position from left to right.
        // • Approach: For each position, determine the valid range `[min_val, max_val]` where `min_val = max(0, sum - (num - 1 - i) * 9)` and `max_val = min(9, sum)`. Greedily pick `max_val` to make the leftmost digits as large as possible.
        // • Why it Works: Assigning the maximum allowable digit at each step from left to right directly satisfies the requirement for the largest string representation while maintaining valid bounds for the remaining sum.
        // • Time Complexity (TC): O(num), since we loop exactly 'num' times.
        // • Space Complexity (SC): O(num) to construct and return the result string.

        // Final Approach Selection:
        // By choosing the maximum valid digit at each position from left to right instead of the minimum leftover, we correctly produce the lexicographically largest string representation (`"30"` instead of `"03"` for inputs like num=2, sum=3).

        if ((long long)num * 9 < sum || sum < 0) return "";

        std::string result = "";
        for (int i = 0; i < num; ++i) {
            int min_val = std::max(0, sum - (num - 1 - i) * 9);
            int max_val = std::min(9, sum);
            
            // Choose the largest possible valid digit for this position
            int chosen = max_val;
            result += std::to_string(chosen);
            sum -= chosen;
        }

        if (sum > 0) return "";
        return result;
    }
};
