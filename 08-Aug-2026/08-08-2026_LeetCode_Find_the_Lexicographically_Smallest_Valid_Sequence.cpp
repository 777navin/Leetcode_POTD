#include <vector>
#include <string>

using namespace std;

/*
=========================================================
Date        : 08-08-2026
Problem Name: Find the Lexicographically Smallest Valid Sequence
Platform: LeetCode
Difficulty: Medium
Tags: Two Pointers, String, Dynamic Programming, Greedy

Problem Summary:
Find the lexicographically smallest sequence of indices in word1 that 
forms a string almost equal to word2 (allowing at most 1 character mismatch).

Key Observation:
Precomputing exact suffix matches from right-to-left allows us to 
make optimal greedy choices from left-to-right.
=========================================================
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACHES
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

1. Brute Force / Backtracking
• Intuition: Explore all possible index combinations to form word2.
• Approach: Recursively pick or skip characters in word1, tracking mismatches.
• Why it Works: Exhaustively checks all paths to find a valid sequence.
• Time Complexity (TC): O(2^N)
• Space Complexity (SC): O(N) for the recursion stack.

2. Precomputation + Greedy (Most Optimal)
• Intuition: To get the smallest indices, we must pick the earliest possible match.
• Approach: Precompute right-to-left suffix matches in a DP array. Then, iterate left-to-right, picking exact matches or utilizing our 1 allowed mismatch only if the DP array guarantees the remainder of word2 can be matched exactly.
• Why it Works: The DP array acts as an oracle, allowing us to confidently consume our mismatch budget at the earliest valid opportunity, securing the lexicographically smallest result.
• Time Complexity (TC): O(N), where N is the length of word1.
• Space Complexity (SC): O(N) for the DP array tracking suffix lengths.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
FINAL APPROACH
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Chosen Approach: Precomputation + Greedy.
• Why it is chosen: It runs in strictly linear time, easily handling the N = 3*10^5 constraint.
• Why it is better: It avoids the exponential time limit issues of backtracking while guaranteeing the absolute smallest indices through early greedy evaluation.
*/

class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();
        
        // dp[i] stores the maximum length of a suffix of word2 
        // that can be found exactly in word1[i...n-1]
        vector<int> dp(n + 1, 0);
        int match_len = 0;
        
        for (int i = n - 1; i >= 0; --i) {
            if (match_len < m && word1[i] == word2[m - 1 - match_len]) {
                match_len++;
            }
            dp[i] = match_len;
        }
        
        vector<int> res;
        bool changed = false;
        int j = 0; // Pointer for word2
        
        // Greedily pick the smallest indices left-to-right
        for (int i = 0; i < n; ++i) {
            if (j == m) break; // All characters matched
            
            // If characters match exactly, unconditionally take it to minimize the index
            if (word1[i] == word2[j]) {
                res.push_back(i);
                j++;
            } 
            // If they don't match, check if we can afford the mismatch here
            else if (!changed && dp[i + 1] >= m - 1 - j) {
                res.push_back(i);
                j++;
                changed = true; // Mismatch budget consumed
            }
        }
        
        // If we successfully found a sequence of length m, return it
        if (res.size() == m) {
            return res;
        }
        
        // Otherwise, no valid sequence exists
        return {};
    }
};
