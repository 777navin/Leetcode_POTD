/*
=========================================================
Date        : 27-09-2026
Problem Name: [1190. Reverse Substrings Between Each Pair of Parentheses](https://leetcode.com/problems/reverse-substrings-between-each-pair-of-parentheses/description/?envType=daily-question&envId=2026-09-27)
Platform    : LeetCode
Difficulty  : Medium
Tags        : String, Stack, Bracket Sequences

Problem Summary:
Given a string containing lower case English letters and parentheses, reverse the strings in each pair of matching parentheses starting from the innermost one. The final result should contain no brackets.

Key Observation:
When we encounter an opening parenthesis, we can save our current state using a stack. When we encounter a closing parenthesis, we reverse the substring accumulated since the last opening parenthesis.
=========================================================
*/

#include <string>
#include <stack>
#include <algorithm>

class Solution {
public:
    /*
    =====================================================
    APPROACH 1: Stack-based Simulation (Most Optimal)
    =====================================================
    
    • Intuition: 
      Use a stack to keep track of previously built string segments when entering nested parentheses.
    
    • Approach: 
      1. Iterate through each character of the string.
      2. If the character is '(', push the current accumulated string onto the stack and reset it.
      3. If the character is ')', reverse the current string, then append it to the top string popped from the stack.
      4. Otherwise, append the character to the current string.
    
    • Why it Works: 
      The stack naturally handles the Last-In, First-Out (LIFO) nature of nested parentheses, allowing us to resolve innermost parentheses first.
    
    • Time Complexity (TC): O(N^2) where N is the length of the string, because reversing strings at each parenthesis level can take up to O(N) operations.
    • Space Complexity (SC): O(N) for storing elements in the stack and current string.
    
    -----------------------------------------------------
    Why this approach is chosen:
    It directly simulates the bracket nesting rules with minimal overhead and conforms cleanly to LeetCode's constraints (1 <= s.length <= 2000).
    -----------------------------------------------------
    */
    std::string reverseParentheses(std::string s) {
        std::stack<std::string> st;
        std::string current = "";
        
        for (char c : s) {
            if (c == '(') {
                st.push(current);
                current = "";
            } else if (c == ')') {
                std::reverse(current.begin(), current.end());
                if (!st.empty()) {
                    current = st.top() + current;
                    st.pop();
                }
            } else {
                current += c;
            }
        }
        
        return current;
    }
};
