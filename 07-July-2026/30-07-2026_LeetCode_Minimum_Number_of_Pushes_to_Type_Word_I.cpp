/*
=========================================================
Date        : 30-07-2026
Problem Name: Minimum Number of Pushes to Type Word I
Platform    : LeetCode
Difficulty  : Easy
Tags        : Math, String, Greedy

Problem Summary:
We are given a string `word` containing distinct lowercase English letters.
We need to map letters to keys 2 through 9 on a keypad such that the total 
number of key pushes required to type `word` is minimized.

Key Observation:
Since there are 8 available keys (2 to 9) and all characters in `word` are distinct, 
we can place the first 8 characters on the 1st position of each key, the next 8 
characters on the 2nd position, and so on.
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Greedy Mapping (Optimal)
---------------------------------------------------------
• Intuition:
  To minimize pushes, we should fill the first position of all 8 available keys 
  before moving to the second position on any key.

• Approach:
  - Since all characters are distinct, length `n` tells us how many total characters exist.
  - The first 8 characters require 1 push each.
  - The next 8 characters (if present) require 2 pushes each.
  - The next 8 characters require 3 pushes each, and so on.
  - We can iterate through groups of 8 characters and compute the total cost.

• Why it Works:
  Placing characters in earlier key positions minimizes the multiplier (pushes) applied to each letter.

• Time Complexity (TC):
  O(1) - Since word length is at most 26 (all distinct lowercase English letters).

• Space Complexity (SC):
  O(1) - Uses a constant amount of auxiliary space.
*/

/*
=========================================================
FINAL APPROACH CHOICE: Greedy Mapping
=========================================================
• This is the most optimal approach as it uses simple arithmetic logic on groups of 8.
• It runs in O(1) time and space complexity without requiring complex data structures.
=========================================================
*/

#include <string>

class Solution {
public:
    int minimumPushes(std::string word) {
        int n = word.length();
        int totalPushes = 0;
        int presses = 1;

        while (n > 0) {
            int currentBatch = std::min(n, 8);
            totalPushes += currentBatch * presses;
            n -= currentBatch;
            presses++;
        }

        return totalPushes;
    }
};
