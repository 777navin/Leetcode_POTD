/*
=========================================================
Date        : 06-10-2026
Problem Name: Minimum Add to Make Parentheses Valid
Platform    : LeetCode
Difficulty  : Medium
Tags        : String, Stack, Greedy

Problem Summary:
Given a string s consisting of '(' and ')' parentheses, find the minimum 
number of parentheses insertions required to make the string valid. A valid 
string has properly matched opening and closing brackets in sequence.

Key Observation:
Unmatched closing brackets ')' must be added immediately when encountered, 
while remaining unmatched opening brackets '(' at the end also require closing 
counterparts.
=========================================================
*/

#include <iostream>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

/*
=========================================================
APPROACH 1: Stack-Based Matching
=========================================================

• Intuition:
  Use a stack to simulate bracket matching. Open brackets are stored until a 
  matching close bracket neutralizes them.

• Approach:
  Iterate through the string. Push '(' onto the stack. When encountering ')', 
  if the top of the stack is '(', pop it. Otherwise, push ')' onto the stack. 
  The final size of the stack is the answer.

• Why it Works:
  The stack maintains unmatched parentheses in proper order. Any remaining elements 
  in the stack represent unpaired brackets that need insertions.

• Time Complexity (TC):
  O(N) - Single pass over string of length N.

• Space Complexity (SC):
  O(N) - Stack can hold up to N characters in the worst case.
*/


/*
=========================================================
APPROACH 2: Greedy Counter (Optimized Space)
=========================================================

• Intuition:
  Instead of storing characters in a stack, track balance counts of open and 
  unmatched close brackets using simple integer variables.

• Approach:
  Maintain `open_needed` for unmatched '(' and `add_count` for unmatched ')'. 
  Increment `open_needed` on '('. On ')', if `open_needed > 0`, decrement it; 
  otherwise, increment `add_count`. Return `open_needed + add_count`.

• Why it Works:
  Order is strictly left-to-right. An unmatched ')' can never pair with future '(', 
  so it immediately increments the required additions count.

• Time Complexity (TC):
  O(N) - Single pass over the string.

• Space Complexity (SC):
  O(1) - Uses only constant auxiliary variables.
*/

/*
=========================================================
FINAL APPROACH SELECTION
=========================================================
Approach 2 (Greedy Counter) is selected because:
• It reduces space complexity from O(N) to O(1) by avoiding extra stack allocations.
• It processes the string in a single linear pass with minimal overhead.
• It provides optimal performance for competitive programming and production use.
=========================================================
*/

class Solution {
public:
    int minAddToMakeValid(string s) {
        int open_needed = 0; // Tracks unmatched '('
        int add_count = 0;   // Tracks unmatched ')' requiring insertion

        for (char c : s) {
            if (c == '(') {
                open_needed++;
            } else {
                if (open_needed > 0) {
                    open_needed--; // Valid pair formed
                } else {
                    add_count++;   // Unmatched ')', needs '(' insertion
                }
            }
        }

        return open_needed + add_count;
    }
};
