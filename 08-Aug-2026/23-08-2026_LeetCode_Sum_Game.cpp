/*
=========================================================
Date        : 23-08-2026
Problem Name: 1927. Sum Game
Platform    : LeetCode
Difficulty  : Medium
Tags        : Math, String, Greedy, Game Theory

Problem Summary:
Alice and Bob play a game replacing '?' characters with digits '0'-'9'.
Alice wants the sum of the first half and second half to be different.
Bob wins if the two halves end up with an equal sum.

Key Observation:
Bob can pair up moves on opposite sides or balance pairs of '?' on the same side with a sum of 9 (averaging 4.5 per '?').
=========================================================
*/

#include <string>
#include <numeric>

using namespace std;

/*
---------------------------------------------------------
APPROACH 1: Game Theory & Math Balance (Optimal)
---------------------------------------------------------

• Intuition:
  - If the total number of '?' is odd, Alice gets the final move and can always make sums unequal.
  - If Bob matches Alice's moves on opposite sides, they cancel out.
  - For remaining '?' on one side, Bob can ensure every 2 '?' sum to 9 (contributing 4.5 per '?').

• Approach:
  - Count the sum and '?' count for both left and right halves: sumLeft, sumRight, qLeft, qRight.
  - Bob wins if and only if the difference in sums equals exactly 4.5 * (qRight - qLeft).
  - Equivalent integer check: 2 * (sumLeft - sumRight) == 9 * (qRight - qLeft).

• Why it Works:
  - Whenever Alice plays a digit `d` in a pair on the side with excess '?', Bob can respond with `9 - d` in the same half, locking in 9 per pair.
  - If the initial difference does not match this exact requirement, Alice can skew the sum to guarantee unequal totals.

• Time Complexity (TC):
  - O(N) where N is the length of the string `num`.

• Space Complexity (SC):
  - O(1) auxiliary space.
---------------------------------------------------------
*/

/*
---------------------------------------------------------
FINAL APPROACH:
---------------------------------------------------------
• We use the Math Balance approach with O(N) time and O(1) space.
• It provides the single-pass optimal solution without simulating turns.
• Avoids floating-point precision issues by scaling the equation by 2.
---------------------------------------------------------
*/

class Solution {
public:
    bool sumGame(string num) {
        int n = num.size();
        int sumDiff = 0;
        int qDiff = 0; // qLeft - qRight

        for (int i = 0; i < n / 2; ++i) {
            if (num[i] == '?') {
                qDiff++;
            } else {
                sumDiff += (num[i] - '0');
            }
        }

        for (int i = n / 2; i < n; ++i) {
            if (num[i] == '?') {
                qDiff--;
            } else {
                sumDiff -= (num[i] - '0');
            }
        }

        // Total '?' count difference must balance the sum difference with 4.5 per '?'
        // Alice wins if the game cannot be balanced by Bob:
        return (2 * sumDiff != -9 * qDiff);
    }
};
