/*
=========================================================
Date        : 02-10-2026
Problem Name: Generate Parentheses
Platform    : LeetCode
Difficulty  : Medium
Tags        : String, Dynamic Programming, Backtracking

Problem Summary:
Given n pairs of parentheses, generate all combinations 
of well-formed parentheses. A string of parentheses is 
well-formed if every opening bracket has a corresponding 
closing bracket in valid sequence.

Key Observation:
At any point during string construction, we can add '(' if 
the count of '(' is less than n, and we can add ')' only if 
the count of ')' is less than the count of '('.
=========================================================
*/

#include <vector>
#include <string>

using namespace std;

/*
---------------------------------------------------------
APPROACH 1: Backtracking (Decision Tree Traversal)
---------------------------------------------------------

• Intuition:
  Build the parenthesis string character by character by placing 
  '(' or ')' while maintaining validity rules at each step.

• Approach:
  - Track open and close parenthesis counts using recursive state.
  - If open < n, recurse adding '('.
  - If close < open, recurse adding ')'.
  - Base case: string length equals 2 * n, append to answer.

• Why it Works:
  By ensuring close count never exceeds open count, we guarantee 
  that every generated string is well-formed without generating 
  invalid combinations.

• Time Complexity (TC):
  O(4^n / sqrt(n)) - Bounded by the n-th Catalan number C_n.

• Space Complexity (SC):
  O(n) - Maximum depth of the recursion stack and temporary string buffer.
---------------------------------------------------------
*/

/*
---------------------------------------------------------
FINAL APPROACH SELECTION:
---------------------------------------------------------
• Chosen Approach: Backtracking (Decision Tree Traversal)
• Reason          : It generates only valid well-formed combinations directly,
                    avoiding brute-force generation of invalid permutations.
                    It provides optimal time complexity and minimum memory usage.
---------------------------------------------------------
*/

class Solution {
private:
    void backtrack(vector<string>& result, string& current, int open, int close, int n) {
        // Base case: string reaches target length 2 * n
        if (current.length() == 2 * n) {
            result.push_back(current);
            return;
        }

        // Add an opening parenthesis if we haven't reached limit 'n'
        if (open < n) {
            current.push_back('(');
            backtrack(result, current, open + 1, close, n);
            current.pop_back(); // Backtrack
        }

        // Add a closing parenthesis if it wouldn't exceed open count
        if (close < open) {
            current.push_back(')');
            backtrack(result, current, open, close + 1, n);
            current.pop_back(); // Backtrack
        }
    }

public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        string current = "";
        backtrack(result, current, 0, 0, n);
        return result;
    }
};
