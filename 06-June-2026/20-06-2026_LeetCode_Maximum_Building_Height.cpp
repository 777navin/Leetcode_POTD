/*
Date: 20-06-2026
Problem Name: Maximum Building Height
Platform: LeetCode
Difficulty: Hard
Tags: Array, Math, Sorting

Problem Summary:
You want to build n buildings labeled 1 to n. 
Building 1 must have a height of 0. 
The height difference between any two adjacent buildings cannot exceed 1.
You are given an array of `restrictions` where each building `id` is limited to `maxHeight`.
Return the maximum possible height of the tallest building.

Methods to Solve:
1. Two-Pass Optimization (Optimal Approach)

For EACH method include:

- Intuition:
  A restriction on a building affects the maximum possible heights of all other buildings 
  because the height can only increase or decrease by at most 1 per step.
  A building's height is constrained by restrictions both to its left and its right. 
  By doing a left-to-right pass, we propagate the restrictions forwards. 
  By doing a right-to-left pass, we propagate the restrictions backwards. 
  After both passes, every restriction reflects the true maximum height that specific 
  building can achieve. Finally, the absolute tallest building could be located somewhere 
  between two restricted buildings, forming a "peak".

- Approach:
  1. Push an initial restriction `{1, 0}` to represent the first building.
  2. Sort the restrictions array by building ID to process them sequentially.
  3. Push a final dummy restriction `{n, n - 1}` if building `n` is not in the restrictions 
     (since the max height could hypothetically grow up to n - 1).
  4. Left-to-Right Pass: Update each restriction's height based on the previous restriction.
     `h[i] = min(h[i], h[i-1] + dist)`
  5. Right-to-Left Pass: Update each restriction's height based on the next restriction.
     `h[i] = min(h[i], h[i+1] + dist)`
  6. Find Max Height: For every pair of adjacent restrictions, calculate the local peak 
     between them using the formula: `peak = (h1 + h2 + dist) / 2`.
  7. Return the global maximum peak.

- Dry Run (small example):
  Input: n = 5, restrictions = [[2,1],[4,1]]
  Initial + Sort: [[1,0], [2,1], [4,1], [5,4]]
  Left-to-Right Pass:
    - [2,1] dist=1 -> min(1, 0+1) = 1
    - [4,1] dist=2 -> min(1, 1+2) = 1
    - [5,4] dist=1 -> min(4, 1+1) = 2
  Right-to-Left Pass:
    - [4,1] dist=1 -> min(1, 2+1) = 1
    - [2,1] dist=2 -> min(1, 1+2) = 1
    - [1,0] dist=1 -> min(0, 1+1) = 0
  Peaks:
    - Between 1 and 2: (0 + 1 + 1)/2 = 1
    - Between 2 and 4: (1 + 1 + 2)/2 = 2
    - Between 4 and 5: (1 + 2 + 1)/2 = 2
  Result: 2

- Time Complexity: O(M log M) where M is the number of restrictions (due to sorting).
- Space Complexity: O(1) auxiliary space (modifying the input array in place).
- Why better than previous method: Creating an array of size `n` (up to 10^9) would result in Memory Limit Exceeded (MLE). Processing only the restrictions takes O(M log M) which easily passes.
- When to use: When dealing with rate-of-change constraints (gradient <= 1) over sparse points.

Comparison Table:
Method             | TC          | SC    | Best Use Case
-------------------|-------------|-------|-------------------------
Array Simulation   | O(N)        | O(N)  | Fails for large N (10^9)
Two-Pass (Sparse)  | O(M log M)  | O(1)  | Optimal, handles large N

Final Recommended Solution:
The two-pass mathematical constraint propagation is the only viable approach for 10^9 constraints.
*/

#include <vector>
#include <algorithm>

class Solution {
public:
    int maxBuilding(int n, std::vector<std::vector<int>>& restrictions) {
        // 1. Add implicit restriction for the first building
        restrictions.push_back({1, 0});
        
        // 2. Sort restrictions by building ID
        std::sort(restrictions.begin(), restrictions.end());
        
        // 3. Add dummy restriction for the last building if missing
        if (restrictions.back()[0] != n) {
            restrictions.push_back({n, n - 1}); // Height can grow by at most 1 per step
        }
        
        int m = restrictions.size();
        
        // 4. Left-to-Right Pass: Propagate constraints forwards
        for (int i = 1; i < m; ++i) {
            int dist = restrictions[i][0] - restrictions[i - 1][0];
            restrictions[i][1] = std::min(restrictions[i][1], restrictions[i - 1][1] + dist);
        }
        
        // 5. Right-to-Left Pass: Propagate constraints backwards
        for (int i = m - 2; i >= 0; --i) {
            int dist = restrictions[i + 1][0] - restrictions[i][0];
            restrictions[i][1] = std::min(restrictions[i][1], restrictions[i + 1][1] + dist);
        }
        
        // 6. Find the peak maximum height between any two restricted points
        int max_height = 0;
        for (int i = 1; i < m; ++i) {
            int dist = restrictions[i][0] - restrictions[i - 1][0];
            int h1 = restrictions[i - 1][1];
            int h2 = restrictions[i][1];
            
            int peak = h1 + (dist + h2 - h1) / 2;
            max_height = std::max(max_height, peak);
        }
        
        return max_height;
    }
};

