/*
=========================================================
Date        : 07-08-2026
Problem Name: Smallest Divisible Digit Product II
Platform    : LeetCode
Difficulty  : Hard
Tags        : Math, String, Backtracking, Greedy, Number Theory

Problem Summary:
Given a positive integer string `num` and an integer `t`, find the smallest 
zero-free positive integer string greater than or equal to `num` whose digit 
product is divisible by `t`. If no such string exists, return "-1".

Key Observation:
Since digits are from 1-9, their prime factors can only be 2, 3, 5, and 7. If `t` has 
any other prime factor, it's impossible (return "-1"). We can use greedy digit matching 
with prime factor counts to find the minimum suffix modification.
=========================================================
*/

#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

/*
=========================================================
APPROACH EXPLANATION
=========================================================

1. Approach: Prime Factor Count Matching + Backtracking / Greedy Suffix Search

• Intuition:
  - Any digit from 1 to 9 can only contribute prime factors 2, 3, 5, and 7 to the product.
  - Therefore, $t$ must only contain prime factors 2, 3, 5, and 7.
  - To find the smallest number $\ge num$, we try to match a prefix of `num` as long as possible, 
    then increase the next character, and fill the remaining suffix greedily with the smallest 
    possible digits that satisfy the remaining prime factor requirements.

• Approach:
  - Check if $t$ has prime factors other than 2, 3, 5, 7. If so, return "-1".
  - Factorize $t$ into count of factors: `c2`, `c3`, `c5`, `c7`.
  - Check if `num` itself is valid (length, no zeros, and digit product divisible by $t$).
  - Iterate over the prefix length $i$ from $N-1$ down to 0, attempting to increment `num[i]`.
  - For each position $i$, try digits $d \in [num[i] + 1, 9]$ (or $1 \dots 9$ for suffix filling).
  - Use a greedy helper function to determine if the remaining $len - 1 - i$ positions can accommodate 
    the needed counts of factors 2, 3, 5, 7.
  - If `num` length isn't enough, expand the total length to $max(N, \text{min\_required\_length})$ 
    and construct the minimal valid string.

• Why it Works:
  - $t \le 10^{14}$ implies small prime factor counts (at most ~46 factors of 2).
  - Greedily placing larger digits (like 8 or 9) near the end minimizes the required string length, 
    and filling lower positions with smaller digits ensures lexicographically smallest result.

• Time Complexity (TC):
  - $\mathcal{O}(N \times 10)$, where $N = |num|$. Factor operations and greedy suffix checks take $O(1)$ time.

• Space Complexity (SC):
  - $\mathcal{O}(N)$ for constructing the final string.
=========================================================
*/

/*
=========================================================
FINAL APPROACH
=========================================================
• We choose the Greedy Backtracking with Prime Factor Tracking approach.
• It optimal because $t$ has at most 4 prime factors, making factor state tracking $O(1)$.
• Checking prefix matches from right to left guarantees finding the smallest strictly larger/equal number in $O(N)$ time.
=========================================================
*/

class Solution {
private:
    // Helper to count required factors 2, 3, 5, 7 for a digit d
    void addFactors(int d, int count2[], int count3[], int count5[], int count7[], int sign) {
        if (d == 2) count2[0] += sign * 1;
        else if (d == 3) count3[0] += sign * 1;
        else if (d == 4) count2[0] += sign * 2;
        else if (d == 5) count5[0] += sign * 1;
        else if (d == 6) { count2[0] += sign * 1; count3[0] += sign * 1; }
        else if (d == 7) count7[0] += sign * 1;
        else if (d == 8) count2[0] += sign * 3;
        else if (d == 9) count3[0] += sign * 2;
    }

    // Min digits required to satisfy remaining factors (c2, c3, c5, c7)
    int minDigitsNeeded(int c2, int c3, int c5, int c7) {
        c2 = max(0, c2);
        c3 = max(0, c3);
        c5 = max(0, c5);
        c7 = max(0, c7);

        // Optimal digit choices: 8 (uses 32s), 9 (uses 2 3s), 6 (uses 1 2 and 1 3), 4 (uses 2 2s), 2, 3, 5, 7
        int count = c5 + c7;
        int d8 = c2 / 3;
        c2 %= 3;
        int d9 = c3 / 2;
        c3 %= 2;

        if (c2 == 2 && c3 == 1) { // 2*2 * 3 = 12 -> 4 and 3, or 2 and 6
            count += 2;
            c2 = 0; c3 = 0;
        } else if (c2 == 1 && c3 == 1) { // 2 * 3 = 6
            count += 1;
            c2 = 0; c3 = 0;
        } else {
            if (c2 > 0) count += 1;
            if (c3 > 0) count += 1;
        }

        return count + d8 + d9;
    }

    // Fills remaining length with lexicographically smallest valid suffix
    string fillSuffix(int len, int c2, int c3, int c5, int c7) {
        string res = "";
        for (int i = 0; i < len; ++i) {
            int remLen = len - 1 - i;
            for (int d = 1; d <= 9; ++d) {
                int nc2 = c2, nc3 = c3, nc5 = c5, nc7 = c7;
                addFactors(d, &nc2, &nc3, &nc5, &nc7, -1);
                if (minDigitsNeeded(nc2, nc3, nc5, nc7) <= remLen) {
                    res += to_string(d);
                    c2 = nc2; c3 = nc3; c5 = nc5; c7 = nc7;
                    break;
                }
            }
        }
        return res;
    }

public:
    string smallestNumber(string num, long long t) {
        int c2 = 0, c3 = 0, c5 = 0, c7 = 0;
        
        // Factorize t
        long long temp = t;
        while (temp % 2 == 0) { c2++; temp /= 2; }
        while (temp % 3 == 0) { c3++; temp /= 3; }
        while (temp % 5 == 0) { c5++; temp /= 5; }
        while (temp % 7 == 0) { c7++; temp /= 7; }

        if (temp > 1) return "-1"; // Prime factor > 7 exists

        int n = num.length();

        // 1. Check if num itself (or with non-zero replacements) is valid
        int cur2 = c2, cur3 = c3, cur5 = c5, cur7 = c7;
        bool has_zero = false;
        int first_zero = -1;

        for (int i = 0; i < n; ++i) {
            if (num[i] == '0') {
                has_zero = true;
                first_zero = i;
                break;
            }
            addFactors(num[i] - '0', &cur2, &cur3, &cur5, &cur7, -1);
        }

        if (!has_zero && cur2 <= 0 && cur3 <= 0 && cur5 <= 0 && cur7 <= 0) {
            return num;
        }

        // 2. Try replacing suffix of num starting from position i
        int req2 = c2, req3 = c3, req5 = c5, req7 = c7;
        
        // Pre-calculate factor requirements up to each index
        vector<vector<int>> pref(n + 1, vector<int>(4, 0));
        pref[0] = {c2, c3, c5, c7};
        
        for (int i = 0; i < n; ++i) {
            if (num[i] == '0') break;
            int d = num[i] - '0';
            int p2 = pref[i][0], p3 = pref[i][1], p5 = pref[i][2], p7 = pref[i][3];
            addFactors(d, &p2, &p3, &p5, &p7, -1);
            pref[i + 1] = {p2, p3, p5, p7};
        }

        int limit = has_zero ? first_zero : n - 1;

        for (int i = limit; i >= 0; --i) {
            int start_digit = (num[i] - '0') + 1;
            int remLen = n - 1 - i;

            for (int d = start_digit; d <= 9; ++d) {
                int nc2 = pref[i][0], nc3 = pref[i][1], nc5 = pref[i][2], nc7 = pref[i][3];
                addFactors(d, &nc2, &nc3, &nc5, &nc7, -1);

                if (minDigitsNeeded(nc2, nc3, nc5, nc7) <= remLen) {
                    string prefix = num.substr(0, i) + to_string(d);
                    string suffix = fillSuffix(remLen, nc2, nc3, nc5, nc7);
                    return prefix + suffix;
                }
            }
        }

        // 3. If no same length number works, generate a number with total length = max(n + 1, minLen)
        int minLen = minDigitsNeeded(c2, c3, c5, c7);
        int targetLen = max(n + 1, minLen);
        
        return fillSuffix(targetLen, c2, c3, c5, c7);
    }
};
