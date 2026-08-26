/*
=========================================================
Date        : 26-08-2026
Problem Name: Shortest and Lexicographically Smallest Beautiful String
Platform    : LeetCode
Difficulty  : Medium
Tags        : String, Sliding Window, Two Pointers

Problem Summary:
Given a binary string s and an integer k, find the shortest substring 
that contains exactly k '1's. If there are multiple substrings of the 
same minimal length, return the lexicographically smallest one.

Key Observation:
A minimal valid substring containing k '1's must always start and end 
with '1'. Any leading or trailing '0's only unnecessarily increase its length.
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Brute Force (Generate All Substrings)
---------------------------------------------------------
• Intuition:
  Check every possible substring, count the number of '1's, and track 
  the shortest and lexicographically smallest valid substring.

• Approach:
  1. Iterate over all starting indices i and ending indices j.
  2. Count the number of '1's in substring s[i..j].
  3. If count == k, update the answer if current length is smaller, or 
     if lengths are equal and current substring is lexicographically smaller.

• Why it Works:
  Exhaustively explores all possible substrings ensuring no optimal candidate is missed.

• Time Complexity (TC) : O(N^3) due to generating and comparing substrings of length N.
• Space Complexity (SC): O(N) to store substring slices.
---------------------------------------------------------
*/

/*
---------------------------------------------------------
APPROACH 2: Optimized Sliding Window / Two Pointers (Most Optimal)
---------------------------------------------------------
• Intuition:
  Maintain a variable-length sliding window [left, right] to keep track of 
  the number of '1's in the window. Shrink from the left to discard leading 
  '0's and minimize length while maintaining exactly k '1's.

• Approach:
  1. Expand the right pointer and add s[right] to the '1's count.
  2. When count exceeds k, or when count == k and s[left] == '0', shrink 
     from left while decrementing count appropriately.
  3. Whenever count == k, extract s[left..right] and compare with the best 
     candidate based on minimum length and lexicographical order.

• Why it Works:
  Both left and right pointers traverse the string at most once, and only valid 
  minimal substrings starting with '1' are evaluated.

• Time Complexity (TC) : O(N^2) in worst case due to string comparisons of length up to N.
• Space Complexity (SC): O(1) auxiliary space (excluding result string storage).
---------------------------------------------------------
*/

/*
---------------------------------------------------------
FINAL APPROACH SELECTION:
We choose the Sliding Window (Two Pointers) approach because it processes 
the string in linear window movements O(N) rather than cubic O(N^3) sweeps. 
It ensures optimal runtime and minimal memory footprint while strictly adhering 
to the lexicographical and length constraints.
---------------------------------------------------------
*/

#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n = s.length();
        string best = "";
        int onesCount = 0;
        int left = 0;

        for (int right = 0; right < n; ++right) {
            if (s[right] == '1') {
                onesCount++;
            }

            // Shrink window if count exceeds k or leading characters are '0'
            while (onesCount > k || (left <= right && s[left] == '0')) {
                if (s[left] == '1') {
                    onesCount--;
                }
                left++;
            }

            // Valid candidate found with exactly k '1's
            if (onesCount == k) {
                string candidate = s.substr(left, right - left + 1);
                if (best.empty() || candidate.length() < best.length() || 
                   (candidate.length() == best.length() && candidate < best)) {
                    best = candidate;
                }
            }
        }

        return best;
    }
};
