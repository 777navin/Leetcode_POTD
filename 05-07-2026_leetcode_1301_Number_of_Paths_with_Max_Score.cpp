/*
=========================================================
Date        : 05-07-2026
Problem Name: 1301. Number of Paths with Max Score
Platform    : LeetCode
Difficulty  : Hard
Tags        : Array, Dynamic Programming, Matrix

• Problem Summary:
  - You are given a square matrix/grid starting at bottom-right ('S') and ending at top-left ('E').
  - Valid moves are Up, Left, and Up-Left.
  - Find the path that gives the maximum sum of numeric characters collected.
  - Return the maximum sum and the total number of paths that yield this sum, modulo 10^9 + 7.
  - Return [0, 0] if there is no valid path.

• Constraints:
  - 2 <= board.length == board[i].length <= 100
  - Board contains 'E', 'S', 'X' (obstacle), and digits '1'-'9'.

• Key Observation:
  - This is an optimal substructure problem solvable with DP. 
  - Every valid cell state (i, j) relies only on previously computed states (i+1, j), (i, j+1), and (i+1, j+1).
  - We can maintain two states per cell simultaneously: the max score achievable and the ways to achieve it.
=========================================================

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 1: 2D Dynamic Programming (Bottom-Up)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  Since we are traversing from bottom-right to top-left, we can iteratively calculate the answer for each cell starting from the target. The maximum score to reach a cell depends entirely on the maximum of its allowed previous positions.

• Idea & Approach:
  1. Initialize two 2D vectors: `dp` (for maximum scores initialized to -1) and `paths` (for path counts).
  2. Set base case at (n-1, n-1) where dp is 0 and paths is 1.
  3. Loop from bottom to top, right to left.
  4. Skip obstacles 'X'.
  5. For each valid transition (Down, Right, Diagonal-Down), find the maximum score.
  6. Add the count of paths from all previous states that yield this max score.
  7. Modulo the path counts by 10^9 + 7.

• Dry Run (Concept):
  - Starting at 'S', its dp is 0.
  - Moving to an adjacent number (e.g., '2'), its max score becomes 0 + 2 = 2. Paths = 1.
  - If a cell can be reached from left and down, both giving max score 5, its total paths will be (paths_left + paths_down).

• Time Complexity: O(N^2)
  - We iterate through each element of the N x N grid exactly once.
• Space Complexity: O(N^2)
  - For the 2D DP tables.

• Advantages: Easy to trace, debug, and logically structure.
• Disadvantages: Uses slightly more memory than strictly necessary.
• When to use: Best for interview scenarios where readability overrides extreme optimization.
• Why next approach is better: By tracking only the active rows, space can be reduced.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 2: Space-Optimized 1D Dynamic Programming
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  State transition for row `i` strictly relies on row `i` (computed to the right) and row `i+1`. We can maintain 1D arrays to drop the N^2 space constraint.

• Idea & Approach:
  1. Utilize 1D arrays for `dp` and `paths` of size N.
  2. Traverse similarly, keeping a `prev_dp` and `prev_paths` buffer for the (i+1, j+1) diagonal state before it gets overwritten by the new row calculation.

• Time Complexity: O(N^2)
• Space Complexity: O(N)

• Advantages: Highly space efficient.
• Disadvantages: Logic for retaining previous diagonal elements makes it slightly more prone to implementation bugs.
• When to use: Used strictly in competitive programming environments where memory limits are extremely tight.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
COMPARISON TABLE
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
-------------------------------------------------------
Method               | Time   | Space  | Diff | Recommended
-------------------------------------------------------
1. 2D DP Bottom-Up   | O(N^2) | O(N^2) | Med  | Yes (Best)
2. Space-Opt 1D DP   | O(N^2) | O(N)   | Hard | For memory caps
-------------------------------------------------------

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
FINAL RECOMMENDED APPROACH
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Approach 1 (2D DP Bottom-Up) is recommended. Given the constraints N <= 100, an N^2 matrix takes around 80KB of memory, which is practically zero. Using 2D matrices keeps the dependency logic crystal clear and eliminates off-by-one errors common in 1D reduction.
*/

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int n = board.size();
        int MOD = 1e9 + 7;
        
        // dp[i][j] tracks the max sum from (n-1, n-1) to (i, j).
        // -1 indicates the cell is unreachable.
        vector<vector<int>> dp(n, vector<int>(n, -1));
        
        // paths[i][j] tracks the number of ways to reach (i, j) with max sum.
        vector<vector<int>> paths(n, vector<int>(n, 0));
        
        // Base case setting for the starting point 'S'
        dp[n - 1][n - 1] = 0;
        paths[n - 1][n - 1] = 1;
        
        for (int i = n - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                // Skip obstacles and starting point
                if (board[i][j] == 'X') continue;
                if (i == n - 1 && j == n - 1) continue;
                
                int max_val = -1;
                
                // Transition 1: From Down (Moving Up)
                if (i + 1 < n && dp[i + 1][j] != -1) {
                    max_val = max(max_val, dp[i + 1][j]);
                }
                // Transition 2: From Right (Moving Left)
                if (j + 1 < n && dp[i][j + 1] != -1) {
                    max_val = max(max_val, dp[i][j + 1]);
                }
                // Transition 3: From Diagonal Down-Right (Moving Up-Left)
                if (i + 1 < n && j + 1 < n && dp[i + 1][j + 1] != -1) {
                    max_val = max(max_val, dp[i + 1][j + 1]);
                }
                
                // If a valid path exists to this current cell
                if (max_val != -1) {
                    long long ways = 0;
                    
                    // Accumulate paths from dependencies that match the max_val
                    if (i + 1 < n && dp[i + 1][j] == max_val) {
                        ways = (ways + paths[i + 1][j]) % MOD;
                    }
                    if (j + 1 < n && dp[i][j + 1] == max_val) {
                        ways = (ways + paths[i][j + 1]) % MOD;
                    }
                    if (i + 1 < n && j + 1 < n && dp[i + 1][j + 1] == max_val) {
                        ways = (ways + paths[i + 1][j + 1]) % MOD;
                    }
                    
                    int current_val = (board[i][j] == 'E') ? 0 : (board[i][j] - '0');
                    dp[i][j] = max_val + current_val;
                    paths[i][j] = ways;
                }
            }
        }
        
        // If the target 'E' remains unreachable
        if (dp[0][0] == -1) {
            return {0, 0};
        }
        
        return {dp[0][0], paths[0][0]};
    }
};
