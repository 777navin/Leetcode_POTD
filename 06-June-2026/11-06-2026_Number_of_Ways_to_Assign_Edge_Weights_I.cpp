/*
Date: 11-06-2026
Problem Name: Number of Ways to Assign Edge Weights I
Platform: LeetCode
Difficulty: Medium
Tags: Math, Tree, Depth-First Search

Problem Summary:
Given an undirected tree rooted at 1, we must assign weights of 1 or 2 to all edges.
For a node x at the maximum depth, we need to find the number of ways to assign 
weights to edges on the path from 1 to x such that the total sum of weights is odd.
Return the result modulo 10^9 + 7.

Methods to Solve:
1. Mathematical Derivation (Optimal)

For the path to be odd, there must be an odd number of edges with weight 1.
If the path has 'L' edges (i.e., the depth of node x), we need to choose an 
odd number of positions for weight 1.
The total number of ways to choose any subset of edges to be weight 1 is 2^L.
It is a known combinatorial property that the number of ways to choose an 
odd number of items from a set of size L is 2^(L-1).

Intuition:
- Since weight 2 is even, it does not change the parity of the sum.
- Only weight 1 changes the parity.
- An odd sum is achieved if and only if there are an odd number of '1's in the path.
- In a sequence of length L, the number of subsequences with an odd number of 1s is 2^(L-1).

Time Complexity: O(N) to find the maximum depth using DFS.
Space Complexity: O(H) where H is the height of the tree (recursion stack).

Comparison Table:
Method | TC | SC | Best Use Case
-------|----|----|--------------
Math   | O(N) | O(H) | Optimal for parity-based path counting

Final Recommended Solution: Mathematical approach using modular exponentiation.
*/

#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
private:
    int maxDepth = 0;
    const int MOD = 1e9 + 7;

    // Helper to find the maximum depth of the tree
    void dfs(int u, int p, int depth, const vector<vector<int>>& adj) {
        maxDepth = max(maxDepth, depth);
        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u, depth + 1, adj);
            }
        }
    }

    // Modular exponentiation to calculate 2^(L-1) % MOD
    long long power(long long base, long long exp) {
        long long res = 1;
        base %= MOD;
        while (exp > 0) {
            if (exp % 2 == 1) res = (res * base) % MOD;
            base = (base * base) % MOD;
            exp /= 2;
        }
        return res;
    }

public:
    int assignEdgeWeights(vector<vector<int>>& edges) {
        int n = edges.size() + 1;
        vector<vector<int>> adj(n + 1);
        for (const auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        // 1. Calculate max depth of the tree
        dfs(1, -1, 0, adj);

        // 2. The path length L is the maxDepth
        // Number of ways = 2^(L-1)
        if (maxDepth == 0) return 0;
        return (int)power(2, maxDepth - 1);
    }
};
