/*
=========================================================
Date        : 12-09-2026
Problem Name: Maximum Score of Non-overlapping Intervals
Platform    : LeetCode (3414)
Difficulty  : Hard
Tags        : Array, Binary Search, Dynamic Programming, Sorting

Problem Summary:
Given an array of intervals [l_i, r_i, weight_i], choose up to 4 mutually
non-overlapping intervals (sharing any point is considered overlapping) to
maximize the total weight. Return the lexicographically smallest list of original
indices representing this choice.

Key Observation:
Since weights are strictly positive, any subset of maximum weight will be compared
lexicographically. By sorting intervals by right endpoint and running dynamic
programming for k = 1 to 4 with binary search for non-overlapping predecessors,
we can track optimal weights and lexicographically smallest index combinations.
=========================================================
*/

/*
APPROACH 1: Brute Force / Backtracking
---------------------------------------------------------
• Intuition:
  Try all possible subsets of up to 4 mutually non-overlapping intervals,
  compute their total weights, and track the maximum weight with the lexicographically
  smallest original indices.

• Approach:
  Generate combinations of size 1, 2, 3, and 4. Check pairwise overlap for each
  combination, updating the best answer when weight is greater or tied with smaller indices.

• Why it Works:
  Exhaustively explores all valid states by definition.

• Time Complexity (TC) : O(N^4)
• Space Complexity (SC): O(1) auxiliary space

---------------------------------------------------------
APPROACH 2: Dynamic Programming with Binary Search (Most Optimal)
---------------------------------------------------------
• Intuition:
  With k <= 4, this is a variation of the Weighted Interval Scheduling problem.
  Sorting intervals by right endpoint allows finding the latest non-overlapping interval
  via binary search. We maintain DP states storing (max_weight, lexicographically_smallest_indices).

• Approach:
  1. Store each interval along with its original index: (l, r, weight, id).
  2. Sort intervals primarily by right endpoint `r`.
  3. Precompute for each interval `i` the largest index `p < i` such that intervals[p].r < intervals[i].l.
  4. Let dp[k][i] represent the optimal result using at most `k` intervals from prefix `[0...i]`.
  5. Transitions:
     - Don't pick interval i: dp[k][i-1]
     - Pick interval i: combine intervals[i] with dp[k-1][p]
     - Compare states by total weight; on ties, compare the sorted index tuples lexicographically.

• Why it Works:
  Sorting by end times guarantees optimal substructure, and binary search allows O(log N)
  lookup for compatible predecessor intervals.

• Time Complexity (TC) : O(K * N * log N) where K = 4
• Space Complexity (SC): O(K * N) to store DP states and paths
*/

/*
FINAL APPROACH:
We implement the DP with Binary Search approach. It processes 50,000 intervals
well within the time limit by reducing the search space from exponential/quartic
to O(K * N log N), precisely handling tie-breaking for lexicographically smallest indices.
*/

#include <vector>
#include <array>
#include <algorithm>

using namespace std;

class Solution {
    struct Interval {
        int l, r, weight, id;
    };

    struct State {
        long long weight = 0;
        vector<int> indices;

        bool operator<(const State& other) const {
            if (weight != other.weight) {
                return weight < other.weight;
            }
            // Tie-breaking: smaller lexicographical index list is better
            return indices > other.indices;
        }
    };

public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<Interval> arr(n);
        for (int i = 0; i < n; ++i) {
            arr[i] = {intervals[i][0], intervals[i][1], intervals[i][2], i};
        }

        // Sort by right boundary, then left boundary, then original index
        sort(arr.begin(), arr.end(), [](const Interval& a, const Interval& b) {
            if (a.r != b.r) return a.r < b.r;
            if (a.l != b.l) return a.l < b.l;
            return a.id < b.id;
        });

        // Precompute the latest non-overlapping interval for each interval
        vector<int> prev(n, -1);
        for (int i = 0; i < n; ++i) {
            int low = 0, high = i - 1, best = -1;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (arr[mid].r < arr[i].l) {
                    best = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
            prev[i] = best;
        }

        // dp[k][i + 1]: best choice using at most k intervals from arr[0...i]
        vector<vector<State>> dp(5, vector<State>(n + 1));

        for (int k = 1; k <= 4; ++k) {
            for (int i = 0; i < n; ++i) {
                // Option 1: Do not include arr[i]
                State best = dp[k][i];

                // Option 2: Include arr[i]
                int p = prev[i];
                State take = dp[k - 1][p + 1];
                take.weight += arr[i].weight;
                
                // Insert current index maintaining sorted order
                take.indices.push_back(arr[i].id);
                sort(take.indices.begin(), take.indices.end());

                if (best < take) {
                    best = move(take);
                }

                dp[k][i + 1] = move(best);
            }
        }

        return dp[4][n].indices;
    }
};
