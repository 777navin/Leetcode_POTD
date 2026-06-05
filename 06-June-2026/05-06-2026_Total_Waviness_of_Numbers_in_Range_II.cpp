/*
Date: 05-06-2026
Problem Name: Total Waviness of Numbers in Range II
Platform: LeetCode
Difficulty: Hard
Tags: Digit DP, Dynamic Programming, Math

Problem Summary:
The goal is to calculate the total "waviness" of all integers in the range [num1, num2]. 
A number's waviness is the total count of peaks and valleys within it.
- A digit is a peak if it is strictly greater than its neighbors.
- A digit is a valley if it is strictly less than its neighbors.
- The first and last digits of a number cannot be peaks or valleys.

Methods to Solve:
1. Digit DP (The Optimal Approach)
   - Intuition: Since the constraints go up to 10^15, a linear search is impossible. 
     We use a digit-by-digit construction approach with memoization.
   - Approach: 
     - Define `dfs(pos, tight, started, prev2, prev1)` where `prev2` and `prev1` track the 
       previous two digits to identify peaks/valleys.
     - `tight` handles the boundary condition of the number $N$.
     - `started` handles leading zeros.
   - Time Complexity: O(Number of Digits * 10 * 2 * 2 * 11 * 11) ≈ O(1), as the number of 
     digits is constant (up to 18).
   - Space Complexity: O(Number of Digits * 10 * 10) for the DP memoization table.

Comparison Table:
Method      | TC    | SC    | Best Use Case
------------|-------|-------|--------------
Digit DP    | O(log N) | O(log N) | Large range queries where N ≤ 10^18

Final Recommended Solution:
The provided Digit DP approach is the industry standard for range-based digit problems.
*/

#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

class Solution {
public:
    struct Node {
        long long waviness;
        long long cnt;
    };

    string s;
    Node dp[17][2][2][11][11];
    bool vis[17][2][2][11][11];

    /*
    tight: Are we still constrained by N's digits?
    started: Have we started placing non-zero digits?
    prev2, prev1: The last two digits placed to identify peak/valley patterns.
    */
    Node dfs(int pos, int tight, int started, int prev2, int prev1) {
        if (pos == s.size()) {
            return {0, 1};
        }
        if (vis[pos][tight][started][prev2][prev1]) {
            return dp[pos][tight][started][prev2][prev1];
        }
        
        vis[pos][tight][started][prev2][prev1] = true;
        long long totalWaviness = 0;
        long long totalCnt = 0;

        int limit = tight ? s[pos] - '0' : 9;

        for (int d = 0; d <= limit; d++) {
            int nextTight = tight && (d == limit);

            if (!started && d == 0) {
                Node child = dfs(pos + 1, nextTight, 0, 10, 10);
                totalWaviness += child.waviness;
                totalCnt += child.cnt;
            } else {
                int nPrev2, nPrev1;
                long long add = 0;

                if (!started) {
                    nPrev2 = 10;
                    nPrev1 = d;
                } else {
                    if (prev2 != 10) {
                        bool peak = (prev1 > prev2 && prev1 > d);
                        bool valley = (prev1 < prev2 && prev1 < d);
                        if (peak || valley) add = 1;
                    }
                    nPrev2 = prev1;
                    nPrev1 = d;
                }

                Node child = dfs(pos + 1, nextTight, 1, nPrev2, nPrev1);
                totalWaviness += child.waviness + add * child.cnt;
                totalCnt += child.cnt;
            }
        }
        return dp[pos][tight][started][prev2][prev1] = {totalWaviness, totalCnt};
    }

    long long solve(long long n) {
        if (n <= 0) return 0;
        s = to_string(n);
        memset(vis, 0, sizeof(vis));
        return dfs(0, 1, 0, 10, 10).waviness;
    }

    long long totalWaviness(long long num1, long long num2) {
        return solve(num2) - solve(num1 - 1);
    }
};
