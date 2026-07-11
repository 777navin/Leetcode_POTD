/*
=========================================================
Date        : 11-07-2026
Problem Name: Count the Number of Complete Components
Platform    : LeetCode
Difficulty  : Medium
Tags        : Depth-First Search, Breadth-First Search, Union-Find, Graph Theory

Problem Summary:
Given an undirected graph with n vertices and an array of edges, find the number 
of complete connected components. A connected component is complete if there is an 
edge between every single pair of its vertices.

Key Observation:
A connected component with 'V' vertices is complete if and only if every vertex 
within that component has a degree exactly equal to V - 1, or equivalently, if the 
total number of unique edges in the component equals V * (V - 1) / 2.
=========================================================
*/

#include <vector>
#include <numeric>

using namespace std;

/*
---------------------------------------------------------
Approach 1: Depth-First Search (DFS) / Breadth-First Search (BFS)
---------------------------------------------------------
• Intuition:
  Traverse each unvisited connected component using DFS or BFS to collect all its 
  vertices. While traversing, count the number of nodes and their degrees.

• Approach:
  - Build an adjacency list and an array to keep track of each node's degree.
  - Iterate through all nodes from 0 to n-1. If a node is unvisited, start a DFS.
  - During the DFS, track the size of the component and verify if every node 
    in this component satisfies the condition: degree == component_size - 1.

• Why it Works:
  In a complete graph (clique) of size V, every node must connect to all other 
  V - 1 nodes. Checking this condition for all nodes in the component guarantees completeness.

• Time Complexity (TC) : O(V + E) - We visit every vertex and edge exactly once.
• Space Complexity (SC): O(V + E) - For the adjacency list and the visited tracking array.
*/

/*
---------------------------------------------------------
Approach 2: Disjoint Set Union (DSU) / Union-Find (Optimized)
---------------------------------------------------------
• Intuition:
  Use a DSU structure to group connected nodes together into components efficiently, 
  while simultaneously tracking the node count and edge count for each component root.

• Approach:
  - Initialize two tracking arrays of size n: `node_count` (filled with 1) and `edge_count` (filled with 0).
  - For each edge, find the absolute parents of both nodes. Union them together and increment the edge count.
  - Iterate over all unique component roots, checking if `edge_count[root] == node_count[root] * (node_count[root] - 1) / 2`.

• Why it Works:
  The DSU groups vertices into independent sets. Since the total structural edges of a complete 
  graph are mathematically fixed at V * (V - 1) / 2, comparing the tracked edges directly determines completeness.

• Time Complexity (TC) : O(V + E * alpha(V)) - Nearly linear, where alpha is the Inverse Ackermann function.
• Space Complexity (SC): O(V) - Requires parent, node count, and edge count arrays.
*/

/*
=========================================================
FINAL APPROACH CHOICE
=========================================================
Approach 2 (DSU) is chosen because it avoids explicit graph reconstruction via adjacency 
lists, reducing structural overhead. It processes edges iteratively on the fly and utilizes 
the pure mathematical property of complete graphs, making it highly elegant and performant 
within a single pass over the edge list.
*/

class Solution {
public:
    // Helper function to find the absolute root of a node with path compression
    int findParent(int node, vector<int>& parent) {
        if (node == parent[node])
            return node;
        return parent[node] = findParent(parent[node], parent);
    }

    // Helper function to union two sets
    void unionNodes(int u, int v, vector<int>& parent, vector<int>& node_count, vector<int>& edge_count) {
        int root_u = findParent(u, parent);
        int root_v = findParent(v, parent);

        // Even if they are already in the same component, this edge belongs to that component
        if (root_u == root_v) {
            edge_count[root_u]++;
            return;
        }

        // Union by size/counts to the smaller component root
        if (node_count[root_u] < node_count[root_v]) {
            swap(root_u, root_v);
        }

        parent[root_v] = root_u;
        node_count[root_u] += node_count[root_v];
        edge_count[root_u] += edge_count[root_v] + 1; // merge existing edges and add the current edge
    }

    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        vector<int> parent(n);
        vector<int> node_count(n, 1);
        vector<int> edge_count(n, 0);

        // Initialize each node as its own parent
        iota(parent.begin(), parent.end(), 0);

        // Process all edges to build components
        for (const auto& edge : edges) {
            unionNodes(edge[0], edge[1], parent, node_count, edge_count);
        }

        int complete_components = 0;

        // Verify validity for the root of each component
        for (int i = 0; i < n; ++i) {
            if (parent[i] == i) {
                long long V = node_count[i];
                long long expected_edges = (V * (V - 1)) / 2;
                
                if (edge_count[i] == expected_edges) {
                    complete_components++;
                }
            }
        }

        return complete_components;
    }
};
