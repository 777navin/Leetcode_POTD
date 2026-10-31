/*
=========================================================
Date        : 31-10-2026
Problem Name: Twisted Mirror Path Count
Platform    : LeetCode
Difficulty  : Medium
Tags        : Array, Dynamic Programming, Matrix

Problem Summary:
- Given an m x n binary grid, count paths from top-left
  to bottom-right.
- The robot can move only right or down.
- Entering a mirror (1) causes the robot to reflect.
- Return the number of valid paths modulo 10^9 + 7.

Key Observation:
- Reflection depends on the direction used to enter a mirror.
- Precompute the final destination for both possible moves
  from every cell using reverse DP.
=========================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {

        /*
        =====================================================
        APPROACH 1: BRUTE FORCE (RECURSION)

        Intuition:
        - Explore both possible moves from every cell.

        Approach:
        - Simulate mirror reflections recursively.
        - Count all valid paths reaching the destination.

        Why it Works:
        - Every possible path is explored.

        TC: Exponential
        SC: O(m + n) recursion stack.
        =====================================================


        =====================================================
        APPROACH 2: OPTIMIZED DYNAMIC PROGRAMMING

        Intuition:
        - Each cell has two possible moves: right and down.
        - Mirrors can redirect these moves through multiple
          consecutive mirror cells.

        Approach:
        - Precompute goRight[i][j] and goDown[i][j].
        - These store the final landing position after
          completing all consecutive mirror reflections.
        - Calculate these transitions in reverse order.
        - Use DP to count paths reaching every cell.
        - Process cells in row-major order.

        Why it Works:
        - Every transition moves strictly right or down.
        - Therefore, row-major order is a valid DP order.
        - Every valid path is counted exactly once.

        TC: O(m * n)
        SC: O(m * n)
        =====================================================
        */

        int m = grid.size();
        int n = grid[0].size();

        const int MOD = 1e9 + 7;

        // -1 represents an invalid move.
        using Point = pair<int, int>;

        vector<vector<Point>> goRight(
            m, vector<Point>(n, {-1, -1})
        );

        vector<vector<Point>> goDown(
            m, vector<Point>(n, {-1, -1})
        );

        /*
        Precompute transitions in reverse order.

        goRight:
        - If the right cell is empty, land there.
        - If it is a mirror, continue using goDown
          from that mirror cell.

        goDown:
        - If the lower cell is empty, land there.
        - If it is a mirror, continue using goRight
          from that mirror cell.
        */

        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {

                // Transition when attempting to move right.
                if (j + 1 < n) {

                    if (grid[i][j + 1] == 0) {
                        goRight[i][j] = {i, j + 1};
                    }
                    else {
                        goRight[i][j] = goDown[i][j + 1];
                    }
                }

                // Transition when attempting to move down.
                if (i + 1 < m) {

                    if (grid[i + 1][j] == 0) {
                        goDown[i][j] = {i + 1, j};
                    }
                    else {
                        goDown[i][j] = goRight[i + 1][j];
                    }
                }
            }
        }

        // DP initialization.
        vector<vector<int>> dp(
            m, vector<int>(n, 0)
        );

        dp[0][0] = 1;

        // Process cells in topological row-major order.
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (dp[i][j] == 0) {
                    continue;
                }

                // Choose right.
                auto [r1, c1] = goRight[i][j];

                if (r1 != -1) {
                    dp[r1][c1] =
                        (dp[r1][c1] + dp[i][j]) % MOD;
                }

                // Choose down.
                auto [r2, c2] = goDown[i][j];

                if (r2 != -1) {
                    dp[r2][c2] =
                        (dp[r2][c2] + dp[i][j]) % MOD;
                }
            }
        }

        // Final answer.
        return dp[m - 1][n - 1];
    }
};

/*
=========================================================
WHY THIS APPROACH?

- Precomputation avoids repeatedly simulating reflections.
- Reverse DP calculates every transition in O(m * n).
- Path counting takes another O(m * n).
- Efficiently handles the maximum constraint of 500 x 500.

Final Complexity:
Time Complexity  : O(m * n)
Space Complexity : O(m * n)
=========================================================
*/
