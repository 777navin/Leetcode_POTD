/*
Date: 12-06-2026
Problem Name: Number of Ways to Assign Edge Weights II
Platform: LeetCode
Difficulty: Hard
Tags: Dynamic Programming, Tree, Lowest Common Ancestor (LCA), Math, Bit Manipulation

Problem Summary:
Given an undirected tree rooted at 1 with n nodes, initially all edges have weight 0. 
We need to assign each edge a weight of 1 or 2. For given queries [u, v], 
find the number of ways to assign weights to edges on the path between u and v 
such that the total cost of the path is odd.

Methods to Solve:
1. Optimal Approach (Dynamic Programming + LCA)

For Optimal Approach:
- Intuition: 
  A path consists of k edges. Let $x$ be the number of edges assigned weight 1, 
  and $y$ be the number of edges assigned weight 2.
  Total edges in path $k = x + y$.
  Total cost = $1*x + 2*y = x + 2y$.
  The cost is odd if $x + 2y$ is odd. Since $2y$ is always even, $x$ must be odd.
  The number of ways to choose $x$ edges out of $k$ to have weight 1 (odd) 
  is the sum of combinations $\binom{k}{x}$ for all odd $x$.
  By binomial theorem properties, the sum of $\binom{k}{x}$ for odd $x$ is $2^{k-1}$ for $k \ge 1$.
- Approach:
  1. Find the distance $k$ (number of edges) between u and v using LCA: 
     $dist(u, v) = depth[u] + depth[v] - 2 * depth[LCA(u, v)]$.
  2. If $k == 0$, the cost is 0 (even), so 0 ways.
  3. If $k > 0$, the number of ways is $2^{k-1} \pmod{10^9 + 7}$.
- Time Complexity: $O(N + Q \log N)$ where $N$ is nodes and $Q$ is queries.
- Space Complexity: $O(N \log N)$ for LCA binary lifting table.

Comparison Table:
Method | TC | SC | Best Use Case
--- | --- | --- | ---
Optimal | O(N log N) | O(N log N) | Large constraints (N, Q <= 10^5)

Final Recommended Solution:
Binary lifting for LCA to calculate path length efficiently.
*/

#include <vector>
#include <cmath>

using namespace std;

class Solution {
    int n;
    vector<vector<int>> adj;
    vector<vector<int>> up;
    vector<int> depth;
    int LOG;

    void dfs(int u, int p, int d) {
        depth[u] = d;
        up[u][0] = p;
        for (int i = 1; i <= LOG; i++) {
            up[u][i] = up[up[u][i - 1]][i - 1];
        }
        for (int v : adj[u]) {
            if (v != p) dfs(v, u, d + 1);
        }
    }

    int get_lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        for (int i = LOG; i >= 0; i--) {
            if (depth[u] - (1 << i) >= depth[v]) u = up[u][i];
        }
        if (u == v) return u;
        for (int i = LOG; i >= 0; i--) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }
        return up[u][0];
    }

    long long power(long long base, long long exp) {
        long long res = 1;
        base %= 1000000007;
        while (exp > 0) {
            if (exp % 2 == 1) res = (res * base) % 1000000007;
            base = (base * base) % 1000000007;
            exp /= 2;
        }
        return res;
    }

public:
    vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        int n = edges.size() + 1;
        this->n = n;
        adj.resize(n + 1);
        for (auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        LOG = ceil(log2(n));
        up.assign(n + 1, vector<int>(LOG + 1));
        depth.assign(n + 1, 0);

        dfs(1, 1, 0);

        vector<int> results;
        for (auto& q : queries) {
            int u = q[0], v = q[1];
            if (u == v) {
                results.push_back(0);
                continue;
            }
            int lca = get_lca(u, v);
            int dist = depth[u] + depth[v] - 2 * depth[lca];
            results.push_back(power(2, dist - 1));
        }
        return results;
    }
};
