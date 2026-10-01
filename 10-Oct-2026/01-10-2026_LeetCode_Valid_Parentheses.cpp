/*
=========================================================
Date        : 01-10-2026
Problem Name: Valid Parentheses
Platform    : LeetCode
Difficulty  : Easy
Tags        : String, Stack, Bracket Sequences

Problem Summary:
Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', 
determine if the input string is valid. An input string is valid if open brackets 
are closed by the same type of brackets in the correct order and every close bracket 
has a corresponding open bracket.

Key Observation:
The most recently opened bracket must be closed first (Last-In, First-Out order), 
which naturally maps to a Stack data structure.
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Stack Data Structure
---------------------------------------------------------
• Intuition:
  Parentheses nesting follows a LIFO (Last-In-First-Out) order. Using a stack allows us to 
  keep track of expected closing brackets for any open bracket encountered.

• Approach:
  1. Iterate through each character in the string s.
  2. If an opening bracket is found, push the matching closing bracket onto the stack.
  3. If a closing bracket is found, check if the stack is empty or if the top of the stack 
     matches the current character. If not, return false; otherwise, pop from the stack.
  4. At the end, return true if the stack is empty (all open brackets matched).

• Why it Works:
  Pushing the expected closing bracket directly simplifies matching logic, ensuring that 
  brackets are matched in proper sequence.

• Time Complexity (TC): O(N) — where N is the length of the string, as we iterate through it once.
• Space Complexity (SC): O(N) — in the worst case (e.g., all open brackets), the stack holds N characters.
---------------------------------------------------------
*/

/*
---------------------------------------------------------
FINAL APPROACH SELECTION
---------------------------------------------------------
The Stack approach is optimal for this problem. It achieves linear time complexity 
O(N) with a simple implementation, fully adhering to the problem constraints without 
unnecessary overhead.
---------------------------------------------------------
*/

#include <iostream>
#include <stack>
#include <string>

class Solution {
public:
    bool isValid(std::string s) {
        // If length is odd, it can never be balanced
        if (s.length() % 2 != 0) return false;

        std::stack<char> st;
        
        for (char c : s) {
            if (c == '(') {
                st.push(')');
            } else if (c == '{') {
                st.push('}');
            } else if (c == '[') {
                st.push(']');
            } else {
                // If stack is empty or top doesn't match the closing bracket
                if (st.empty() || st.top() != c) {
                    return false;
                }
                st.pop();
            }
        }
        
        // Valid if no unmatched opening brackets remain
        return st.empty();
    }
};
