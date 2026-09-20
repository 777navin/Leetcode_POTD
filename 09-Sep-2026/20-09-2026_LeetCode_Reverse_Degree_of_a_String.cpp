/*
=========================================================
Date        : 20-09-2026
Problem Name: Reverse Degree of a String
Platform    : LeetCode
Difficulty  : Easy
Tags        : String, Simulation

Problem Summary:
Calculate the reverse degree of a given string s.
Each character's reverse alphabet rank ('a' = 26, 'b' = 25, ..., 'z' = 1)
is multiplied by its 1-indexed position in the string, and all products are summed.

Key Observation:
The reversed alphabet value of any lowercase English letter c is given by (26 - (c - 'a')).
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Linear Scan (Simulation)
---------------------------------------------------------
• Intuition:
  Iterate through the string once, evaluate the contribution of each character,
  and accumulate the total into a running sum.

• Approach:
  1. Initialize total_degree to 0.
  2. For each index i from 0 to s.length() - 1:
     - Compute the reverse alphabet rank: rev_val = 26 - (s[i] - 'a').
     - Compute the 1-based string index: pos = i + 1.
     - Add (rev_val * pos) to total_degree.
  3. Return total_degree.

• Why it Works:
  Directly simulates the definition given in the problem statement in a single pass.

• Time Complexity (TC):
  O(n), where n is the length of string s.

• Space Complexity (SC):
  O(1), requiring only a few integer variables.
---------------------------------------------------------
*/

/*
---------------------------------------------------------
FINAL APPROACH SELECTION:
---------------------------------------------------------
• Approach 1 (Linear Scan) is chosen because it achieves optimal linear time O(n) and O(1) auxiliary space.
• A single traversal is the most direct, elegant, and standard solution for string simulation problems.
---------------------------------------------------------
*/

#include <string>

class Solution {
public:
    int reverseDegree(std::string s) {
        int totalDegree = 0;
        int n = static_cast<int>(s.length());

        for (int i = 0; i < n; ++i) {
            int revAlphabetRank = 26 - (s[i] - 'a');
            int stringIndex = i + 1;
            totalDegree += revAlphabetRank * stringIndex;
        }

        return totalDegree;
    }
};
