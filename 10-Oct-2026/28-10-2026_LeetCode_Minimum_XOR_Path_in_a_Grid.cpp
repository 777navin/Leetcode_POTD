/*
=========================================================
Date        : 28-10-2026
Problem Name: Minimum XOR Path in a Grid
Platform    : LeetCode
Difficulty  : Medium
Tags        : Array, Dynamic Programming, Bit Manipulation, Matrix

Problem Summary:
- Given an m * n grid, find the minimum possible XOR value of all elements along a path from the top-left cell (0, 0) to the bottom-right cell (m - 1, n - 1).
- Movement is restricted to moving either right or down at each step.
- The path cost is the bitwise XOR sum of all visited cells, including start and end cells.

Key Observation:
- Unlike standard arithmetic paths where greedy choices preserve monotonicity (A < B implies A + C < B + C), XOR operation does not preserve order (A < B does NOT imply A ^ C < B ^ C).
- Therefore, we must maintain the complete set of all reachable cumulative XOR values at every grid cell rather than just the minimum value.
=========================================================
*/

/*
=========================================================
APPROACH EXPLANATION
=========================================================

1. Brute Force (Recursive Backtracking / DFS)
• Intuition: Explore every possible path from (0, 0) to (m - 1, n - 1) and collect the XOR sum.
• Approach: Recursively move right and down, keeping track of the running XOR sum.
• Why it Works: Exhaustively checks all paths to guarantee finding the optimal answer.
• Time Complexity (TC): Exponential, O(2^(m + n))
• Space Complexity (SC): O(m + n) for recursion stack.

2. Dynamic Programming with Hash Sets (Optimized)
• Intuition: Since overlapping subproblems exist, we can use DP, but each cell needs to store a set of reachable XOR sums.
• Approach: Maintain an unordered_set of valid cumulative XOR values at each grid cell (i, j) derived from cells above (i-1, j) and to the left (i, j-1).
• Why it Works: Because grid values are up to 1023, the maximum possible XOR sum is constrained, keeping the number of unique reachable values per cell manageable (at most 1024).
• Time Complexity (TC): O(m * n * V_max) where V_max <= 1024.
• Space Complexity (SC): O(m * n * V_max) or optimized to O(n * V_max) row-wise.

=========================================================
FINAL APPROACH: Dynamic Programming with Hash Sets (Space-Optimized Grid Traversal)
=========================================================
- We choose the 2D DP table with unordered sets because it correctly aggregates all reachable XOR values without missing optimal configurations caused by non-monotonic XOR operations.
- Storing the sets cell-by-cell allows efficient state transitions from top and left neighbors.
- Finally, the minimum element in the set at the bottom-right cell gives the desired answer.
=========================================================
*/

#include <vector>
#include <unordered_set>
#include <algorithm>

class Solution {
public:
    int minCost(std::vector<std::vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // DP table to store the set of all possible XOR values reachable at each cell
        std::vector<std::vector<std::unordered_set<int>>> dp(
            m, std::vector<std::unordered_set<int>>(n)
        );

        // Initialize the starting cell with its own value
        dp[0][0].insert(grid[0][0]);

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                // Transition from the cell directly above
                if (i > 0) {
                    for (int x : dp[i - 1][j]) {
                        dp[i][j].insert(x ^ grid[i][j]);
                    }
                }

                // Transition from the cell directly to the left
                if (j > 0) {
                    for (int x : dp[i][j - 1]) {
                        dp[i][j].insert(x ^ grid[i][j]);
                    }
                }
            }
        }

        // The answer is the minimum XOR value present in the bottom-right cell's set
        return *std::min_element(
            dp[m - 1][n - 1].begin(),
            dp[m - 1][n - 1].end()
        );
    }
};
