/*
=========================================================
Date        : 09-09-2026
Problem Name: 3871. Count Commas in Range II
Platform    : LeetCode
Difficulty  : Medium
Tags        : Math

Problem Summary:
Given an integer n, calculate the total number of commas used when writing
all integers from 1 to n (inclusive) in standard number formatting.
A comma is placed every three digits from the right, meaning numbers with
fewer than 4 digits have 0 commas.

Key Observation:
Every number with at least 1,000 has at least 1 comma; every number with at least
1,000,000 has a second comma, and so on. A comma is added at every threshold 10^(3k).
=========================================================
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 1: Group By Digit Length / Comma Count
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  Group numbers based on how many commas they contain: [1, 999] has 0,
  [1000, 999999] has 1, [10^6, 10^9 - 1] has 2, etc.

• Approach:
  Find the lower and upper bounds of each comma band, compute the count of
  numbers falling within [1, n] for each band, and multiply by the comma count.

• Why it Works:
  All numbers in a given range [10^(3k), 10^(3k+3) - 1] have the exact same number
  of commas (k commas). Summing these disjoint intervals gives the exact count.

• Time Complexity (TC):
  O(log10(n) / 3) -> at most 5 iterations for n <= 10^15.

• Space Complexity (SC):
  O(1) auxiliary space.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 2: Prefix Threshold Accumulation (Most Optimal)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  Instead of multiplying band counts by k, think of each comma threshold independently:
  every integer >= 10^3 contributes 1 comma, every integer >= 10^6 contributes another comma,
  every integer >= 10^9 contributes another, etc.

• Approach:
  Iterate through powers threshold = 10^3, 10^6, 10^9, 10^12, 10^15.
  If n >= threshold, exactly (n - threshold + 1) numbers contribute at least one comma
  at this position. Add (n - threshold + 1) to the total ans.

• Why it Works:
  A number with k commas is >= 10^(3*1), >= 10^(3*2), ..., >= 10^(3*k).
  It gets counted exactly once for each of the k thresholds, naturally yielding k commas.

• Time Complexity (TC):
  O(log1000(n)) = O(log(n)) operations (~5 steps for 10^15).

• Space Complexity (SC):
  O(1) auxiliary space.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
*/

/*
---------------------------------------------------------
Final Approach Selection:
• Approach 2 (Threshold Accumulation) is chosen.
• It avoids boundary edge cases and interval subtraction logic.
• Produces clean, elegant, and overflow-safe code running in O(log1000(n)) time.
---------------------------------------------------------
*/

class Solution {
public:
    long long countCommas(long long n) {
        long long totalCommas = 0;
        long long threshold = 1000LL;

        while (threshold <= n) {
            totalCommas += (n - threshold + 1);

            // Guard against 64-bit integer overflow for the next multiplication
            if (threshold > LLONG_MAX / 1000LL) {
                break;
            }
            threshold *= 1000LL;
        }

        return totalCommas;
    }
};
