/*
=========================================================
Date        : 17-08-2026
Problem Name: 1563. Stone Game V
Platform    : LeetCode
Difficulty  : Hard
Tags        : Array, Math, Dynamic Programming, Game Theory

Problem Summary:
Alice divides a row of stones into two non-empty parts in each round.
Bob calculates the sum of each part and discards the strictly larger one; Alice gains the sum of the remaining part.
If both parts have equal sum, Alice chooses which part to keep. The game continues until one stone remains.

Key Observation:
This is an interval dynamic programming problem on subarrays [i, j].
Prefix sums allow O(1) range sum queries to test every partition split k (i <= k < j).
=========================================================

---------------------------------------------------------
APPROACH 1: Recursive Interval DP with Memoization
---------------------------------------------------------
• Intuition:
  For any subarray stoneValue[i...j], Alice tries every valid split point k.
  Bob forces Alice to continue on the part with the strictly smaller sum, adding that sum to Alice's score.
  If sums are equal, Alice can pick the maximum resulting score between the left and right halves.

• Approach:
  1. Build a prefix sum array to compute sum(i, j) in O(1) time.
  2. Define memoized function `solve(i, j)` returning the maximum score for range [i, j].
  3. Base case: if i == j, return 0 (single stone remaining).
  4. For every k from i to j - 1:
     - leftSum = sum(i, k), rightSum = sum(k + 1, j)
     - If leftSum < rightSum: score = leftSum + solve(i, k)
     - If rightSum < leftSum: score = rightSum + solve(k + 1, j)
     - If leftSum == rightSum: score = leftSum + max(solve(i, k), solve(k + 1, j))
  5. Take the maximum score across all k and memoize.

• Why it Works:
  The state depends entirely on the subarray boundaries [i, j]. Memoizing subproblems prevents recalculating
  overlapping subproblems and cleanly captures all game decisions.

• Time Complexity (TC) : O(N^3) where N <= 500 (O(N^2) states, each exploring O(N) split points).
• Space Complexity (SC): O(N^2) for memoization table + O(N) recursion call stack.

---------------------------------------------------------
FINAL APPROACH SELECTION
---------------------------------------------------------
The interval DP with memoization and prefix sums computes all O(N^2) subproblems directly.
Given N <= 500 and efficient array-based memoization, O(N^3) passes comfortably within the time limit.
*/

#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

class Solution {
private:
    int memo[505][505];
    int pref[505];

    int getSum(int l, int r) {
        return pref[r + 1] - pref[l];
    }

    int solve(int i, int j, const vector<int>& stoneValue) {
        if (i >= j) return 0;
        if (memo[i][j] != -1) return memo[i][j];

        int maxScore = 0;

        for (int k = i; k < j; ++k) {
            int leftSum = getSum(i, k);
            int rightSum = getSum(k + 1, j);

            if (leftSum < rightSum) {
                maxScore = max(maxScore, leftSum + solve(i, k, stoneValue));
            } else if (rightSum < leftSum) {
                maxScore = max(maxScore, rightSum + solve(k + 1, j, stoneValue));
            } else {
                maxScore = max(maxScore, leftSum + max(solve(i, k, stoneValue), solve(k + 1, j, stoneValue)));
            }
        }

        return memo[i][j] = maxScore;
    }

public:
    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();
        pref[0] = 0;
        for (int i = 0; i < n; ++i) {
            pref[i + 1] = pref[i] + stoneValue[i];
        }

        memset(memo, -1, sizeof(memo));
        return solve(0, n - 1, stoneValue);
    }
};
