/*
=========================================================
Date        : 07-10-2026
Problem Name: Remove Invalid Parentheses
Platform    : LeetCode
Difficulty  : Hard
Tags        : String, Backtracking, Breadth-First Search

Problem Summary:
Given a string 's' containing parentheses and letters, remove the minimum 
number of invalid parentheses to make the input string valid. Return all 
unique valid strings that can be formed using the minimum removals.

Key Observation:
Using BFS guarantees finding valid strings with the minimum number of removals 
first, as it explores level by level (where level depth corresponds to the number 
of removed characters).
=========================================================
*/

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>

/*
---------------------------------------------------------
APPROACH 1: Breadth-First Search (BFS) [Most Optimal / Standard]
---------------------------------------------------------
• Intuition:
  - Treat each string state as a node in a graph. Removing one parenthesis creates an edge to a child node.
  - BFS explores level-by-level, so the first depth where we find valid strings corresponds to the minimum removals.

• Approach:
  - Use a queue for BFS and an unordered_set to avoid duplicate processing.
  - Push the initial string 's' into the queue.
  - Process level by level: if any string at the current level is valid, flag 'found = true' and collect all valid strings at this level.
  - If valid strings are found at the current level, stop generating further states (to ensure minimum removals).

• Why it Works:
  - BFS guarantees shortest path exploration in unweighted state graphs, ensuring minimum parenthesis removals.

• Time Complexity (TC):
  - O(N * 2^N), where N is the length of string 's'. In the worst case, we generate all subsets of string permutations.

• Space Complexity (SC):
  - O(N * 2^N) to store states in the queue and set.
---------------------------------------------------------
*/

/*
---------------------------------------------------------
FINAL APPROACH CHOICE
---------------------------------------------------------
• BFS is chosen because it directly guarantees minimum removals without extra counting phases.
• It automatically handles string uniqueness via a set and stops as soon as the optimal level is processed.
• It cleanly fits within constraints (N <= 25) with optimal performance.
---------------------------------------------------------
*/

class Solution {
private:
    // Helper function to check if a string has valid parentheses
    bool isValid(const string& s) {
        int count = 0;
        for (char c : s) {
            if (c == '(') {
                count++;
            } else if (c == ')') {
                count--;
                if (count < 0) return false;
            }
        }
        return count == 0;
    }

public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string> result;
        if (s.empty()) return result;

        unordered_set<string> visited;
        queue<string> q;

        q.push(s);
        visited.insert(s);

        bool found = false;

        while (!q.empty()) {
            string curr = q.front();
            q.pop();

            if (isValid(curr)) {
                result.push_back(curr);
                found = true;
            }

            // If we found valid strings at this removal level, do not expand further levels
            if (found) continue;

            // Generate next states by removing one parenthesis
            for (int i = 0; i < curr.length(); i++) {
                if (curr[i] != '(' && curr[i] != ')') continue;

                string nextState = curr.substr(0, i) + curr.substr(i + 1);

                if (visited.find(nextState) == visited.end()) {
                    visited.insert(nextState);
                    q.push(nextState);
                }
            }
        }

        return result;
    }
};
