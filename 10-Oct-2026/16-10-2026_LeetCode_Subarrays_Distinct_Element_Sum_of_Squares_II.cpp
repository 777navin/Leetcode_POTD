/*
=========================================================
Date        : 16-10-2026
Problem Name: Subarrays Distinct Element Sum of Squares II
Platform    : LeetCode
Difficulty  : Hard
Tags        : Array, Segment Tree, Monotonic Stack

Problem Summary:
- Given a 0-indexed integer array nums.
- The distinct count of a subarray is the number of distinct values in it.
- Return the sum of squares of distinct counts of all subarrays, modulo 10^9 + 7.

Key Observation:
- When the right endpoint j increases by 1, the contribution of each left endpoint i changes only for indices where nums[j] appeared previously.
=========================================================
*/

/*
=========================================================
APPROACH EXPLANATION
=========================================================

1. Brute Force
   • Intuition: Generate all possible subarrays, count distinct elements for each, square them, and sum up.
   • Approach: Use nested loops to iterate over all start and end points of subarrays.
   • Why it Works: Directly follows the problem statement definition.
   • Time Complexity (TC): O(N^3) or O(N^2) with a hash set.
   • Space Complexity (SC): O(N) to store distinct elements.

2. Optimized (Segment Tree with Lazy Propagation)
   • Intuition: Maintain the sum of squares of distinct counts dynamically as the right endpoint moves from left to right.
   • Approach: Use a segment tree to maintain the values of (cnt[i] + 1)^2 - cnt[i]^2 = 2*cnt[i] + 1 for active distinct elements in current subarrays ending at j, updating ranges when duplicate elements are encountered.
   • Why it Works: Efficiently updates range sums and retrieves total sum in O(log N) time per element.
   • Time Complexity (TC): O(N log N)
   • Space Complexity (SC): O(N)

=========================================================
FINAL APPROACH
=========================================================
- The optimized segment tree approach is chosen because N up to 10^5 requires an O(N log N) solution.
- It is significantly faster than the brute force approach, avoiding the O(N^2) bottleneck by maintaining interval sums dynamically.
*/

#include <vector>
#include <iostream>
#include <unordered_map>
#include <stack>

using namespace std;

class Solution {
    static constexpr int MOD = 1e9 + 7;

    struct Node {
        long long sum = 0;
        long long lazy = 0;
    };

    int n;
    vector<Node> tree;

    void push(int node, int l, int r) {
        if (tree[node].lazy != 0) {
            long long val = tree[node].lazy;
            int mid = l + (r - l) / 2;
            
            // Left child
            tree[2 * node].sum = (tree[2 * node].sum + val * (mid - l + 1)) % MOD;
            tree[2 * node].lazy = (tree[2 * node].lazy + val) % MOD;
            
            // Right child
            tree[2 * node + 1].sum = (tree[2 * node + 1].sum + val * (r - mid)) % MOD;
            tree[2 * node + 1].lazy = (tree[2 * node + 1].lazy + val) % MOD;
            
            tree[node].lazy = 0;
        }
    }

    void update(int node, int l, int r, int ql, int qr, long long val) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            tree[node].sum = (tree[node].sum + val * (r - l + 1)) % MOD;
            tree[node].lazy = (tree[node].lazy + val) % MOD;
            return;
        }
        push(node, l, r);
        int mid = l + (r - l) / 2;
        update(2 * node, l, mid, ql, qr, val);
        update(2 * node + 1, mid + 1, r, ql, qr, val);
        tree[node].sum = (tree[2 * node].sum + tree[2 * node + 1].sum) % MOD;
    }

public:
    int sumCounts(vector<int>& nums) {
        n = nums.size();
        tree.assign(4 * n + 1, Node());

        unordered_map<int, int> last_seen;
        vector<int> prev_idx(n);
        for (int i = 0; i < n; ++i) {
            if (last_seen.find(nums[i]) != last_seen.end()) {
                prev_idx[i] = last_seen[nums[i]];
            } else {
                prev_idx[i] = -1;
            }
            last_seen[nums[i]] = i;
        }

        long long total_sum = 0;
        long long current_sum_squares = 0;

        for (int j = 0; j < n; ++j) {
            int l = prev_idx[j] + 1;
            int r = j;
            
            // Update segment tree for the range [l, j]
            // We add 2 * sum_{i=l}^{j} (cnt[i]) + (j - l + 1)
            // Which corresponds to incrementing counts by 1 for range [l, j] and updating squares.
            update(1, 0, n - 1, l, r, 1);
            
            // Query current sum of squares which is stored at the root updated with linear terms
            // Actually, maintaining (cnt+1)^2 = cnt^2 + 2*cnt + 1
            // We can maintain linear prefix sum of counts in tree, and maintain total sum of squares directly.
            // Let's implement standard range add for linear term and compute total sum correctly.
            // Simplified standard approach for 2916:
        }

        // Re-adjusting standard solution template logic for LeetCode 2916:
        // Sum of squares of distinct counts = sum over all j of (2 * sum_{i=0}^{j} distinct_count(i..j) - distinct_count(j..j))
        // Using segment tree to maintain linear counts and their prefix sums.
        
        vector<long long> st_sum(4 * n + 1, 0);
        vector<long long> st_lazy(4 * n + 1, 0);
        
        auto range_add = [&](auto self, int node, int l, int r, int ql, int qr, long long val) -> void {
            if (ql > r || qr < l) return;
            if (ql <= l && r <= qr) {
                st_sum[node] = (st_sum[node] + val * (r - l + 1)) % MOD;
                st_lazy[node] = (st_lazy[node] + val) % MOD;
                return;
            }
            if (st_lazy[node] != 0) {
                int mid = l + (r - l) / 2;
                st_sum[2 * node] = (st_sum[2 * node] + st_lazy[node] * (mid - l + 1)) % MOD;
                st_lazy[2 * node] = (st_lazy[2 * node] + st_lazy[node]) % MOD;
                st_sum[2 * node + 1] = (st_sum[2 * node + 1] + st_lazy[node] * (r - mid)) % MOD;
                st_lazy[2 * node + 1] = (st_lazy[2 * node + 1] + st_lazy[node]) % MOD;
                st_lazy[node] = 0;
            }
            int mid = l + (r - l) / 2;
            self(self, 2 * node, l, mid, ql, qr, val);
            self(self, 2 * node + 1, mid + 1, r, ql, qr, val);
            st_sum[node] = (st_sum[2 * node] + st_sum[2 * node + 1]) % MOD;
        };

        auto query_sum = [&](auto self, int node, int l, int r, int ql, int qr) -> long long {
            if (ql > r || qr < l) return 0;
            if (ql <= l && r <= qr) return st_sum[node];
            if (st_lazy[node] != 0) {
                int mid = l + (r - l) / 2;
                st_sum[2 * node] = (st_sum[2 * node] + st_lazy[node] * (mid - l + 1)) % MOD;
                st_lazy[2 * node] = (st_lazy[2 * node] + st_lazy[node]) % MOD;
                st_sum[2 * node + 1] = (st_sum[2 * node + 1] + st_lazy[node] * (r - mid)) % MOD;
                st_lazy[2 * node + 1] = (st_lazy[2 * node + 1] + st_lazy[node]) % MOD;
                st_lazy[node] = 0;
            }
            int mid = l + (r - l) / 2;
            return (self(self, 2 * node, l, mid, ql, qr) + self(self, 2 * node + 1, mid + 1, r, ql, qr)) % MOD;
        };

        long long ans = 0;
        long long current_sum = 0;
        last_seen.clear();

        for (int j = 0; j < n; ++j) {
            int prev = last_seen.count(nums[j]) ? last_seen[nums[j]] : -1;
            last_seen[nums[j]] = j;

            long long sum_before = query_sum(query_sum, 1, 0, n - 1, prev + 1, j);
            long long added = (2 * sum_before + (j - prev)) % MOD;
            current_sum = (current_sum + added) % MOD;
            ans = (ans + current_sum) % MOD;

            range_add(range_add, 1, 0, n - 1, prev + 1, j, 1);
        }

        return ans;
    }
};
