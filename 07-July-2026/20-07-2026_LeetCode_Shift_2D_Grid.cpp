/*
=========================================================
Date        : 20-07-2026
Problem Name: Shift 2D Grid
Platform    : LeetCode
Difficulty  : Easy
Tags        : Array, Matrix, Simulation

Problem Summary:
Given an m x n 2D grid and an integer k, shift the grid k times. 
In one shift, elements move to the right, elements at the end of a row 
move to the beginning of the next row, and the last element wraps around to (0,0).

Key Observation:
Treating the 2D grid as a flattened 1D array of size m * n allows 
us to find the new position of any element using modulo arithmetic: 
new_index = (old_index + k) % (m * n).
=========================================================
*/

/*
---------------------------------------------------------
Approach 1: Simulation (K times)
---------------------------------------------------------
• Intuition: Literally simulate the shifting process cell-by-cell, repeating it k times.
• Approach: Create a temporary grid, copy elements shifted by 1 position, repeat this outer loop k times.
• Why it Works: It strictly follows the problem statement rules for a single shift operation.
• Time Complexity (TC): O(k * m * n)
• Space Complexity (SC): O(m * n) to store the temporary grid.

---------------------------------------------------------
Approach 2: Flattening & Modulo Arithmetic (Optimized)
---------------------------------------------------------
• Intuition: Instead of shifting k times step-by-step, we can precalculate the final resting position of each element directly.
• Approach: 
  - A 2D cell (i, j) corresponds to a 1D index: index = i * n + j.
  - Shifting by k moves it to: new_index = (index + k) % (m * n).
  - Convert new_index back to 2D: new_row = new_index / n, new_col = new_index % n.
• Why it Works: Mathematically models the wrap-around cyclic shift properties of a sequence.
• Time Complexity (TC): O(m * n) - each cell is processed exactly once.
• Space Complexity (SC): O(m * n) - required to build the output grid.
*/

/*
=========================================================
FINAL APPROACH CHOICE
=========================================================
• Chosen Approach: Approach 2 (Flattening & Modulo Arithmetic)
• Reason: It optimizes the time complexity from O(k * m * n) to O(m * n), completely eliminating the dependency on k.
*/

class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        int totalElements = m * n;
        
        // Optimize k if it is greater than total elements
        k = k % totalElements;
        
        // Initialize the result grid with the same dimensions
        vector<vector<int>> result(m, vector<int>(n));
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                // Convert 2D coordinate to 1D index
                int current1DIndex = i * n + j;
                
                // Calculate the new 1D index after shifting
                int new1DIndex = (current1DIndex + k) % totalElements;
                
                // Convert 1D index back to 2D coordinates
                int newRow = new1DIndex / n;
                int newCol = new1DIndex % n;
                
                // Place the current element into its new position
                result[newRow][newCol] = grid[i][j];
            }
        }
        
        return result;
    }
};
