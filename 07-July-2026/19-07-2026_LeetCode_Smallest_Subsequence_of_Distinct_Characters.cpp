/*
=========================================================
Date        : 19-07-2026
Problem Name: Smallest Subsequence of Distinct Characters
Platform    : LeetCode
Difficulty  : Medium
Tags        : String, Stack, Greedy, Monotonic Stack

Problem Summary:
Given a string s, return the lexicographically smallest subsequence 
that contains all the distinct characters of s exactly once.

Key Observation:
To build the lexicographically smallest string, we should maintain 
characters in an increasing order using a monotonic stack. We can 
pop a larger character if we know it appears again later in the string.
=========================================================
*/

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

/*
---------------------------------------------------------
Approach 1: Greedy with Monotonic Stack (Optimal)
---------------------------------------------------------
• Intuition:
  We want smaller characters to appear as early as possible. If we see a 
  character smaller than the last one added, we should replace the last 
  character, provided the last character appears again later to ensure 
  it isn't lost permanently.

• Approach:
  - Track the last occurrence index of each character in a frequency or index map.
  - Maintain a 'visited' array to avoid adding duplicate characters already in our stack.
  - Iterate through the string: if the current character is not visited, pop characters 
    from the stack that are lexicographically greater than the current character and 
    occur again later.
  - Push the current character to the stack and mark it visited.

• Why it Works:
  Popping greater characters safely optimizes the prefix lexicographically without 
  violating the constraint of including all distinct characters, since we verify 
  their presence downstream using our last occurrence map.

• Time Complexity (TC) : O(N), where N is the length of string s. Each character is pushed and popped at most once.
• Space Complexity (SC): O(1) auxiliary space, as the stack, visited array, and count array take at most O(26) space.
*/

/*
=========================================================
FINAL APPROACH CHOICE
=========================================================
This monotonic stack approach is chosen because it resolves the greedy criteria 
optimally in a single pass. It runs efficiently within linear time O(N) and uses 
constant extra space O(1), making it perfectly optimal for the given constraints.
=========================================================
*/

class Solution {
public:
    string smallestSubsequence(string s) {
        vector<int> lastIndex(26, 0);
        vector<bool> visited(26, false);
        string result = ""; // Acting as a stack
        
        // Step 1: Find the last occurrence index of each character
        for (int i = 0; i < s.length(); ++i) {
            lastIndex[s[i] - 'a'] = i;
        }
        
        // Step 2: Iterate through the string and build the monotonic subsequence
        for (int i = 0; i < s.length(); ++i) {
            char curr = s[i];
            
            // If the character is already included in the sequence, skip it
            if (visited[curr - 'a']) {
                continue;
            }
            
            // Pop characters from the end of result if they are lexicographically 
            // greater than curr and appear again later in the string
            while (!result.empty() && result.back() > curr && lastIndex[result.back() - 'a'] > i) {
                visited[result.back() - 'a'] = false;
                result.pop_back();
            }
            
            // Push current character and mark it as visited
            result.push_back(curr);
            visited[curr - 'a'] = true;
        }
        
        return result;
    }
};
