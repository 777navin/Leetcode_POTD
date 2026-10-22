/*
=========================================================
Date        : 22-10-2026
Problem Name: Minimum Operations to Sort a Permutation
Platform    : LeetCode
Difficulty  : Medium
Tags        : Array, Breadth-First Search

Problem Summary:
- Given a permutation of integers from 0 to n - 1.
- Allowed operations: 
  1. Reverse the entire array.
  2. Rotate Left by One (move first element to the end).
- Return the minimum number of operations to sort the array in increasing order, or -1 if impossible.

Key Observation:
- Each reachable array belongs to one of two families: rotations of the original array (type 0) or rotations of the reversed array (type 1).
- We can use a Breadth-First Search (BFS) over the compressed state space `(type, shift)` where there are 2n total states.
=========================================================
*/

#include <vector>
#include <queue>
#include <algorithm>

class Solution {
public:
    /*
    Approach: Breadth-First Search on State Space
    
    • Intuition:
      - Since the allowed operations only generate rotations of either the original array or the reversed array, every reachable configuration can be mapped to a state defined by `(type, shift)`.
    
    • Approach:
      - Represent states as `(type, shift)` where `type` is 0 (rotation of original) or 1 (rotation of reversed), and `shift` denotes the number of left rotations.
      - Use BFS from `(0, 0)` representing the initial input state.
      - Transition 1 (Left Rotate): `shift` becomes `(shift + 1) % n`.
      - Transition 2 (Reverse): `type` toggles, and `shift` becomes `(n - shift) % n`.
      - Find the target state that corresponds to the sorted array.

    • Why it Works:
      - The state space is extremely small ($2n$ states, where $n \le 10^5$), allowing an efficient $O(n)$ BFS traversal.

    • Time Complexity (TC): O(n)
    • Space Complexity (SC): O(n)
    */

    int minOperations(std::vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return 0;

        // Helper function to check if the current state matches a sorted cyclic shift
        // or a sorted reversed cyclic shift.
        // Instead of full BFS queue simulation which can be optimized, 
        // we can directly test valid target shifts or use the state graph shortest path.
        
        // Let's implement the state graph BFS:
        // States: 2 * n states. State index = type * n + shift.
        // We find the starting shift of nums relative to [0, 1, ..., n-1] or reversed.
        
        // Let's determine initial type and shift of `nums`.
        int init_type = 0, init_shift = -1;
        
        // Check if nums is a rotation of [0, 1, ..., n-1]
        for (int i = 0; i < n; ++i) {
            bool ok = true;
            for (int j = 0; j < n; ++j) {
                if (nums[(i + j) % n] != j) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                init_type = 0;
                init_shift = i;
                break;
            }
        }
        
        // Check if nums is a rotation of [n-1, n-2, ..., 0]
        if (init_shift == -1) {
            for (int i = 0; i < n; ++i) {
                bool ok = true;
                for (int j = 0; j < n; ++j) {
                    if (nums[(i + j) % n] != n - 1 - j) {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    init_type = 1;
                    init_shift = i;
                    break;
                }
            }
        }

        if (init_shift == -1) return -1; // Not reachable from the allowed operations

        // BFS to find minimum distance from (0, 0) to (init_type, init_shift)
        // Queue stores {type, shift}
        std::vector<std::vector<int>> dist(2, std::vector<int>(n, -1));
        std::queue<std::pair<int, int>> q;

        dist[0][0] = 0;
        q.push({0, 0});

        while (!q.empty()) {
            auto [t, s] = q.front();
            q.pop();

            if (t == init_type && s == init_shift) {
                return dist[t][s];
            }

            // Operation 1: Rotate Left
            int next_t1 = t;
            int next_s1 = (s + 1) % n;
            if (dist[next_t1][next_s1] == -1) {
                dist[next_t1][next_s1] = dist[t][s] + 1;
                q.push({next_t1, next_s1});
            }

            // Operation 2: Reverse Array
            int next_t2 = 1 - t;
            int next_s2 = (n - s) % n;
            if (dist[next_t2][next_s2] == -1) {
                dist[next_t2][next_s2] = dist[t][s] + 1;
                q.push({next_t2, next_s2});
            }
        }

        return -1;
    }
};
