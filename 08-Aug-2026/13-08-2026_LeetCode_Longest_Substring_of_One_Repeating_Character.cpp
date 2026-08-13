/*
=========================================================
Date        : 13-08-2026
Problem Name: Longest Substring of One Repeating Character
Platform    : LeetCode
Difficulty  : Hard
Tags        : Array, String, Segment Tree, Ordered Set

Problem Summary:
Given a string s and k point update queries consisting of indices and target characters,
perform each update on s sequentially. After each update, find the length of the longest
substring consisting of only one repeating character. Return an array of these lengths.

Key Observation:
Since string modifications occur dynamically at specific indices, a Segment Tree can 
maintain character values, prefix lengths, suffix lengths, and maximum contiguous repeating 
lengths for substrings to support O(log n) updates and O(1) query lookups at the root node.
=========================================================
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH EXPLANATION
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

1. Brute Force
• Intuition:
  - Perform each character replacement sequentially and scan the updated string to find the longest repeating substring.
• Approach:
  - For each of the k queries, update s[idx] = char.
  - Traverse the entire string s from left to right, tracking the maximum contiguous identical character sequence length.
• Why it Works:
  - It directly implements the problem rules step-by-step for every query.
• Time Complexity (TC):
  - O(k * n), where n is the length of s and k is the number of queries. (Causes TLE)
• Space Complexity (SC):
  - O(1) auxiliary space (modifying s in-place).

2. Segment Tree (Most Optimal)
• Intuition:
  - We can divide string s into range segments using a Segment Tree.
  - When merging two adjacent segments, if the boundary characters match, the suffix of the left segment and the prefix of the right segment can combine into a longer contiguous substring.
• Approach:
  - Build a Segment Tree where each node tracks:
    1. prefix_char: Leftmost character in segment.
    2. suffix_char: Rightmost character in segment.
    3. pref: Length of longest repeating prefix substring in segment.
    4. suff: Length of longest repeating suffix substring in segment.
    5. mx: Maximum length of repeating substring anywhere within the segment.
    6. len: Total length of the segment.
  - Combine rule during tree updates:
    - If left_child.suffix_char == right_child.prefix_char:
      - Middle candidate = left_child.suff + right_child.pref.
      - Update max length node.mx = max({left.mx, right.mx, middle candidate}).
      - Adjust prefix/suffix length if left/right segment is completely filled with a single character.
  - Perform point updates in O(log n) time per query and read the answer directly from the root node (node 1).
• Why it Works:
  - Any contiguous repeating substring spanning across two halves must pass through the midpoint, which is captured by checking left segment's suffix and right segment's prefix.
• Time Complexity (TC):
  - O(n + k log n), where tree construction takes O(n) and each of the k updates takes O(log n).
• Space Complexity (SC):
  - O(n) to store the segment tree nodes.
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
FINAL APPROACH
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

• Chosen Approach: Segment Tree (Most Optimal)
• Why it is chosen:
  - Given n <= 10^5 and k <= 10^5, an O(k * n) brute force approach will result in Time Limit Exceeded (TLE).
  - The Segment Tree allows O(log n) dynamic updates and O(1) retrieval of the global maximum repeating character substring length from the root node after each query.
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
private:
    struct Node {
        char prefix_char;
        char suffix_char;
        int pref;
        int suff;
        int mx;
        int len;

        Node() : prefix_char('#'), suffix_char('#'), pref(0), suff(0), mx(0), len(0) {}
    };

    vector<Node> tree;

    Node merge(const Node& left, const Node& right) {
        Node parent;
        parent.len = left.len + right.len;
        parent.prefix_char = left.prefix_char;
        parent.suffix_char = right.suffix_char;

        // Base prefix and suffix lengths
        parent.pref = left.pref;
        parent.suff = right.suff;
        parent.mx = max(left.mx, right.mx);

        // Check boundary merger
        if (left.suffix_char == right.prefix_char) {
            parent.mx = max(parent.mx, left.suff + right.pref);
            
            if (left.pref == left.len) {
                parent.pref = left.len + right.pref;
            }
            if (right.suff == right.len) {
                parent.suff = right.len + left.suff;
            }
        }

        return parent;
    }

    void build(int node, int start, int end, const string& s) {
        if (start == end) {
            tree[node].prefix_char = s[start];
            tree[node].suffix_char = s[start];
            tree[node].pref = 1;
            tree[node].suff = 1;
            tree[node].mx = 1;
            tree[node].len = 1;
            return;
        }

        int mid = start + (end - start) / 2;
        build(2 * node, start, mid, s);
        build(2 * node + 1, mid + 1, end, s);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    void update(int node, int start, int end, int idx, char ch) {
        if (start == end) {
            tree[node].prefix_char = ch;
            tree[node].suffix_char = ch;
            tree[node].pref = 1;
            tree[node].suff = 1;
            tree[node].mx = 1;
            tree[node].len = 1;
            return;
        }

        int mid = start + (end - start) / 2;
        if (idx <= mid) {
            update(2 * node, start, mid, idx, ch);
        } else {
            update(2 * node + 1, mid + 1, end, idx, ch);
        }
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        int n = s.length();
        int k = queryIndices.size();
        tree.resize(4 * n);

        build(1, 0, n - 1, s);

        vector<int> result(k);
        for (int i = 0; i < k; ++i) {
            update(1, 0, n - 1, queryIndices[i], queryCharacters[i]);
            result[i] = tree[1].mx;
        }

        return result;
    }
};
