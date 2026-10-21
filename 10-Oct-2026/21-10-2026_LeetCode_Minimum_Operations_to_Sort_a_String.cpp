/*
=========================================================
Date        : 21-10-2026
Problem Name: Minimum Operations to Sort a String
Platform: LeetCode
Difficulty: Medium
Tags: Greedy, Sorting, Strings, Math

Problem Summary:
Given a string 's', you can select any proper substring (length < n) 
and sort it. Return the minimum number of operations to make the entire 
string sorted. Return -1 if it's impossible.

Key Observation:
Any string of length >= 3 can be sorted in at most 3 operations. 
We just need to check the conditions for 0, 1, 2, or 3 operations.
=========================================================
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH EXPLANATION
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

1. Optimal Greedy Approach
• Intuition:
  Since we can sort any proper substring, the maximum substring we can sort has length n-1. 
  By observing the boundaries of out-of-order elements, we can determine the exact minimum moves.

• Approach:
  - If the string is already sorted, return 0.
  - If n == 2 and not sorted, return -1 (proper substrings have length 1, sorting them does nothing).
  - Find the first (L) and last (R) misplaced characters by comparing with a sorted copy.
  - If the mismatched range (R - L + 1) < n, we can sort that exact range in 1 operation.
  - Otherwise, we need 2 or 3 operations. 2 operations (prefix then suffix, or vice-versa) work 
    unless the unique global maximum is stuck at index 0 AND the unique global minimum is stuck 
    at index n-1. If both are stuck, we need 3 operations. Otherwise, 2 operations suffice.

• Why it Works:
  Sorting a prefix of length n-1 puts the minimum character at index 0. If the global minimum 
  exists anywhere in the prefix, it moves to the front. Then, sorting the suffix of length n-1 
  sorts everything else. This 2-step process only fails if the min is exclusively at the end 
  and the max is exclusively at the beginning.

• Time Complexity (TC): O(N log N)
  Sorting the string takes O(N log N) time, which dominates the linear scans.

• Space Complexity (SC): O(N)
  We use O(N) auxiliary space to store a sorted copy of the string.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
FINAL APPROACH
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
This approach is chosen because it elegantly breaks down the problem into a fixed set of states 
(0, 1, 2, or 3 operations) using simple condition checks. It runs well within the constraint 
limits and avoids complex dynamic programming or graph traversal.
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minOperations(string s) {
        int n = s.length();
        string sorted_s = s;
        sort(sorted_s.begin(), sorted_s.end());
        
        // Case 0: Already sorted
        if (s == sorted_s) {
            return 0;
        }
        
        // Case -1: Impossible for length 2
        if (n == 2) {
            return -1;
        }
        
        // Find the mismatched boundaries
        int L = 0, R = n - 1;
        while (L < n && s[L] == sorted_s[L]) {
            L++;
        }
        while (R >= 0 && s[R] == sorted_s[R]) {
            R--;
        }
        
        // Case 1: The out-of-order elements fit within a proper substring
        if (R - L + 1 < n) {
            return 1;
        }
        
        // Determine the global minimum and maximum characters
        char min_c = sorted_s[0];
        char max_c = sorted_s[n - 1];
        
        // Check if the global minimum is exclusively at the end
        bool min_only_at_end = (s[n - 1] == min_c) && 
                               (count(s.begin(), s.end() - 1, min_c) == 0);
                               
        // Check if the global maximum is exclusively at the beginning
        bool max_only_at_start = (s[0] == max_c) && 
                                 (count(s.begin() + 1, s.end(), max_c) == 0);
        
        // Case 3: Both min and max are stuck at opposite ends
        if (min_only_at_end && max_only_at_start) {
            return 3;
        }
        
        // Case 2: 2 operations are sufficient
        return 2;
    }
};

// 21-10-2026_LeetCode_Minimum_Operations_to_Sort_a_String.cpp
