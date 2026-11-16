/*
=========================================================
Date        : 08-11-2026
Problem Name: Count Servers that Communicate
Platform    : LeetCode
Difficulty  : Medium
Tags        : Array, Matrix, Counting

Problem Summary:
- A server is represented by 1 and an empty cell by 0.
- Two servers can communicate if they lie in the same row
  or the same column.
- Return the number of servers that can communicate with
  at least one other server.

Key Observation:
- A server can communicate if its row count > 1
  OR its column count > 1.
=========================================================
*/

/*
=========================================================
Approach 1: Brute Force
=========================================================

Intuition:
- For every server, search its entire row and column.

Approach:
- If another server exists in the same row/column,
  count this server.

Why it Works:
- Directly verifies the communication condition.

TC:
- O(m * n * (m + n))

SC:
- O(1)
*/

/*
=========================================================
Approach 2: Optimized Counting (Chosen Approach)
=========================================================

Intuition:
- A server communicates if there is at least one more
  server in its row or column.

Approach:
- Count servers in every row.
- Count servers in every column.
- Traverse the grid again.
- Count a server if:
      rowCount[row] > 1
      OR
      colCount[col] > 1

Why it Works:
- Row/column frequencies completely determine whether
  a server can communicate.

TC:
- O(m * n)

SC:
- O(m + n)
*/

/*
Final Approach:
- The counting approach avoids repeatedly scanning rows
  and columns for every server.
- Row and column frequencies are precomputed once.
- This reduces the complexity from O(m*n*(m+n))
  to O(m*n), making it optimal for the constraints.
*/

class Solution {
public:
    int countServers(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();

        vector<int> rowCount(rows, 0);
        vector<int> colCount(cols, 0);

        // Count servers in each row and column
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == 1) {
                    rowCount[r]++;
                    colCount[c]++;
                }
            }
        }

        int communicatingServers = 0;

        // Count valid servers
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == 1 &&
                    (rowCount[r] > 1 || colCount[c] > 1)) {
                    communicatingServers++;
                }
            }
        }

        return communicatingServers;
    }
};
