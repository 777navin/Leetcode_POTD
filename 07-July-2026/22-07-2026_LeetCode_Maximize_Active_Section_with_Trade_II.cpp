/*
=========================================================
Date        : 22-07-2026
Problem Name: 3501. Maximize Active Section with Trade II
Platform    : LeetCode
Difficulty  : Hard
Tags        : Array, String, Binary Search, Segment Tree

Problem Summary:
Given a binary string 's' and range queries [l, r], each query considers the substring s[l...r] 
augmented with '1's at both ends. We can perform at most one trade strictly inside the substring: 
convert a block of '1's surrounded by '0's to '0's, and a block of '0's surrounded by '1's to '1's.
We need to return the maximum number of '1's in the ENTIRE string 's' after a valid trade.

Key Observation:
Performing a trade strictly inside the substring means sacrificing a '1'-block completely 
contained in the substring to merge its adjacent '0'-blocks, and then flipping that merged 
'0'-block to '1's. The net gain in '1's is the sum of the lengths of these adjacent '0'-blocks.
The total number of '1's in 's' becomes `total_ones_in_s + max_gain_in_substring`.
=========================================================
*/

/*
=========================================================
APPROACH 1: Binary Search + Segment Tree (RMQ)
=========================================================

• Intuition:
  - Any valid trade sacrifices a '1'-block (fully inside the query range) to merge its left 
    and right '0'-blocks.
  - The gain from sacrificing a '1'-block is `len(left_0) + len(right_0)`.
  - To maximize the final '1's in the string, we need to find the maximum possible gain 
    among all valid '1'-blocks inside the query range [l, r].

• Approach:
  - Pre-extract all '1'-segments (contiguous blocks of '1's) and their start/end indices.
  - Precompute the gain for each '1'-segment assuming it is fully unrestricted by query bounds.
  - Build a Segment Tree over these precomputed gains for O(log N) Range Maximum Queries (RMQ).
  - For each query [l, r], use binary search to find the range of '1'-segments `[a, b]` that are 
    strictly inside [l, r] (i.e., start > l and end < r).
  - If a valid range exists, calculate the gain for the boundary segments `a` and `b` manually 
    (handling truncation at `l` and `r`), and use the Segment Tree to get the max gain for all 
    inner segments `[a+1, b-1]`.
  - The answer for the query is `total_ones + max_gain`.

• Why it Works:
  - Binary search isolates exactly the '1'-segments that can be sacrificed.
  - The manual boundary calculation precisely cuts off the '0'-segments at `l` and `r`.
  - Inner segments are fully enveloped by [l, r], so their precomputed gains remain perfectly valid.

• Time Complexity (TC):
  - Preprocessing: O(N) to find segments and build the Segment Tree.
  - Query: O(log N) per query due to binary search and Segment Tree query.
  - Overall TC: O(N + Q log N), easily passing constraints for N, Q <= 10^5.

• Space Complexity (SC):
  - O(N) auxiliary space for storing the segments and the Segment Tree array.
=========================================================
*/

/*
=========================================================
FINAL APPROACH
=========================================================
• We use the Segment Tree + Binary Search approach. It handles queries dynamically in O(log N) time
  while mathematically maintaining the exact boundary truncations without iterating elements.
=========================================================
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
private:
    struct SegmentTree {
        int n;
        vector<int> tree;

        SegmentTree(int size) {
            n = size;
            if (n > 0) {
                tree.assign(4 * n, 0);
            }
        }

        void build(const vector<int>& arr, int node, int start, int end) {
            if (start == end) {
                tree[node] = arr[start];
                return;
            }
            int mid = start + (end - start) / 2;
            build(arr, 2 * node, start, mid);
            build(arr, 2 * node + 1, mid + 1, end);
            tree[node] = max(tree[2 * node], tree[2 * node + 1]);
        }

        int query(int node, int start, int end, int l, int r) {
            if (r < start || end < l) return 0;
            if (l <= start && end <= r) return tree[node];
            int mid = start + (end - start) / 2;
            return max(query(2 * node, start, mid, l, r), 
                       query(2 * node + 1, mid + 1, end, l, r));
        }
    };

public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.length();
        int total_ones = 0;
        
        // Extract all '1'-segments (blocks of 1s)
        vector<pair<int, int>> ones;
        vector<int> first_vals, second_vals;
        
        for (int i = 0; i < n; ) {
            if (s[i] == '1') {
                int j = i;
                while (j < n && s[j] == '1') j++;
                ones.push_back({i, j - 1});
                first_vals.push_back(i);
                second_vals.push_back(j - 1);
                total_ones += (j - i);
                i = j;
            } else {
                i++;
            }
        }
        
        int m = ones.size();
        vector<int> pre_gain(m, 0);
        
        // Precompute the maximum unrestricted gain for each '1'-segment
        for (int i = 0; i < m; ++i) {
            int left_zeros = ones[i].first - (i > 0 ? ones[i - 1].second + 1 : 0);
            int right_zeros = (i < m - 1 ? ones[i + 1].first - 1 : n - 1) - ones[i].second;
            pre_gain[i] = left_zeros + right_zeros;
        }
        
        SegmentTree st(m);
        if (m > 0) {
            st.build(pre_gain, 1, 0, m - 1);
        }
        
        vector<int> ans;
        ans.reserve(queries.size());
        
        for (const auto& q : queries) {
            int l = q[0], r = q[1];
            
            // Find the range of '1'-segments completely strictly inside [l, r]
            // start > l
            int a = upper_bound(first_vals.begin(), first_vals.end(), l) - first_vals.begin();
            // end < r
            int b = lower_bound(second_vals.begin(), second_vals.end(), r) - second_vals.begin() - 1;
            
            int max_gain = 0;
            
            if (a <= b) {
                if (a == b) {
                    // Only one valid '1'-segment
                    int left_zeros = ones[a].first - max(l, a > 0 ? ones[a - 1].second + 1 : l);
                    int right_zeros = min(r, a < m - 1 ? ones[a + 1].first - 1 : r) - ones[a].second;
                    max_gain = left_zeros + right_zeros;
                } else {
                    // Multiple valid '1'-segments
                    // Evaluate boundary segment 'a'
                    int left_a = ones[a].first - max(l, a > 0 ? ones[a - 1].second + 1 : l);
                    int right_a = ones[a + 1].first - 1 - ones[a].second;
                    max_gain = max(max_gain, left_a + right_a);
                    
                    // Evaluate boundary segment 'b'
                    int left_b = ones[b].first - 1 - ones[b - 1].second;
                    int right_b = min(r, b < m - 1 ? ones[b + 1].first - 1 : r) - ones[b].second;
                    max_gain = max(max_gain, left_b + right_b);
                    
                    // Evaluate completely inner segments using RMQ
                    if (a + 1 <= b - 1) {
                        max_gain = max(max_gain, st.query(1, 0, m - 1, a + 1, b - 1));
                    }
                }
            }
            
            // Answer is the total original '1's plus the maximum gain we achieved
            ans.push_back(total_ones + max_gain);
        }
        
        return ans;
    }
};
