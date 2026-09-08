/*
=========================================================
Date        : 08-09-2026
Problem Name: 3870. Count Commas in Range
Platform    : LeetCode
Difficulty  : Easy
Tags        : Math

Problem Summary:
Given an integer n, calculate the total number of commas used when writing
all integers from 1 to n (inclusive) in standard number formatting.
A comma is placed after every three digits from the right, so numbers with
fewer than 4 digits contain no commas.

Key Observation:
Since n <= 10^5, every number from 1,000 to n has between 4 and 6 digits,
meaning each such number contains exactly one comma, while numbers < 1000 have zero.
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Brute Force (Simulation)
---------------------------------------------------------
• Intuition:
  Iterate through each number from 1 to n, convert it to a string or inspect
  its digit length, and count how many commas it requires.

• Approach:
  Loop `i` from 1 to n. For each number, determine its digit length `L`.
  The number of commas is `(L - 1) / 3`. Sum this value for all numbers.

• Why it Works:
  Directly simulates the formatting rule for every number in the range [1, n].

• Time Complexity (TC):
  O(n) — requires checking each number up to n.

• Space Complexity (SC):
  O(1) — constant extra space.
---------------------------------------------------------
*/

/*
---------------------------------------------------------
APPROACH 2: Mathematical / Direct Range Count (Most Optimal)
---------------------------------------------------------
• Intuition:
  Numbers with < 4 digits (1 to 999) have 0 commas. Numbers with 4 to 6 digits
  (1,000 to 999,999) have exactly 1 comma.

• Approach:
  Since the constraint is 1 <= n <= 10^5, no number reaches 1,000,000 (which would have 2 commas).
  Thus, any number >= 1000 contributes exactly 1 comma.
  If n < 1000, the answer is 0; otherwise, the answer is n - 999.

• Why it Works:
  Every integer in [1000, n] has 4, 5, or 6 digits, each having exactly one comma.

• Time Complexity (TC):
  O(1) — single arithmetic operation and conditional check.

• Space Complexity (SC):
  O(1) — no auxiliary space needed.
---------------------------------------------------------
*/

/*
=========================================================
FINAL APPROACH:
Chosen Approach: Mathematical / Direct Range Count
Why:
- It runs in pure O(1) time and O(1) auxiliary space.
- Directly leverages the constraint n <= 10^5 to eliminate any looping or string conversion.
=========================================================
*/

#include <algorithm>

class Solution {
public:
    int countCommas(int n) {
        if (n < 1000) {
            return 0;
        }
        return n - 999;
    }
};
