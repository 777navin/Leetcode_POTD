/*
=========================================================
Date        : 08-10-2026
Problem Name: Remove Outermost Parentheses
Platform    : LeetCode
Difficulty  : Easy
Tags        : String, Stack, Bracket Sequences

Problem Summary:
Given a valid parentheses string `s`, split it into its primitive valid components.
A primitive valid string is non-empty and cannot be split into smaller valid strings.
Return the result string after removing the outermost parentheses of each primitive part.

Key Observation:
We can keep track of the depth/balance of open parentheses. An opening bracket '(' is 
outermost if balance is 0 before adding it, and a closing bracket ')' is outermost if 
balance becomes 0 after processing it.
=========================================================
*/

#include <iostream>
#include <string>

/*
---------------------------------------------------------
APPROACH 1: Stack Simulation (Brute / Standard)
---------------------------------------------------------
• Intuition:
  Use a stack to keep track of parentheses. Non-outermost characters are identified by checking stack depth.

• Approach:
  Traverse the string. Push '(' to the stack and append it to the result if the stack depth before pushing is > 0.
  Pop for ')' and append to the result if the stack depth after popping is > 0.

• Why it Works:
  The stack explicitly tracks nesting depth. Depth 0 corresponds strictly to the outermost parentheses.

• Time Complexity (TC):
  O(N), where N is the length of string s.

• Space Complexity (SC):
  O(N) auxiliary space for the stack in the worst case.
---------------------------------------------------------
*/

/*
---------------------------------------------------------
APPROACH 2: Counter / Balance Tracking (Optimal)
---------------------------------------------------------
• Intuition:
  Instead of an explicit stack, use a integer counter to maintain the balance of parentheses.

• Approach:
  Iterate through `s` using an integer `count` = 0.
  - If c == '(': Append to result if `count` > 0, then increment `count`.
  - If c == ')': Decrement `count`, then append to result if `count` > 0.

• Why it Works:
  An integer count perfectly mimics stack depth without any extra memory allocations or stack overhead.

• Time Complexity (TC):
  O(N), traversing the string once.

• Space Complexity (SC):
  O(1) auxiliary space (excluding string output).
---------------------------------------------------------
*/

/*
=========================================================
FINAL APPROACH: Counter / Balance Tracking
=========================================================
• Why Chosen:
  It achieves linear time complexity while completely avoiding external stack overhead.
• Advantages:
  O(1) auxiliary space, clean implementation, and optimal performance for string length up to 10^5.
=========================================================
*/

class Solution {
public:
    std::string removeOuterParentheses(std::string s) {
        std::string result = "";
        int count = 0;

        for (char c : s) {
            if (c == '(') {
                if (count > 0) {
                    result += c;
                }
                count++;
            } else {
                count--;
                if (count > 0) {
                    result += c;
                }
            }
        }

        return result;
    }
};
