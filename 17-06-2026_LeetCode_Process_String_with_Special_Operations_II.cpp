/*
Date: 17-06-2026
Problem Name: Process String with Special Operations II
Platform: LeetCode
Difficulty: Hard
Tags: String, Simulation, Math, Backtracking

Problem Summary:
Given a string 's' containing lowercase letters and special characters ('*', '#', '%'), 
and an integer 'k', find the k-th character (0-indexed) of the final processed string.
- '*' : Removes the last character of the current string.
- '#' : Duplicates the current string (concatenates it to itself).
- '%' : Reverses the current string.

Methods to Solve:
1. Brute Force Simulation (TLE)
2. Reverse Traversal / Backtracking (Optimal Approach)

For EACH method include:

Method 1: Brute Force Simulation
- Intuition: Actually build the string applying the operations step-by-step.
- Approach: Use a string or stack to build the result.
- Dry Run: For "cd%#*#", string builds as "c" -> "cd" -> "dc" -> "dcdc" -> "dcd" -> "dcddcd".
- Time Complexity: O(2^N) because '#' doubles the length each time.
- Space Complexity: O(2^N) to store the massive string.
- Why better than previous method: N/A (Baseline).
- When to use: Only when 'k' and string length are extremely small.

Method 2: Reverse Traversal
- Intuition: Since string length can reach 10^15, we can't build it. Instead, we can 
  store the lengths of the string at each step. By starting from 'k' at the final step 
  and walking backward, we can mathematically trace where the character at index 'k' 
  originally came from.
- Approach: 
  1. Forward Pass: Track the string length at each step in an array `len`.
  2. Backward Pass: Traverse from the end. 
     - If '*': Do nothing. The index doesn't shift when characters are removed from the end.
     - If '#': If `currK` is in the duplicated (second) half, map it back to the first half (`currK -= len[i]`).
     - If '%': Mirror the index across the current string length (`currK = len[i] - 1 - currK`).
     - If character: Check if this was the exact character inserted at this step (`currK == len[i]`).
- Dry Run (s = "cd%#*#", k = 3):
  - Lengths: [0, 1, 2, 2, 4, 3, 6]
  - Backtrack from k = 3:
    - i = 5 ('#'): len=3. k(3) >= 3 -> k = 0
    - i = 4 ('*'): len=4. k remains 0
    - i = 3 ('#'): len=2. k(0) < 2 -> k remains 0
    - i = 2 ('%'): len=2. k = 2 - 1 - 0 = 1
    - i = 1 ('d'): len=1. k(1) == len[1](1). Found! Return 'd'.
- Time Complexity: O(N) where N is the length of string 's'.
- Space Complexity: O(N) to store the intermediate lengths.
- Why better than previous method: Avoids exponential memory and time limits.
- When to use: Always for this problem due to large constraints.

Comparison Table:
Method | TC | SC | Best Use Case
-------|----|----|--------------
Brute Force | O(2^N) | O(2^N) | Process String I (Small Constraints)
Reverse Traversal| O(N) | O(N) | Process String II (Large Constraints)

Final Recommended Solution: Reverse Traversal
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Solution {
public:
    char processStr(std::string s, long long k) {
        int n = s.length();
        
        // len[i] stores the length of the string after processing s[0...i-1]
        std::vector<long long> len(n + 1, 0);
        
        // Forward pass: Calculate lengths at each step
        for (int i = 0; i < n; ++i) {
            if (s[i] == '*') {
                len[i + 1] = std::max(0LL, len[i] - 1);
            } else if (s[i] == '#') {
                len[i + 1] = len[i] * 2;
            } else if (s[i] == '%') {
                len[i + 1] = len[i];
            } else {
                len[i + 1] = len[i] + 1;
            }
        }
        
        // Safety check for out of bounds
        if (k < 0 || k >= len[n]) return '.';
        
        // Backward pass: Trace the origin of index 'k'
        long long currK = k;
        for (int i = n - 1; i >= 0; --i) {
            if (s[i] == '*') {
                // Do nothing. Removing a character from the end 
                // does not change the index of the characters before it.
                continue;
            } else if (s[i] == '#') {
                // If the character is in the duplicated second half, 
                // map it back to its original position in the first half.
                if (currK >= len[i]) {
                    currK -= len[i];
                }
            } else if (s[i] == '%') {
                // The string was reversed, so mirror the index.
                currK = len[i] - 1 - currK;
            } else {
                // If it's a normal character and currK matches the length 
                // before it was added, this is our target character.
                if (currK == len[i]) {
                    return s[i];
                }
            }
        }
        
        return '.';
    }
};
