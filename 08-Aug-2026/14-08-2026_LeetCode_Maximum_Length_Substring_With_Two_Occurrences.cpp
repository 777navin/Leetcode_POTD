/*
=========================================================
Date        : 14-08-2026
Problem Name: 3090. Maximum Length Substring With Two Occurrences
Platform    : LeetCode
Difficulty  : Easy
Tags        : Hash Table, String, Sliding Window

Problem Summary:
Given a string s, find the maximum length of a contiguous substring
such that every unique character in that substring appears at most 
two times.

Key Observation:
Since we need a contiguous valid substring, maintaining a frequency count
over a sliding window [left, right] allows dynamic expansion and contraction.
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Brute Force
---------------------------------------------------------
• Intuition:
  Check every possible substring and count character frequencies to find the longest valid one.

• Approach:
  - Generate all pairs of (i, j) where 0 <= i <= j < n.
  - Count frequencies of all characters in s[i..j].
  - If no character appears > 2 times, update max length with (j - i + 1).

• Why it Works:
  It exhaustively evaluates all candidate substrings, guaranteeing the optimal length.

• Time Complexity (TC) : O(n^2) or O(n^3) depending on frequency check.
• Space Complexity (SC): O(1) auxiliary space (character frequency array of fixed size 26).
---------------------------------------------------------

---------------------------------------------------------
APPROACH 2: Optimized (Two-Pointer / Sliding Window)
---------------------------------------------------------
• Intuition:
  Expand the window by moving the right pointer; when any character frequency exceeds 2,
  shrink the window from the left until the invariant is restored.

• Approach:
  - Maintain a frequency array of size 26 and two pointers `left = 0` and `right = 0`.
  - For each character at `right`, increment its count.
  - While `count[s[right] - 'a'] > 2`, decrement `count[s[left] - 'a']` and increment `left`.
  - Update `maxLength = max(maxLength, right - left + 1)`.

• Why it Works:
  Both pointers move monotonically from left to right (at most n steps each), ensuring all maximal
  valid windows are evaluated in linear time.

• Time Complexity (TC) : O(n) where n is the length of string s.
• Space Complexity (SC): O(1) using a fixed-size frequency array of 26 integers.
---------------------------------------------------------
*/

/*
=========================================================
FINAL APPROACH CHOICE:
The Sliding Window approach is selected because it processes the string in a single 
linear pass (O(n) time) compared to the O(n^2) brute force method, achieving optimal 
time and space efficiency.
=========================================================
*/

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maximumLengthSubstring(string s) {
        int n = s.length();
        vector<int> freq(26, 0);
        int maxLen = 0;
        int left = 0;

        for (int right = 0; right < n; ++right) {
            freq[s[right] - 'a']++;

            // Shrink window until the frequency of s[right] is <= 2
            while (freq[s[right] - 'a'] > 2) {
                freq[s[left] - 'a']--;
                left++;
            }

            maxLen = max(maxLen, right - left + 1);
        }

        return maxLen;
    }
};
