/*
=========================================================
Date        : 28-09-2026
Problem Name: 1614. Maximum Nesting Depth of the Parentheses
Platform    : LeetCode
Difficulty  : Easy
Tags        : String, Stack

Problem Summary:
Given a valid parentheses string `s` (VPS), calculate its maximum nesting depth. 
The nesting depth is the maximum number of open parentheses '(' that are nested 
inside each other without being closed. Non-parenthesis characters are ignored.

Key Observation:
Since the string is guaranteed to be a Valid Parentheses String (VPS), we do not need 
an actual stack data structure. Incrementing a counter for '(' and decrementing for ')' 
allows us to track the current depth, and the maximum value of this counter gives the result.
=========================================================
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/*
=========================================================
APPROACH 1: Counter-Based Tracking (Optimal)
=========================================================

• Intuition:
  Every '(' increases the current nesting depth, and every ')' decreases it. 
  By keeping track of the peak depth reached during the traversal, we find the maximum nesting depth.

• Approach:
  1. Initialize `current_depth` = 0 and `max_depth` = 0.
  2. Traverse through each character in the string `s`.
  3. If character is '(', increment `current_depth` and update `max_depth = max(max_depth, current_depth)`.
  4. If character is ')', decrement `current_depth`.
  5. Return `max_depth`.

• Why it Works:
  The string is guaranteed to be a valid parentheses string, so open brackets are always properly paired and balanced.
  The maximum value attained by the balance factor at any point corresponds directly to the maximum nesting depth.

• Time Complexity (TC):
  O(N) - Single pass over the string of length N.

• Space Complexity (SC):
  O(1) - Constant auxiliary space used for counter variables.
=========================================================
*/

/*
=========================================================
FINAL APPROACH CHOICE
=========================================================
This single-pass counter approach is chosen because it achieves optimal O(N) time 
complexity while utilizing O(1) space. Using an actual stack data structure is unnecessary 
since the input string is guaranteed to be valid and we only need to track the count.
=========================================================
*/

class Solution {
public:
    int maxDepth(string s) {
        int current_depth = 0;
        int max_depth = 0;

        for (char ch : s) {
            if (ch == '(') {
                current_depth++;
                max_depth = max(max_depth, current_depth);
            } else if (ch == ')') {
                current_depth--;
            }
        }

        return max_depth;
    }
};
