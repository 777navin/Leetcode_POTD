/*
=========================================================
Date        : 29-09-2026
Problem Name: Check if There Is a Valid Parentheses String Path
Platform    : LeetCode
Difficulty  : Hard
Tags        : Array, Dynamic Programming, Matrix, Bracket Sequences

Problem Summary:
Given an m x n matrix 'grid' of '(' and ')', determine if there exists a valid path from 
(0, 0) to (m - 1, n - 1) moving only down or right such that the concatenation of characters 
forms a valid parentheses string.

Key Observation:
A path forms a valid parentheses string if and only if the path length is even, every prefix 
has count('(') >= count(')'), and at the destination, count('(') == count(')'). We can track 
the balance `balance = count('(') - count(')')`.
=========================================================
*/

#include <vector>
#include <vector>

using namespace std;

/*
---------------------------------------------------------
APPROACH 1: Brute Force (DFS / Backtracking)
---------------------------------------------------------
• Intuition:
  Explore all possible paths from (0, 0) to (m-1, n-1) moving only right or down, keeping track of 
  the open/close parenthesis balance.

• Approach:
  Recursively move to (r+1, c) and (r, c+1) while maintaining the balance. If balance ever drops 
  below 0, prune the path. Check if balance == 0 at (m-1, n-1).

• Why it Works:
  It checks all possible valid paths exhaustive until a valid path is found.

• Time Complexity (TC):
  O(2^(m + n)) - Exponential number of paths in the worst case.

• Space Complexity (SC):
  O(m + n) - Recursion stack depth.


---------------------------------------------------------
APPROACH 2: Optimized DP / Memoized DFS (Chosen)
---------------------------------------------------------
• Intuition:
  Multiple paths can reach the same cell (r, c) with the exact same net balance. We can avoid 
  re-evaluating identical states using dynamic programming / memoization.

• Approach:
  Use a 3D memoization table/array `visited[r][c][balance]`. Calculate balance changes at each step.
  Prune if balance < 0 or balance > (m + n)/2. Also prune early if (m + n - 1) is odd.

• Why it Works:
  A path string length is fixed at (m + n - 1). A valid parentheses string must have an even length. 
  Tracking visited states (r, c, balance) prevents redundant computations across overlapping subproblems.

• Time Complexity (TC):
  O(m * n * (m + n)) - There are m * n cells and max possible balance is (m + n) / 2.

• Space Complexity (SC):
  O(m * n * (m + n)) - 3D memoization array and recursion stack.
*/

/*
---------------------------------------------------------
FINAL APPROACH SELECTION
---------------------------------------------------------
Approach 2 (Memoized DFS) is chosen because the matrix dimensions (m, n <= 100) will result in a Time Limit Exceeded (TLE) error for pure brute force DFS. 
By memoizing the state (row, col, balance), we reduce the state space to at most 100 * 100 * 100 states, making it run well within the execution time limits.
---------------------------------------------------------
*/

class Solution {
private:
    int m, n;
    bool memo[100][100][101];
    bool visited[100][100][101];

    bool dfs(int r, int c, int balance, const vector<vector<char>>& grid) {
        // Balance delta for current cell
        balance += (grid[r][c] == '(' ? 1 : -1);

        // Invalid prefix balance
        if (balance < 0) return false;
        
        // Maximum required balance cannot exceed remaining steps or total max balance
        if (balance > (m + n) / 2) return false;

        // Base case: Reached bottom-right cell
        if (r == m - 1 && c == n - 1) {
            return balance == 0;
        }

        if (visited[r][c][balance]) {
            return memo[r][c][balance];
        }

        bool result = false;
        // Move Down
        if (r + 1 < m) {
            result = result || dfs(r + 1, c, balance, grid);
        }
        // Move Right
        if (!result && c + 1 < n) {
            result = result || dfs(r, c + 1, balance, grid);
        }

        visited[r][c][balance] = true;
        return memo[r][c][balance] = result;
    }

public:
    bool hasValidPath(vector<vector<char>>& grid) {
        m = grid.size();
        n = grid[0].size();

        // Valid parentheses path must have an even length (m + n - 1)
        if ((m + n - 1) % 2 != 0) return false;

        // Starting cell must be '(' and ending cell must be ')'
        if (grid[0][0] == ')' || grid[m - 1][n - 1] == '(') return false;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k <= (m + n) / 2; ++k) {
                    visited[i][j][k] = false;
                }
            }
        }

        return dfs(0, 0, 0, grid);
    }
};
