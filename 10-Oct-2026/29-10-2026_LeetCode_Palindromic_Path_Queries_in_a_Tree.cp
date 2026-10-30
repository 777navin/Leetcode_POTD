/*
=========================================================
Date        : 29-10-2026
Problem Name: Palindromic Path Queries in a Tree
Platform    : LeetCode
Difficulty  : Hard
Tags        : Tree, Heavy-Light Decomposition, Segment Tree,
              Bit Manipulation, DFS

Problem Summary:
- Given a tree where each node contains a lowercase letter.
- Updates change a node's character.
- Path queries check whether the path characters can form
  a palindrome after rearrangement.

Key Observation:
- A string can form a palindrome if at most one character
  has an odd frequency.
- Represent character frequencies using a 26-bit XOR mask.
=========================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
APPROACH 1: BRUTE FORCE

- Intuition:
  Traverse the path between the two queried nodes.

- Approach:
  Find the path and count the frequency of every character.

- Why it Works:
  The path's character frequencies determine palindrome validity.

- Time Complexity (TC): O(n) per query.
- Space Complexity (SC): O(n).

APPROACH 2: OPTIMIZED

- Intuition:
  Store each character as a single bit in a 26-bit mask.

- Approach:
  Use Heavy-Light Decomposition (HLD) to split a tree path
  into O(log n) chain segments. Query each segment using a
  segment tree that maintains XOR masks.

- Why it Works:
  XOR combines character parities. A path forms a palindrome
  exactly when its combined mask contains at most one set bit.

- Time Complexity (TC): O(log^2 n) per query.
- Space Complexity (SC): O(n).

FINAL APPROACH:
- HLD reduces a tree path to O(log n) contiguous segments.
- The segment tree supports point updates and range XOR queries.
- This avoids repeatedly traversing the tree for each query.
- Iterative tree preprocessing avoids deep recursive DFS calls.
*/

class Solution {
private:
    int n;
    vector<vector<int>> adj;

    vector<int> parent;
    vector<int> depth;
    vector<int> subtreeSize;
    vector<int> heavy;
    vector<int> head;
    vector<int> position;

    int timer = 0;

    // Segment tree storing XOR masks.
    vector<int> segTree;

    int charMask(char c) {
        return 1 << (c - 'a');
    }

    void buildSegmentTree(const vector<int>& values) {
        int size = 1;
        while (size < n) {
            size <<= 1;
        }

        segTree.assign(2 * size, 0);

        for (int i = 0; i < n; ++i) {
            segTree[size + i] = values[i];
        }

        for (int i = size - 1; i >= 1; --i) {
            segTree[i] = segTree[i << 1] ^
                         segTree[i << 1 | 1];
        }
    }

    void update(int index, int value) {
        int size = static_cast<int>(segTree.size()) / 2;

        int p = size + index;
        segTree[p] = value;

        for (p >>= 1; p >= 1; p >>= 1) {
            segTree[p] = segTree[p << 1] ^
                         segTree[p << 1 | 1];
        }
    }

    // Returns the XOR mask over the inclusive range [left, right].
    int rangeQuery(int left, int right) {
        int size = static_cast<int>(segTree.size()) / 2;

        left += size;
        right += size + 1;

        int result = 0;

        while (left < right) {
            if (left & 1) {
                result ^= segTree[left++];
            }

            if (right & 1) {
                result ^= segTree[--right];
            }

            left >>= 1;
            right >>= 1;
        }

        return result;
    }

    // Builds parent, depth, traversal order, and subtree sizes.
    void buildTree(int root = 0) {
        vector<int> order;
        order.reserve(n);

        vector<int> stack;
        stack.reserve(n);
        stack.push_back(root);

        parent[root] = -1;

        while (!stack.empty()) {
            int u = stack.back();
            stack.pop_back();

            order.push_back(u);

            for (int v : adj[u]) {
                if (v == parent[u]) {
                    continue;
                }

                parent[v] = u;
                depth[v] = depth[u] + 1;
                stack.push_back(v);
            }
        }

        // Process nodes in reverse traversal order.
        for (int i = n - 1; i >= 0; --i) {
            int u = order[i];

            subtreeSize[u] = 1;
            heavy[u] = -1;

            int largestSubtree = 0;

            for (int v : adj[u]) {
                if (parent[v] != u) {
                    continue;
                }

                subtreeSize[u] += subtreeSize[v];

                if (subtreeSize[v] > largestSubtree) {
                    largestSubtree = subtreeSize[v];
                    heavy[u] = v;
                }
            }
        }
    }

    // Assigns each node a chain head and linearized position.
    void decompose(int root = 0) {
        vector<pair<int, int>> stack;
        stack.reserve(n);
        stack.push_back({root, root});

        timer = 0;

        while (!stack.empty()) {
            auto [start, chainHead] = stack.back();
            stack.pop_back();

            for (int u = start; u != -1; u = heavy[u]) {
                head[u] = chainHead;
                position[u] = timer++;

                // Light children begin separate heavy chains.
                for (int v : adj[u]) {
                    if (parent[v] == u && v != heavy[u]) {
                        stack.push_back({v, v});
                    }
                }
            }
        }
    }

    // XOR mask of all characters on the inclusive path u -> v.
    int pathQuery(int u, int v) {
        int mask = 0;

        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]]) {
                swap(u, v);
            }

            mask ^= rangeQuery(position[head[u]], position[u]);
            u = parent[head[u]];
        }

        if (depth[u] > depth[v]) {
            swap(u, v);
        }

        mask ^= rangeQuery(position[u], position[v]);

        return mask;
    }

public:
    vector<bool> palindromePath(
        int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries
    ) {
        this->n = n;
        adj.assign(n, {});

        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        parent.assign(n, -1);
        depth.assign(n, 0);
        subtreeSize.assign(n, 0);
        heavy.assign(n, -1);
        head.assign(n, 0);
        position.assign(n, 0);

        buildTree();
        decompose();

        vector<int> values(n, 0);

        for (int u = 0; u < n; ++u) {
            values[position[u]] = charMask(s[u]);
        }

        buildSegmentTree(values);

        vector<bool> answer;
        answer.reserve(queries.size());

        for (const string& q : queries) {
            stringstream ss(q);

            string operation;
            ss >> operation;

            if (operation == "update") {
                int u;
                char c;

                ss >> u >> c;

                s[u] = c;
                update(position[u], charMask(c));
            } else if (operation == "query") {
                int u, v;
                ss >> u >> v;

                int mask = pathQuery(u, v);

                // A palindrome permits at most one odd frequency.
                bool canFormPalindrome =
                    (mask & (mask - 1)) == 0;

                answer.push_back(canFormPalindrome);
            }
        }

        return answer;
    }
};

/*
=========================================================
Complexity:
- Preprocessing: O(n)
- Each update:   O(log n)
- Each query:    O(log^2 n)
- Total space:   O(n)

Filename:
29-10-2026_LeetCode_Palindromic_Path_Queries_in_a_Tree.cpp
=========================================================
*/
