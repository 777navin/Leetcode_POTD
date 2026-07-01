/*
Date        : 01-07-2026
Problem Name: Find the Safest Path in a Grid
Platform    : LeetCode
Difficulty  : Medium
Tags        : Array, Binary Search, Breadth-First Search, Graph, Matrix, Heap (Priority Queue)

Problem Summary:
Given an n x n grid where 0 represents an empty cell and 1 represents a thief, find a path from (0, 0) to (n-1, n-1) such that the minimum Manhattan distance from any cell in the path to the nearest thief is maximized.

Constraints:

1 <= grid.length == n <= 400

grid[i].length == n

grid[i][j] is 0 or 1

At least one thief exists

Key Observation: This is a multi-source shortest path problem. We first use BFS to precompute the minimum Manhattan distance from every cell to the nearest thief. Then, the problem becomes finding a path where the minimum value along the path is as large as possible. This can be solved using either Dijkstra's algorithm (max-heap) or Binary Search on the answer combined with BFS/DFS to check path validity.
*/

#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
int maximumSafenessFactor(vector<vector<int>>& grid) {
int n = grid.size();
if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1) return 0;

    vector<vector<int>> dist(n, vector<int>(n, -1));
    queue<pair<int, int>> q;

    // Multi-source BFS to compute distance to nearest thief
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 1) {
                dist[i][j] = 0;
                q.push({i, j});
            }
        }
    }

    int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        for (auto& d : dirs) {
            int nr = r + d[0], nc = c + d[1];
            if (nr >= 0 && nr < n && nc >= 0 && nc < n && dist[nr][nc] == -1) {
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }

    // Dijkstra-like approach using Max-Heap to find the safest path
    // Priority Queue stores {safeness_factor, r, c}
    priority_queue<vector<int>> pq;
    pq.push({dist[0][0], 0, 0});
    
    vector<vector<int>> min_safeness(n, vector<int>(n, -1));
    min_safeness[0][0] = dist[0][0];

    while (!pq.empty()) {
        vector<int> curr = pq.top();
        pq.pop();
        int d = curr[0], r = curr[1], c = curr[2];

        if (r == n - 1 && c == n - 1) return d;

        for (auto& dir : dirs) {
            int nr = r + dir[0], nc = c + dir[1];
            if (nr >= 0 && nr < n && nc >= 0 && nc < n) {
                int new_safeness = min(d, dist[nr][nc]);
                if (new_safeness > min_safeness[nr][nc]) {
                    min_safeness[nr][nc] = new_safeness;
                    pq.push({new_safeness, nr, nc});
                }
            }
        }
    }

    return 0;
}
};

/*
Method          | Idea                               | Time      | Space    | Difficulty | Recommended
Dijkstra/Heap   | Max-heap tracks max-min safety     | O(N^2 logN)| O(N^2)   | Medium     | Yes Binary Search   | Binary search + BFS check validity | O(N^2 logN)| O(N^2)   | Medium     | Yes
*/

// Final Recommended Approach:
// Using a Priority Queue (Dijkstra-like) is often more intuitive for "bottleneck path" problems.
// It greedily explores paths that maintain the highest possible minimum safeness factor,
// ensuring the first time we reach (n-1, n-1), we have the optimal result.
