/*
=========================================================
Date        : 03-10-2026
Problem Name: Longest Valid Parentheses
Platform    : LeetCode
Difficulty  : Hard
Tags        : String, Dynamic Programming, Stack

Problem Summary:
Given a string containing just the characters '(' and ')', return the length of the 
longest valid (well-formed) parentheses substring.

Key Observation:
Using a stack to keep track of the indices of unmatched parentheses allows us to 
calculate the length of valid substrings by measuring the distance between current 
indices and the last unmatched parenthesis index.
=========================================================
*/

/*
---------------------------------------------------------
1. Stack Approach
---------------------------------------------------------
• Intuition:
  We can track the boundaries of valid substring chunks by keeping the indices of 
  unmatched parentheses in a stack.

• Approach:
  Push -1 to the stack as a base index. Iterate through the string: push index of '('; 
  for ')', pop the stack. If stack becomes empty, push current index as new base; 
  otherwise, update max length with (i - stack.top()).

• Why it Works:
  The element at the top of the stack represents the boundary right before the start 
  of the current valid parentheses substring.

• Time Complexity (TC): O(N) - Single pass through the string of length N.
• Space Complexity (SC): O(N) - For storing indices in the stack in worst case.

---------------------------------------------------------
2. Two-Pointer / Two-Pass Approach (Most Optimal)
---------------------------------------------------------
• Intuition:
  A valid parentheses substring must have an equal number of left and right brackets, 
  and at no point from left to right can right brackets exceed left brackets.

• Approach:
  Scan left-to-right keeping count of '(' and ')'. If right == left, update max length; 
  if right > left, reset counts. Repeat right-to-left to handle cases where left > right.

• Why it Works:
  Left-to-right pass catches all balanced substrings and cases where left <= right, while 
  the right-to-left pass catches cases where left > right.

• Time Complexity (TC): O(N) - Two linear scans through the string.
• Space Complexity (SC): O(1) - Uses only constant extra space for variables.
*/

/*
---------------------------------------------------------
FINAL APPROACH SELECTION
---------------------------------------------------------
Chosen Approach: Stack Approach (Class Solution)
Reason: It is standard, clean, intuitive for stack-based bracket matching, runs in 
O(N) time, and easily handles all edge cases in a single pass.
*/

#include <iostream>
#include <string>
#include <stack>
#include <algorithm>

class Solution {
public:
    int longestValidParentheses(std::string s) {
        std::stack<int> st;
        st.push(-1);
        int maxLen = 0;

        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                st.push(i);
            } else {
                st.pop();
                if (st.empty()) {
                    st.push(i);
                } else {
                    maxLen = std::max(maxLen, i - st.top());
                }
            }
        }

        return maxLen;
    }
};
