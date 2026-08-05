/*
=========================================================
Date        : 05-08-2026
Problem Name: 3310. Remove Methods From Project
Platform    : LeetCode
Difficulty  : Medium
Tags        : Depth-First Search, Breadth-First Search, Graph Theory

Problem Summary:
Given a project with n methods, method k has a bug. Method k and any 
methods it invokes directly or indirectly are suspicious. We can only 
remove the suspicious group if no non-suspicious method calls them.

Key Observation:
This is a reachability problem on a directed graph. First, find all 
suspicious methods using a graph traversal (DFS/BFS) starting from k. 
Then, scan all edges to ensure no edge flows from a safe node to a 
suspicious node.
=========================================================
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH EXPLANATION
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

1. Graph Traversal (DFS)
   • Intuition: The invocations represent a directed graph. Finding all infected methods is equivalent to finding the reachable component from node `k`.
   • Approach:
     - Build an adjacency list `adj` from the given `invocations`.
     - Run a DFS starting from method `k` to mark all reachable methods in a boolean array `suspicious`.
     - Iterate over the `invocations` again. If any invocation goes from an unmarked (safe) method to a marked (suspicious) method, flag that removal is invalid.
     - Return the remaining safe methods if removal is valid, else return all methods.
   • Why it Works: DFS accurately marks all dependencies. A linear scan of the edges robustly verifies the "no outside invocation" constraint.
   • Time Complexity (TC): O(N + E), where N is the number of methods and E is the number of invocations. Constructing the graph and traversing it takes linear time.
   • Space Complexity (SC): O(N + E) for the adjacency list and O(N) for the visited/suspicious array.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
FINAL APPROACH
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
The Graph Traversal approach is chosen because it perfectly matches the 
reachability nature of the problem. It is the most optimal way to solve 
it and runs efficiently in linear time.
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void dfs(int u, vector<vector<int>>& adj, vector<bool>& suspicious) {
        suspicious[u] = true;
        for (int v : adj[u]) {
            if (!suspicious[v]) {
                dfs(v, adj, suspicious);
            }
        }
    }

    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        // Step 1: Build the directed graph
        vector<vector<int>> adj(n);
        for (const auto& edge : invocations) {
            adj[edge[0]].push_back(edge[1]);
        }

        // Step 2: Mark all suspicious methods using DFS from k
        vector<bool> suspicious(n, false);
        dfs(k, adj, suspicious);

        // Step 3: Check if any non-suspicious method calls a suspicious method
        bool canRemove = true;
        for (const auto& edge : invocations) {
            int u = edge[0];
            int v = edge[1];
            if (!suspicious[u] && suspicious[v]) {
                canRemove = false;
                break;
            }
        }

        // Step 4: Construct the final result array
        vector<int> result;
        if (canRemove) {
            for (int i = 0; i < n; ++i) {
                if (!suspicious[i]) {
                    result.push_back(i);
                }
            }
        } else {
            for (int i = 0; i < n; ++i) {
                result.push_back(i);
            }
        }

        return result;
    }
};

int main() {
    // Fast I/O for competitive programming environments
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution sol;
    
    // Test Case 1
    int n1 = 4, k1 = 1;
    vector<vector<int>> invocations1 = {{1, 2}, {0, 1}, {3, 2}};
    vector<int> res1 = sol.remainingMethods(n1, k1, invocations1);
    
    cout << "Remaining Methods (Test 1): ";
    for (int method : res1) {
        cout << method << " ";
    }
    cout << "\n";

    // Test Case 2
    int n2 = 5, k2 = 0;
    vector<vector<int>> invocations2 = {{1, 2}, {0, 2}, {0, 1}, {3, 4}};
    vector<int> res2 = sol.remainingMethods(n2, k2, invocations2);
    
    cout << "Remaining Methods (Test 2): ";
    for (int method : res2) {
        cout << method << " ";
    }
    cout << "\n";

    return 0;
}
