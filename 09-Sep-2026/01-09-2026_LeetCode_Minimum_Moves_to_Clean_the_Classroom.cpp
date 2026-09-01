/*
=========================================================
Date        : 01-09-2026
Problem Name: Minimum Moves to Clean the Classroom
Platform    : LeetCode
Difficulty  : Medium
Tags        : Array, Breadth-First Search, Bit Manipulation, Matrix

Problem Summary:
- Clean all litter ('L') in an m x n classroom starting from 'S' with a fixed energy capacity.
- Moving costs 1 energy; reaching 0 energy halts movement unless standing on a reset area ('R') which refills energy to max.
- Find the minimum moves to collect all litter items, or return -1 if impossible.

Key Observation:
- Since the number of litter items is small (at most 10), we can represent collected litter as a bitmask.
- BFS state can be tracked via (row, col, collected_mask) with the maximum remaining energy seen so far for pruning.
=========================================================
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 1: State-Space BFS with Bitmask and Energy Pruning
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  - We need the shortest path (minimum moves) to achieve full litter collection (mask == (1 << num_litter) - 1).
  - A standard BFS guarantees finding the minimum step count first, but states can be revisited if we reach them with strictly higher energy.

• Approach:
  - Identify starting position 'S' and index each litter cell 'L' from 0 to k - 1 (k <= 10).
  - Use a BFS queue storing (row, col, mask, current_energy, moves).
  - Maintain a 3D array max_energy[r][c][mask] initialized to -1 to prune states that reach the same position and collected mask with <= energy.
  - In each transition, move to valid 4-directional adjacent cells, decrement energy, update collected litter bitmask, refill energy to max if landing on 'R', and push to queue if the new energy exceeds max_energy[nr][nc][new_mask].

• Why it Works:
  - BFS traverses in increasing order of moves, so the first time all litter items are collected, the move count is optimal.
  - Tracking max remaining energy ensures we explore new valid paths without falling into infinite cycles.

• Time Complexity (TC) : O(M * N * 2^K * E), where M, N <= 20, K <= 10, E <= 50.
• Space Complexity (SC): O(M * N * 2^K) to store maximum energy per state and BFS queue.
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
FINAL APPROACH SELECTION
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
- The Bitmask BFS with maximum energy pruning is chosen as it directly finds the minimum step count in level-by-level traversal.
- It prevents exponential state explosion through effective 3D state deduplication while respecting energy limits and reset tiles.
*/

#include <vector>
#include <string>
#include <queue>
#include <tuple>
#include <cstring>

using namespace std;

class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();
        
        int start_r = -1, start_c = -1;
        vector<pair<int, int>> litters;
        
        // Locate starting position and assign indices to all litter tiles
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (classroom[r][c] == 'S') {
                    start_r = r;
                    start_c = c;
                } else if (classroom[r][c] == 'L') {
                    litters.push_back({r, c});
                }
            }
        }
        
        int k = litters.size();
        int full_mask = (1 << k) - 1;
        
        // If there is no litter to collect, 0 moves are needed
        if (full_mask == 0) return 0;
        
        // Map litter positions to their respective bit index
        vector<vector<int>> litter_idx(m, vector<int>(n, -1));
        for (int i = 0; i < k; ++i) {
            litter_idx[litters[i].first][litters[i].second] = i;
        }
        
        // max_energy_seen[r][c][mask] stores the maximum energy when visiting (r, c) with subset mask
        // Dimensions: 20 x 20 x 1024
        static int max_energy_seen[20][20][1024];
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                for (int mask = 0; mask <= full_mask; ++mask) {
                    max_energy_seen[r][c][mask] = -1;
                }
            }
        }
        
        // Queue elements: {row, col, mask, current_energy, steps}
        queue<tuple<int, int, int, int, int>> q;
        
        q.push({start_r, start_c, 0, energy, 0});
        max_energy_seen[start_r][start_c][0] = energy;
        
        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};
        
        while (!q.empty()) {
            auto [r, c, mask, e, steps] = q.front();
            q.pop();
            
            // If current remaining energy is less than what was recorded for this state, skip
            if (e < max_energy_seen[r][c][mask]) continue;
            
            // If all litter is collected, return the minimum steps
            if (mask == full_mask) {
                return steps;
            }
            
            // Cannot move further if energy is depleted
            if (e == 0) continue;
            
            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                
                // Boundary and obstacle check
                if (nr < 0 || nr >= m || nc < 0 || nc >= n || classroom[nr][nc] == 'X') {
                    continue;
                }
                
                int next_e = e - 1;
                int next_mask = mask;
                
                // Collect litter if present
                if (classroom[nr][nc] == 'L') {
                    int idx = litter_idx[nr][nc];
                    if (idx != -1) {
                        next_mask |= (1 << idx);
                    }
                }
                
                // Refill energy if stepped on reset area 'R'
                if (classroom[nr][nc] == 'R') {
                    next_e = energy;
                }
                
                // Check if this gives a strictly higher energy for the same state
                if (next_e > max_energy_seen[nr][nc][next_mask]) {
                    max_energy_seen[nr][nc][next_mask] = next_e;
                    q.push({nr, nc, next_mask, next_e, steps + 1});
                }
            }
        }
        
        return -1;
    }
};
