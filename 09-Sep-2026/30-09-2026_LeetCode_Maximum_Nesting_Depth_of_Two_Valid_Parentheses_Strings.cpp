/*
=========================================================
Date        : 30-09-2026
Problem Name: Maximum Nesting Depth of Two Valid Parentheses Strings
Platform    : LeetCode
Difficulty  : Medium
Tags        : String, Stack, Greedy

Problem Summary:
Given a valid parentheses string (VPS) seq, split its characters into two disjoint 
subsequences A and B such that both A and B are valid parentheses strings.
The goal is to minimize the maximum nesting depth between A and B, returning an 
array of 0s and 1s indicating membership in A or B respectively.

Key Observation:
Since the input seq is already a balanced VPS, we can split depth levels evenly 
between subsequences A and B by assigning alternating nesting levels (e.g., odd 
depth to A and even depth to B).
=========================================================
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
=========================================================
APPROACH 1: Stack-Based Depth Division
=========================================================

• Intuition:
  We can maintain the current nesting depth while iterating through the string. By 
  distributing parentheses at odd depths to one sequence and even depths to the other, 
  we effectively balance and halve the maximum nesting depth for both subsequences.

• Approach:
  Maintain a `depth` variable initialized to 0. When encountering '(', check the current 
  `depth`: assign 0 (subsequence A) if depth is even, or 1 (subsequence B) if depth is odd, 
  then increment `depth`. When encountering ')', decrement `depth` first, then assign based 
  on the updated `depth`.

• Why it Works:
  Matching open and close parentheses corresponding to the same nesting level will be 
  assigned to the same subsequence, preserving valid parentheses structure while halving 
  the nesting depth.

• Time Complexity (TC):
  O(N) - Single pass through the string of length N.

• Space Complexity (SC):
  O(1) auxiliary space (excluding the output answer array of size N).
*/

/*
=========================================================
FINAL APPROACH SELECTION
=========================================================
• Chosen Approach: Approach 1 (Depth Parity Assignment / Greedy)
• Reason for Selection: It achieves optimal O(N) time complexity with O(1) auxiliary 
  space. It processes the string in a single linear scan without needing extra data structures 
  like stacks.
*/

class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        int n = seq.size();
        vector<int> answer(n, 0);
        int depth = 0;

        for (int i = 0; i < n; ++i) {
            if (seq[i] == '(') {
                // Assign based on current depth parity, then increase depth
                answer[i] = depth % 2;
                depth++;
            } else {
                // Decrease depth first, then assign based on depth parity
                depth--;
                answer[i] = depth % 2;
            }
        }

        return answer;
    }
};
