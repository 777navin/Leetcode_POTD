/*
=========================================================
Date        : 09-10-2026
Problem Name: Minimum Insertions to Balance a Parentheses String
Platform    : LeetCode
Difficulty  : Medium
Tags        : String, Stack, Greedy

Problem Summary:
Given a parentheses string containing only '(' and ')', calculate the minimum number 
of insertions required to make the string balanced. A string is balanced if every '(' 
has a corresponding consecutive '))' after it.

Key Observation:
Instead of using an explicit stack, track open brackets using a counter. Whenever 
encountering closing brackets, ensure they form consecutive pairs '))' and consume an open bracket.
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Stack Simulation
---------------------------------------------------------
• Intuition:
  Use a stack to keep track of unmatched open brackets '('. When encountering closing 
  brackets, check if they form consecutive pairs '))' and match them with '('.

• Approach:
  - Iterate through the string.
  - Push '(' to the stack.
  - For ')', check if the next character is also ')'. If so, consume both; otherwise, insert 1 ')' to make it '))'.
  - If stack is empty when matching '))', insert 1 '(' first.
  - At the end, each remaining '(' in stack requires 2 ')'.

• Why it Works:
  It explicitly models the matching process using stack operations, ensuring proper order and nesting.

• Time Complexity (TC): O(N) - Single pass through the string of length N.
• Space Complexity (SC): O(N) - Stack space needed for unmatched open brackets.

---------------------------------------------------------
APPROACH 2: Greedy Counter (Optimal Space)
---------------------------------------------------------
• Intuition:
  Replace the stack with a counter tracking open brackets. Maintain the count of required 
  insertions continuously during a single linear traversal.

• Approach:
  - Maintain `open` (count of needed unmatched '(') and `insertions` (total insertions needed).
  - On '(': increment `open`.
  - On ')': if the next character is also ')', advance index; else increment `insertions` (adding missing ')').
  - If `open > 0`, decrement `open` (matched with current '))'). Otherwise, increment `insertions` (adding missing '(').
  - After processing, add `2 * open` to `insertions` for unmatched open brackets.

• Why it Works:
  All '(' are identical in nested scope for this problem, so tracking only the depth (count) 
  is sufficient without needing explicit storage.

• Time Complexity (TC): O(N) - Traverses string once.
• Space Complexity (SC): O(1) - Uses constant extra space.
*/

/*
---------------------------------------------------------
FINAL APPROACH SELECTION
---------------------------------------------------------
Approach 2 (Greedy Counter) is chosen because it achieves optimal O(1) auxiliary 
space while maintaining O(N) time complexity. It eliminates stack overhead and handles 
all edge cases (missing '(' or missing ')') in a single linear pass.
*/

class Solution {
public:
    int minInsertions(string s) {
        int insertions = 0;
        int open = 0;
        int n = s.length();

        for (int i = 0; i < n; i++) {
            if (s[i] == '(') {
                open++;
            } else {
                // If it's a single ')', check if the next character is also ')'
                if (i + 1 < n && s[i + 1] == ')') {
                    i++; // Consume the second ')'
                } else {
                    insertions++; // Need to insert one ')' to make "))"
                }

                // Match with an existing '(' if available, otherwise insert a '('
                if (open > 0) {
                    open--;
                } else {
                    insertions++; // Need to insert one '('
                }
            }
        }

        // Each remaining unmatched '(' requires 2 ')'
        insertions += open * 2;

        return insertions;
    }
};
