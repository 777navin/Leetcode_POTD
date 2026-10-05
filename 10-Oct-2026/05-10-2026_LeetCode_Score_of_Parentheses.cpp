/*
=========================================================
Date        : 05-10-2026
Problem Name: Score of Parentheses
Platform    : LeetCode
Difficulty  : Medium
Tags        : String, Stack, Bracket Sequences

Problem Summary:
Given a balanced parentheses string s, return its calculated score.
- "()" has a score of 1.
- AB has a score of A + B, where A and B are balanced parentheses strings.
- (A) has a score of 2 * A, where A is a balanced parentheses string.

Key Observation:
Every empty pair "()" contributes 2^d to the total score, where d is the nesting depth of that "()". We can either compute this with a stack or by tracking depth directly.
=========================================================
*/

#include <iostream>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

/*
---------------------------------------------------------
APPROACH 1: Stack Approach
---------------------------------------------------------
• Intuition:
  Use a stack to maintain scores at each depth level. Pushing 0 represents opening a new scope.

• Approach:
  - Iterate through characters in string s.
  - If '(', push 0 onto stack to start a new inner expression score.
  - If ')', pop top value v. The score of current block is max(2 * v, 1). Add this score to the new top of stack.

• Why it Works:
  - Evaluates scores hierarchically from innermost nested brackets outward, correctly applying A + B and 2 * A rules.

• Time Complexity (TC): O(N) — single pass through string of length N.
• Space Complexity (SC): O(N) — space for stack depth up to N/2.
---------------------------------------------------------
*/

/*
---------------------------------------------------------
APPROACH 2: Counting Core Parentheses (O(1) Space)
---------------------------------------------------------
• Intuition:
  Distribute the multiplication: (A + B) * 2 = 2*A + 2*B. Thus, each "()" contributes 2^(nesting_depth) to the overall score.

• Approach:
  - Track current depth using a counter variable when encountering '('.
  - Decrement depth when encountering ')'.
  - When a primitive "()" pair is detected (i.e., s[i] == ')' and s[i-1] == '('), add 1 << depth to total score.

• Why it Works:
  - Every primitive pair "()" is nested inside 'depth' outer pairs, effectively getting multiplied by 2 'depth' times.

• Time Complexity (TC): O(N) — single pass through the string.
• Space Complexity (SC): O(1) — constant auxiliary space.
---------------------------------------------------------
*/

/*
=========================================================
FINAL APPROACH CHOICE
=========================================================
Approach 2 (Counting Core Parentheses) is chosen as the final solution.
It achieves optimal performance with O(N) time complexity and O(1) auxiliary space,
avoiding the extra memory overhead of a stack while remaining clean and concise.
=========================================================
*/

class Solution {
public:
    int scoreOfParentheses(string s) {
        int score = 0;
        int depth = 0;
        int n = s.length();

        for (int i = 0; i < n; ++i) {
            if (s[i] == '(') {
                depth++;
            } else {
                depth--;
                // If this ')' directly closes the previous '(', it's a core "()" pair
                if (s[i - 1] == '(') {
                    score += (1 << depth);
                }
            }
        }

        return score;
    }
};
