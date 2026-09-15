/*
=========================================================
Date        : 15-09-2026
Problem Name: 2472. Maximum Number of Non-overlapping Palindrome Substrings
Platform    : LeetCode
Difficulty  : Hard
Tags        : Two Pointers, String, Dynamic Programming, Greedy

Problem Summary:
Given a string s and an integer k, find the maximum number of 
non-overlapping palindromic substrings of length at least k.

Key Observation:
Any palindrome of length L >= k can be reduced to a smaller core 
palindrome of length exactly k or k+1 by peeling off its ends.
=========================================================

=========================================================
APPROACH 1: Dynamic Programming (DP)
=========================================================
• Intuition:
  We can compute the maximum non-overlapping palindromes up to each index i.
• Approach:
  Use a DP array dp[i] and expand around centers to find valid palindromes, 
  updating dp[end_index] = max(dp[end_index], dp[start_index - 1] + 1).
• Why it Works:
  It systematically tracks the optimal non-overlapping choices by building 
  on smaller overlapping subproblems.
• Time Complexity (TC): O(N^2)
  Expanding around 2N-1 centers takes quadratic time in the worst case.
• Space Complexity (SC): O(N)
  Requires an array of size N to store DP states.

=========================================================
APPROACH 2: Greedy Search
=========================================================
• Intuition:
  Selecting the shortest possible valid palindrome as early as possible 
  leaves the maximum remaining string for subsequent palindromes.
• Approach:
  Iterate through the string and check if a substring of length k or k+1 
  is a palindrome. If found, increment the count and jump the index forward.
• Why it Works:
  Since any longer palindrome contains a core of length k or k+1, finding 
  and greedily picking this core ensures we don't waste space.
• Time Complexity (TC): O(N * K)
  At each index, we only do a localized check of length k and k+1.
• Space Complexity (SC): O(1)
  We only use a few integer variables for iteration and counting.

=========================================================
FINAL APPROACH
=========================================================
• Why this approach is chosen:
  The Greedy Search approach is much simpler, highly intuitive, and 
  completely avoids the overhead of a DP array.
• Why it is better than the previous ones:
  It optimizes the Space Complexity down to O(1) and often runs significantly 
  faster in practice by jumping over processed sections.
*/

#include <iostream>
#include <string>

using namespace std;

class Solution {
private:
    // Helper function to check if a substring is a palindrome
    bool isPalindrome(const string& s, int left, int right) {
        while (left < right) {
            if (s[left++] != s[right--]) {
                return false;
            }
        }
        return true;
    }

public:
    int maxPalindromes(string s, int k) {
        int n = s.length();
        int count = 0;
        int i = 0;
        
        while (i <= n - k) {
            // Check if there's a palindrome of length k
            if (isPalindrome(s, i, i + k - 1)) {
                count++;
                i += k; // Jump index to avoid overlap
            } 
            // Check if there's a palindrome of length k + 1
            else if (i + k < n && isPalindrome(s, i, i + k)) {
                count++;
                i += k + 1; // Jump index to avoid overlap
            } 
            // Move forward if no valid core palindrome starts at i
            else {
                i++;
            }
        }
        
        return count;
    }
};
