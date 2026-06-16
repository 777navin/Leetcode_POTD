/*
Date: 16-06-2026
Problem Name: Process String with Special Operations I
Platform: LeetCode
Difficulty: Medium
Tags: String, Simulation

Problem Summary:
Given a string 's' consisting of lowercase English letters and special characters ('*', '#', '%'), 
build a result string by processing 's' from left to right:
- Lowercase letter: Append to result.
- '*': Remove the last character from result, if it exists.
- '#': Duplicate the current result and append it to itself.
- '%': Reverse the current result.

Methods to Solve:
1. Simulation (Using std::string)
   - Intuition: Directly simulate the operations as described using a mutable string.
   - Approach: Iterate through the string; perform corresponding string manipulations 
     (push_back, pop_back, concatenation, reverse).
   - Time Complexity: O(N * L), where N is the length of input 's' and L is the length 
     of the intermediate string (worst case due to # operation).
   - Space Complexity: O(L) to store the result string.

Comparison Table:
Method         | TC    | SC   | Best Use Case
-------------- | ----- | ---- | -------------
Simulation     | O(N*L)| O(L) | Direct implementation for small constraints

Final Recommended Solution: Simulation
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

class Solution {
public:
    /**
     * Processes the input string based on special operations.
     * * @param s The input string containing letters and special characters.
     * @return The resulting string after processing.
     */
    std::string processStr(std::string s) {
        std::string result = "";
        
        for (char c : s) {
            if (c == '*') {
                // Remove the last character if it exists
                if (!result.empty()) {
                    result.pop_back();
                }
            } else if (c == '#') {
                // Duplicate the current result and append it to itself
                result += result;
            } else if (c == '%') {
                // Reverse the current result
                std::reverse(result.begin(), result.end());
            } else {
                // Append lowercase English letter
                result.push_back(c);
            }
        }
        
        return result;
    }
};

/**
 * Note: Since the constraints are small (s.length <= 20), 
 * direct simulation with std::string is efficient and optimal.
 */
