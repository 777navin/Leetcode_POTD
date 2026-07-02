/*
=========================================================
Date        : 02-07-2026
Problem Name: Find a Safe Walk Through a Grid
Platform    : LeetCode
Difficulty  : Medium
Tags        : Array, Breadth-First Search, Graph Theory, Heap (Priority Queue), Matrix, Shortest Path

Problem Summary:
Given an m x n binary matrix 'grid' and an integer 'health'. You start at the top-left 
corner (0, 0) and want to reach the bottom-right corner (m - 1, n - 1). You can move 
up, down, left, or right to adjacent cells as long as your health remains strictly 
positive (> 0). Moving into an unsafe cell (where grid[i][j] == 1) reduces your 
health by 1. Return true if you can reach the destination with 1 or more health, 
otherwise false.

Constraints:
- m == grid.length, n == grid[i].length
- 1 <= m, n <= 50
- 2 <= m * n
- 1 <= health <= m + n
- grid[i][j] is either 0 or 1.

Key Observation:
The compile error was caused by an incorrect type initialization on line 113. 
`vector<vector<int>>(n, INT_MAX)` attempts to initialize an inner vector with another 2D vector type, 
which is invalid. It should be a standard 1D `vector<int>`. Once fixed, maximizing the remaining health 
at the destination is equivalent to minimizing the number of unsafe cells (1s) encountered. 
Because the weights are only 0 and 1, 0-1 BFS is the most optimal approach.
=========================================================
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 1: Dijkstra's Algorithm (Priority Queue)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition: Track the maximum health remaining to reach each cell. Alternatively, 
  find the path that minimizes total health lost. A min-heap can systematically 
  explore paths by prioritizing cells with the least health cost.
• Idea: Maintain a 2D array 'cost' initialized to infinity. Use a priority queue 
  storing {health_lost, r, c}. Traverse in 4 directions, updating the minimum cost 
  to reach adjacent cells.
• Dry Run: For Example 1 with grid = [[0,1,0,0,0],[0,1,0,1,0],[0,0,0,1,0]], health = 1:
  Start at (0,0) with cost = grid[0][0] = 0. Explore Neighbors. The algorithm finds 
  a path to (2,4) with a total cost of 0. Final health = 1 - 0 = 1 >= 1. Returns true.
• Why it works: Dijkstra guarantees the shortest path (minimum health loss) in graphs 
  with non-negative edge weights.
• Time Complexity: O(m * n * log(m * n)) because each cell is pushed/popped from the 
  priority queue at most once.
• Space Complexity: O(m * n) for the cost tracking matrix and the priority queue.
• Advantages: Standard, robust algorithm for finding single-source shortest paths.
• Disadvantages: Priority queue introduces a logarithmic factor overhead.
• When to use: When graph edge weights vary across multiple non-negative values.
• Why next approach is better: Since the costs are strictly 0 and 1, we can eliminate 
  the O(log(m*n)) factor using a double-ended queue (Deque).

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 2: 0-1 BFS (Most Optimal)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition: When edge weights are strictly 0 and 1, we don't need a heavy priority queue. 
  A standard `std::deque` allows us to push 0-cost moves to the front and 1-cost moves 
  to the back, keeping the queue naturally sorted by cost.
• Idea: Initialize a 2D array 'min_loss' with a high value. Start at (0,0) with initial 
  loss = grid[0][0]. If an adjacent cell has a grid value of 0, push it to the front of 
  the deque; if it's 1, push it to the back.
• Dry Run: 
  - Pop (0,0) with loss 0. 
  - Neighbors: (0,1) has grid=1 -> push back with loss 1. (1,0) has grid=0 -> push front with loss 0.
  - Deque always processes lower costs first, ensuring optimal exploration linearly.
• Why it works: Pushing 0-weight edges to the front preserves the monotonic property of 
  the BFS queue without explicit sorting.
• Time Complexity: O(m * n) since each cell is processed at most once with O(1) deque operations.
• Space Complexity: O(m * n) to maintain the min_loss matrix and the deque.
• Advantages: Avoids sorting overhead, achieving strictly linear time complexity.
• Disadvantages: Slightly more complex queue logic compared to standard BFS.
• When to use: Perfectly tailored for graphs containing only 0 and 1 cost transitions.
*/

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// COMPARISON TABLE
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// -----------------------------------------------------------------------------
// Method            | Idea               | Time              | Space    | Difficulty | Recommended
// -----------------------------------------------------------------------------
// Dijkstra's Algorithm| Min-Heap Tracking  | O(m * n * log(MN))| O(m * n) | Medium     | Yes
// 0-1 BFS           | Deque Front/Back   | O(m * n)          | O(m * n) | Medium     | **Yes (Best)**
// -----------------------------------------------------------------------------

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
FINAL RECOMMENDED APPROACH: 0-1 BFS
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
The 0-1 BFS implementation is chosen as the most optimal solution because it guarantees 
a strict linear time complexity of O(m * n). The compile error has been resolved by fixing 
the 2D vector initialization syntax.
*/

#include <vector>
#include <deque>
#include <climits>

using namespace std;

class Solution {
public:
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int m = grid.size();
        int n = grid[0].size();
        
        // Fixed Compile Error: 
        // Changed vector<vector<int>>(n, INT_MAX) to vector<int>(n, INT_MAX)
        vector<vector<int>> min_loss(m, vector<int>(n, INT_MAX));
        
        // Deque for 0-1 BFS: stores pairs of {row, col}
        deque<pair<int, int>> dq;
        
        // Initialize start position
        min_loss[0][0] = grid[0][0];
        dq.push_back({0, 0});
        
        // Direction vectors for moving up, down, left, and right
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        while (!dq.empty()) {
            auto [r, c] = dq.front();
            dq.pop_front();
            
            // Optimization: If we reached the destination, we can stop early
            if (r == m - 1 && c == n - 1) {
                break;
            }
            
            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                
                // Check grid boundaries
                if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
                    int weight = grid[nr][nc];
                    
                    // Relaxation step
                    if (min_loss[r][c] + weight < min_loss[nr][nc]) {
                        min_loss[nr][nc] = min_loss[r][c] + weight;
                        
                        // 0-1 BFS positioning logic
                        if (weight == 0) {
                            dq.push_front({nr, nc});
                        } else {
                            dq.push_back({nr, nc});
                        }
                    }
                }
            }
        }
        
        // Total health remaining = original health - minimum health lost
        int remaining_health = health - min_loss[m - 1][n - 1];
        
        return remaining_health >= 1;
    }
};

// 02-07-2026_LeetCode_Find_a_Safe_Walk_Through_a_Grid.cpp
