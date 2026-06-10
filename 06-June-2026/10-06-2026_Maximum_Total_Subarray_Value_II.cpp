/*
Date: 10-06-2026
Problem Name: Maximum Total Subarray Value II
Platform: LeetCode
Difficulty: Hard
Tags: Array, Greedy, Segment Tree, Heap (Priority Queue)

Problem Summary:
Given an integer array `nums` of length `n` and an integer `k`, you need to select exactly `k` distinct subarrays to maximize the total value. The value of a subarray is defined as the maximum element minus the minimum element in that subarray.

Methods to Solve:
1. Brute Force (Sorting all subarrays)
2. Optimal Approach (Sparse Table / RMQ + Max-Heap)

---------------------------------------------------------
Method 1: Brute Force
---------------------------------------------------------
- Intuition:
  The most straightforward way is to generate all possible subarrays, calculate the value (max - min) for each, store them in a list, sort the list in descending order, and sum up the top `k` values.
  
- Approach:
  1. Use two nested loops to iterate through all possible start (`l`) and end (`r`) indices.
  2. For each `(l, r)` pair, track the maximum and minimum values.
  3. Push `max - min` to an array.
  4. Sort the array descending and take the sum of the first `k` elements.

- Dry Run (small example):
  nums = [1,3,2], k = 2
  Subarrays:
  [1] -> max: 1, min: 1, val: 0
  [1, 3] -> max: 3, min: 1, val: 2
  [1, 3, 2] -> max: 3, min: 1, val: 2
  [3] -> max: 3, min: 3, val: 0
  [3, 2] -> max: 3, min: 2, val: 1
  [2] -> max: 2, min: 2, val: 0
  Values: [2, 2, 1, 0, 0, 0]. Top 2 sum = 2 + 2 = 4.

- Time Complexity: O(N^2 log(N^2)) to generate and sort.
- Space Complexity: O(N^2) to store all values.
- Why better than previous method: N/A (Baseline).
- When to use: Only when N <= 1000. Fails for N = 50,000.

---------------------------------------------------------
Method 2: Optimal Approach (RMQ + Max-Heap)
---------------------------------------------------------
- Intuition:
  Instead of evaluating all subarrays, we can systematically explore the most promising ones. For a fixed starting index `l`, the value `v(l, r) = max - min` is non-increasing as `r` moves left. This means the largest value starting at `l` is `v(l, n-1)`. We can use a Max-Heap to keep track of the largest available subarrays and eagerly pick the top `k`.
  
- Approach:
  1. Precompute Sparse Tables for Range Minimum Query (RMQ) and Range Maximum Query so we can find `max` and `min` of any subarray in O(1) time.
  2. Initialize a max-heap. For every starting index `l` from `0` to `n-1`, push the tuple `{v(l, n-1), l, n-1}` into the heap.
  3. Loop `k` times:
     a. Pop the top element (which is the maximum available subarray value).
     b. Add its value to our total answer.
     c. If the popped subarray was `nums[l..r]` and `r > l`, the next best candidate starting at `l` is `nums[l..r-1]`. Push `{v(l, r-1), l, r-1}` into the heap.
     
- Dry Run (small example):
  nums = [1,3,2], k = 2
  Heap initially holds maximums for ends at n-1:
  l=0, r=2 -> val: 2
  l=1, r=2 -> val: 1
  l=2, r=2 -> val: 0
  Heap state: {(2, 0, 2), (1, 1, 2), (0, 2, 2)}
  
  Pop 1: (2, 0, 2). Total = 2.
  Next for l=0 is r=1. v(0, 1) = 2. Push (2, 0, 1).
  Heap state: {(2, 0, 1), (1, 1, 2), (0, 2, 2)}
  
  Pop 2: (2, 0, 1). Total = 2 + 2 = 4.
  Next for l=0 is r=0. v(0, 0) = 0. Push (0, 0, 0).
  Loop ends (k=2). Return 4.

- Time Complexity: O(N log N) to build Sparse Tables + O(K log N) for heap operations. Total: O((N + K) log N).
- Space Complexity: O(N log N) for Sparse Tables + O(N) for Priority Queue. Total: O(N log N).
- Why better than previous method: Drastically reduces time and space from quadratic to linearithmic, easily passing constraints (N = 50,000, K = 100,000).
- When to use: Ideal for massive arrays where range queries and top-K extraction are needed.

---------------------------------------------------------
Comparison Table:
Method         | TC             | SC         | Best Use Case
---------------------------------------------------------
Brute Force    | O(N^2 log N)   | O(N^2)     | N <= 1000
Optimal (Heap) | O((N+K) log N) | O(N log N) | Large N & K (Current problem)

Final Recommended Solution: Optimal Approach (RMQ + Max-Heap)
*/

#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>

using namespace std;

class Solution {
public:
    long long maxTotalValue(vector<int>& nums, int k) {
        int n = nums.size();
        if (n == 0 || k == 0) return 0;
        
        int max_log = log2(n) + 1;
        
        // Sparse Tables for O(1) Range Maximum and Minimum Queries
        vector<vector<int>> st_max(n, vector<int>(max_log));
        vector<vector<int>> st_min(n, vector<int>(max_log));
        
        for (int i = 0; i < n; i++) {
            st_max[i][0] = nums[i];
            st_min[i][0] = nums[i];
        }
        
        for (int j = 1; j < max_log; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st_max[i][j] = max(st_max[i][j - 1], st_max[i + (1 << (j - 1))][j - 1]);
                st_min[i][j] = min(st_min[i][j - 1], st_min[i + (1 << (j - 1))][j - 1]);
            }
        }
        
        // Lambda to get max - min for a range [l, r] in O(1) time
        auto get_val = [&](int l, int r) -> int {
            if (l > r) return 0;
            int j = log2(r - l + 1);
            int max_val = max(st_max[l][j], st_max[r - (1 << j) + 1][j]);
            int min_val = min(st_min[l][j], st_min[r - (1 << j) + 1][j]);
            return max_val - min_val;
        };
        
        // Max-Heap stores pairs of {subarray_value, {start_index, end_index}}
        priority_queue<pair<int, pair<int, int>>> pq;
        
        // Initialize heap with the largest possible right bound for each left bound
        for (int l = 0; l < n; l++) {
            pq.push({get_val(l, n - 1), {l, n - 1}});
        }
        
        long long total_value = 0;
        
        // Greedily pick the top k non-overlapping sequence bounds
        while (k > 0 && !pq.empty()) {
            auto top = pq.top();
            pq.pop();
            
            int val = top.first;
            int l = top.second.first;
            int r = top.second.second;
            
            total_value += val;
            k--;
            
            // If we can still shrink the subarray from the right, push the next candidate
            if (r > l) {
                pq.push({get_val(l, r - 1), {l, r - 1}});
            }
        }
        
        return total_value;
    }
};
