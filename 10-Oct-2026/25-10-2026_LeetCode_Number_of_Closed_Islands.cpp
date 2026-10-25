/*
=========================================================
Date        : 25-10-2026
Problem Name: Number of Closed Islands
Platform    : LeetCode
Difficulty  : Medium
Tags        : DFS, BFS, Matrix, Graph

Problem Summary:
Given a grid where 0 represents land and 1 represents water,
return the number of islands completely surrounded by water.
Any island touching the boundary is not considered closed.

Key Observation:
Remove all boundary-connected land cells first.
The remaining land components are closed islands.
=========================================================
*/

/*
=========================================================
Approach 1: DFS + Boundary Flood Fill (Optimal)

Intuition:
- A closed island cannot touch the boundary.
- Boundary-connected lands are invalid.

Approach:
- Flood-fill all boundary-connected 0s.
- Count remaining connected components of 0s.

Why it Works:
- Every remaining land component is completely enclosed.

TC: O(m * n)
SC: O(m * n) (recursion stack worst case)
=========================================================
*/

/*
Why this approach?
- Simple and interview-friendly.
- Visits every cell at most once.
- Cleaner than checking boundary reachability for every island.
*/

class Solution {
private:
    int m, n;

    void dfs(vector<vector<int>>& grid, int r, int c) {
        if (r < 0 || c < 0 || r >= m || c >= n || grid[r][c] == 1)
            return;

        grid[r][c] = 1;

        dfs(grid, r + 1, c);
        dfs(grid, r - 1, c);
        dfs(grid, r, c + 1);
        dfs(grid, r, c - 1);
    }

public:
    int closedIsland(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();

        for (int i = 0; i < m; i++) {
            dfs(grid, i, 0);
            dfs(grid, i, n - 1);
        }

        for (int j = 0; j < n; j++) {
            dfs(grid, 0, j);
            dfs(grid, m - 1, j);
        }

        int closedIslands = 0;

        for (int i = 1; i < m - 1; i++) {
            for (int j = 1; j < n - 1; j++) {
                if (grid[i][j] == 0) {
                    ++closedIslands;
                    dfs(grid, i, j);
                }
            }
        }

        return closedIslands;
    }
};
