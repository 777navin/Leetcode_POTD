/*
=========================================================
Date        : 04-10-2026
Problem Name: Valid Parenthesis String
Platform    : LeetCode
Difficulty  : Medium
Tags        : String, Dynamic Programming, Stack, Greedy, Bracket Sequences

Problem Summary:
Given a string s consisting of characters '(', ')', and '*', return true if s is a valid parenthesis string.
The wildcard character '*' can be treated as a left parenthesis '(', a right parenthesis ')', or an empty string "".

Key Observation:
A string is valid if at no point the count of closing parentheses exceeds the maximum possible open parentheses,
and at the end, the minimum required open parentheses count can reach zero.
=========================================================
*/

#include <iostream>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 1: RECURSION / BACKTRACKING (BRUTE FORCE)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  Try all three possibilities for each wildcard '*' (as '(', ')', or empty string)
  and check if any path results in a valid balanced string.

• Approach:
  - Define a recursive helper function `solve(index, openCount)`.
  - If `openCount < 0`, return false immediately.
  - When `index == s.length()`, return `openCount == 0`.
  - For '(', increment `openCount`. For ')', decrement `openCount`.
  - For '*', recursively evaluate `openCount + 1`, `openCount - 1`, and `openCount`.

• Why it Works:
  It systematically explores the full decision tree of wildcard replacements to guarantee
  finding a valid solution if one exists.

• Time Complexity (TC):
  O(3^N) where N is the length of string s.

• Space Complexity (SC):
  O(N) auxiliary recursion stack space.
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 2: TWO STACKS (BETTER)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  Track indices of open brackets '(' and stars '*' separately to match ')' greedily first,
  and then ensure remaining '(' can be matched by '*' appearing after them.

• Approach:
  - Use `openStack` for indices of '(' and `starStack` for indices of '*'.
  - Iterate through `s`:
    - Push indices for '(' and '*'.
    - For ')', pop from `openStack` first; if empty, pop from `starStack`; if both empty, return false.
  - After iteration, pair remaining '(' with '*': while both non-empty, pop if `openStack.top() < starStack.top()`.
  - Return `openStack.empty()`.

• Why it Works:
  Prioritizes matching explicit parentheses before relying on wildcards. Post-processing ensures
  stars are positioned to the right of unmatched open brackets.

• Time Complexity (TC):
  O(N) single pass and linear cleanup.

• Space Complexity (SC):
  O(N) to store indices in two stacks.
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 3: GREEDY RANGE COUNTER (MOST OPTIMAL)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  Maintain a dynamic range `[low, high]` representing the minimum and maximum possible number
  of open parentheses at any position.

• Approach:
  - Initialize `low = 0` and `high = 0`.
  - For '(': increment both `low` and `high`.
  - For ')': decrement both `low` and `high`.
  - For '*': decrement `low` (treat as ')') and increment `high` (treat as '(').
  - Clamp `low = max(low, 0)` since open brackets cannot drop below zero.
  - If `high < 0`, return false (too many ')' encountered).
  - At the end, return `low == 0`.

• Why it Works:
  The range `[low, high]` covers all reachable open parenthesis counts. As long as `high >= 0`
  throughout and `low == 0` at the end, a valid parenthesis assignment exists.

• Time Complexity (TC):
  O(N) single pass traversal over string s.

• Space Complexity (SC):
  O(1) auxiliary space using two counter variables.
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
FINAL APPROACH SELECTION: GREEDY RANGE COUNTER
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Chosen because it achieves optimal O(N) time and O(1) space complexity.
• Eliminates memory allocation overhead compared to the two-stack approach.
• Handles all wildcard combinations simultaneously by maintaining bounds on valid balance counts.
*/

class Solution {
public:
    bool checkValidString(string s) {
        int low = 0;   // Minimum possible open parentheses count
        int high = 0;  // Maximum possible open parentheses count

        for (char c : s) {
            if (c == '(') {
                low++;
                high++;
            } else if (c == ')') {
                low--;
                high--;
            } else { // c == '*'
                low--;   // Treat '*' as ')'
                high++;  // Treat '*' as '('
            }

            // If maximum possible open parentheses is negative, string is invalid
            if (high < 0) {
                return false;
            }

            // Minimum open parentheses cannot drop below 0
            if (low < 0) {
                low = 0;
            }
        }

        // Valid if minimum required open parentheses at the end is 0
        return low == 0;
    }
};
