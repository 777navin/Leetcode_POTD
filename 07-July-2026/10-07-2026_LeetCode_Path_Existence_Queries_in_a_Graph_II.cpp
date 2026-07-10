/*
=========================================================
Date        : 10-07-2026
Problem Name: Path Existence Queries in a Graph II
Platform    : LeetCode
Difficulty  : Hard
Tags        : Array, Binary Search, Graph Theory, Sorting, Greedy

Problem Summary:
Given an array of node values, an undirected edge exists between nodes if their absolute value difference is <= maxDiff.
Answer multiple queries to find the minimum distance (shortest path) between two nodes u and v, returning -1 if unreachable.

Key Observation:
Since connectivity solely depends on value differences, sorting the values and greedily jumping to the furthest reachable value minimizes the shortest path.
=========================================================
*/

/*
1. Brute Force (BFS)
- Intuition: Model the problem as a standard unweighted graph and use BFS for shortest paths.
- Approach: Build an adjacency list by comparing every pair of nodes. If their difference is <= maxDiff, add an edge. Run BFS for each query.
- Why it Works: BFS guarantees the shortest path in any unweighted graph.
- Time Complexity (TC): O(Q * N^2) - Graph building is O(N^2), and each BFS explores up to O(N^2) edges. TLE for large constraints.
- Space Complexity (SC): O(N^2) to store the dense graph.

2. Most Optimal (Binary Lifting / Sparse Table)
- Intuition: Because reachability is strictly 1-dimensional, we can sort the values. To get from A to B with the minimum steps, we should always jump to the maximum reachable value.
- Approach: Sort a copy of `nums`. Precompute `up[i][0]` as the furthest right index reachable from `i` within `maxDiff`. Use Binary Lifting to build an `up[i][j]` table representing 2^j jumps. 
- Why it Works: The greedy jump strategy is provably optimal. Binary lifting allows us to compute the exact number of jumps needed in logarithmic time.
- Time Complexity (TC): O(N log N + Q log N) - Sorting and table construction takes O(N log N). Each query binary jumps in O(log N).
- Space Complexity (SC): O(N log N) - To store the sparse table for binary lifting.
*/

/*
FINAL APPROACH
We choose Binary Lifting because it optimally scales to handle large constraints (N, Q <= 10^5). 
By precomputing the furthest reachable nodes using powers of 2, we completely bypass the O(N^2) BFS overhead, condensing each query computation down to a lightning-fast O(log N).
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<int> sorted_nums = nums;
        sort(sorted_nums.begin(), sorted_nums.end());

        // For N <= 100,000, 2^17 > 100,000, so 18 is a safe logarithmic bound
        int LOG = 18;
        vector<vector<int>> up(n, vector<int>(LOG, 0));

        // Precompute up[i][0]: furthest reachable node to the right with 1 jump
        for (int i = 0; i < n; ++i) {
            int target = sorted_nums[i] + maxDiff;
            // Find the first element strictly greater than the target, then step back one
            auto it = upper_bound(sorted_nums.begin(), sorted_nums.end(), target);
            up[i][0] = distance(sorted_nums.begin(), it) - 1;
        }

        // Build Binary Lifting sparse table
        for (int j = 1; j < LOG; ++j) {
            for (int i = 0; i < n; ++i) {
                up[i][j] = up[up[i][j - 1]][j - 1];
            }
        }

        vector<int> ans;
        ans.reserve(queries.size());

        for (const auto& q : queries) {
            int u = q[0], v = q[1];
            
            // 0 distance if starting and ending at the exact same node
            if (u == v) {
                ans.push_back(0);
                continue;
            }

            int valU = nums[u], valV = nums[v];
            
            // Direction doesn't matter for distance, always travel left to right
            if (valU > valV) {
                swap(valU, valV);
            }

            // If it can be reached in exactly 1 jump
            if (valV - valU <= maxDiff) {
                ans.push_back(1);
                continue;
            }

            // Find starting index in the sorted array
            auto it = lower_bound(sorted_nums.begin(), sorted_nums.end(), valU);
            int idx = distance(sorted_nums.begin(), it);

            // Check if the target is completely unreachable even with infinite (2^17) jumps
            if (sorted_nums[up[idx][LOG - 1]] < valV) {
                ans.push_back(-1);
                continue;
            }

            int jumps = 0;
            
            // Greedily accumulate jumps using powers of 2 without crossing the target
            for (int j = LOG - 1; j >= 0; --j) {
                if (sorted_nums[up[idx][j]] < valV) {
                    idx = up[idx][j];
                    jumps += (1 << j);
                }
            }

            // We stopped right before reaching/crossing valV, so 1 final jump is required
            ans.push_back(jumps + 1);
        }

        return ans;
    }
};
