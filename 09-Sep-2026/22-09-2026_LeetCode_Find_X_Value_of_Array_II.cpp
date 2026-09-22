/*
=========================================================
Date        : 22-09-2026
Problem Name: 3525. Find X Value of Array II
Platform    : LeetCode
Difficulty  : Hard
Tags        : Array, Math, Segment Tree

Problem Summary:
Given an array nums and integer k, handle point updates and queries.
Each query asks for the number of non-empty prefixes of the subarray
nums[start..n-1] whose product modulo k equals x.

Key Observation:
The previous Segment Tree implementation triggered a Time Limit Exceeded (TLE) 
because of the massive overhead from dynamically allocating memory using 
std::vector inside the Node struct during millions of tree merges. Replacing 
std::vector with a fixed-size std::array eliminates these allocations, bringing 
the constant time factor down drastically.
=========================================================
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACHES CONSIDERED
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

1. Segment Tree with std::vector (Previous - TLE)
• Intuition: Store product mod k and counts of prefix products in each node.
• Approach: Use std::vector<int> to store counts for each remainder.
• Why it Works: Correct logic but fails constraints.
• Time Complexity (TC): O(Q * k log N).
• Space Complexity (SC): O(N * k).
• Issue: Dynamic memory allocations (new/delete) for vectors during recursive merges cause massive overhead and TLE.

2. Segment Tree with Fixed-Size Array (Optimal - AC)
• Intuition: Since k is very small (<= 5), we don't need dynamic sizing.
• Approach: Replace std::vector<int> with std::array<int, 10>. 
• Why it Works: The Node struct becomes a Plain Old Data (POD) type. Copying it is almost instant and avoids all heap allocation overhead.
• Time Complexity (TC): O((N + Q) * k * log N).
• Space Complexity (SC): O(N * k).

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
FINAL APPROACH: Segment Tree with Fixed-Size Array
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Chosen because it solves the exact bottleneck causing the TLE.
• The O(k log N) per query remains theoretically identical, but practically runs orders of magnitude faster in C++.
*/

#include <vector>
#include <array>

using namespace std;

class Solution {
    struct Node {
        int prod;
        array<int, 10> count; // Using fixed size array to prevent dynamic allocation TLE
        
        Node() {
            prod = 1;
            count.fill(0);
        }
    };

    int n, K;
    vector<Node> tree;

    Node merge(const Node& left, const Node& right) {
        Node res;
        res.prod = (left.prod * right.prod) % K;
        
        for (int i = 0; i < K; ++i) {
            res.count[i] = left.count[i];
        }
        
        for (int r = 0; r < K; ++r) {
            if (right.count[r] > 0) {
                int new_r = (left.prod * r) % K;
                res.count[new_r] += right.count[r];
            }
        }
        return res;
    }

    void build(int node, int l, int r, const vector<int>& nums) {
        if (l == r) {
            int rem = nums[l] % K;
            if (rem < 0) rem += K; // Handle negative numbers safely
            tree[node].prod = rem;
            tree[node].count[rem] = 1;
            return;
        }
        int mid = l + (r - l) / 2;
        build(2 * node, l, mid, nums);
        build(2 * node + 1, mid + 1, r, nums);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    void update(int node, int l, int r, int idx, int val) {
        if (l == r) {
            tree[node].count.fill(0);
            int rem = val % K;
            if (rem < 0) rem += K;
            tree[node].prod = rem;
            tree[node].count[rem] = 1;
            return;
        }
        int mid = l + (r - l) / 2;
        if (idx <= mid) {
            update(2 * node, l, mid, idx, val);
        } else {
            update(2 * node + 1, mid + 1, r, idx, val);
        }
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    Node query(int node, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return tree[node];
        }
        int mid = l + (r - l) / 2;
        if (qr <= mid) {
            return query(2 * node, l, mid, ql, qr);
        }
        if (ql > mid) {
            return query(2 * node + 1, mid + 1, r, ql, qr);
        }
        Node left_res = query(2 * node, l, mid, ql, qr);
        Node right_res = query(2 * node + 1, mid + 1, r, ql, qr);
        return merge(left_res, right_res);
    }

public:
    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
        n = nums.size();
        K = k;
        tree.assign(4 * n, Node());

        build(1, 0, n - 1, nums);

        vector<int> result;
        result.reserve(queries.size());

        for (const auto& q : queries) {
            int idx = q[0];
            int val = q[1];
            int start = q[2];
            int x = q[3];

            update(1, 0, n - 1, idx, val);
            Node seg = query(1, 0, n - 1, start, n - 1);
            result.push_back(seg.count[x]);
        }

        return result;
    }
};
