
/*
=========================================================
Date        : 30-10-2026
Problem Name: Shortest Path With At Most K Consecutive
              Identical Characters
Platform    : LeetCode
Difficulty  : Medium
Tags        : Graph, Dijkstra, Priority Queue, Shortest Path

Problem Summary:
- Given a directed weighted graph and a character for each node.
- Find the minimum cost path from node 0 to node n-1.
- The path cannot contain more than k consecutive identical
  characters in its sequence of node labels.
- Return -1 if no valid path exists.

Key Observation:
- The current node alone is insufficient to determine a state.
- We must also track the consecutive count of its character.
=========================================================

APPROACH 1: BRUTE FORCE (NOT PRACTICAL)

- Intuition:
  Explore every possible path from node 0 to node n-1.

- Approach:
  Use DFS while maintaining the current character run length.
  Reject paths whenever the run length exceeds k.

- Why it Works:
  Every valid path is explored and the minimum cost is selected.

- Time Complexity (TC):
  Exponential in the worst case due to repeated path exploration.

- Space Complexity (SC):
  O(V) recursion depth, excluding graph storage.


APPROACH 2: OPTIMIZED - DIJKSTRA ON EXPANDED STATES

- Intuition:
  A state consists of (node, consecutive character count).

- Approach:
  Maintain dist[node][count] as the minimum cost.
  Use a min-priority queue to process the cheapest state.
  Update the count when moving to the next node:
    Same character     -> count + 1
    Different character -> 1
  Ignore transitions where count exceeds k.

- Why it Works:
  Every state contains all information needed to determine
  whether a future transition is valid.
  Dijkstra finds the minimum cost for every reachable state.

- Time Complexity (TC):
  O((V*K + E*K) * log(V*K))

- Space Complexity (SC):
  O(V*K + E)


FINAL APPROACH:
- Choose Dijkstra on expanded states.
- It avoids repeatedly exploring expensive paths.
- At most V*K states and E*K transitions are processed.
- It efficiently handles the given constraints.

=========================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges,
                     string labels, int k) {

        // Build directed weighted graph.
        vector<vector<pair<int, int>>> adj(n);

        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];

            adj[u].push_back({v, w});
        }

        const long long INF = LLONG_MAX / 4;

        // dist[node][count] = minimum cost to reach this state.
        vector<vector<long long>> dist(
            n, vector<long long>(k + 1, INF)
        );

        // {cost, node, consecutive character count}
        using State = tuple<long long, int, int>;

        priority_queue<
            State,
            vector<State>,
            greater<State>
        > pq;

        // Starting node contributes its own character.
        dist[0][1] = 0;
        pq.push({0, 0, 1});

        while (!pq.empty()) {
            auto [cost, u, count] = pq.top();
            pq.pop();

            // Ignore outdated priority queue entries.
            if (cost != dist[u][count]) {
                continue;
            }

            // First valid popped destination state is optimal.
            if (u == n - 1) {
                return static_cast<int>(cost);
            }

            for (auto [v, weight] : adj[u]) {

                int nextCount;

                if (labels[u] == labels[v]) {
                    nextCount = count + 1;
                } else {
                    nextCount = 1;
                }

                // More than k consecutive identical characters.
                if (nextCount > k) {
                    continue;
                }

                long long newCost = cost + weight;

                if (newCost < dist[v][nextCount]) {
                    dist[v][nextCount] = newCost;

                    pq.push({
                        newCost,
                        v,
                        nextCount
                    });
                }
            }
        }

        return -1;
    }
};

/*
=========================================================
Complexity:
V = Number of nodes
E = Number of directed edges
K = Maximum allowed consecutive identical characters

Time  : O((V*K + E*K) * log(V*K))
Space : O(V*K + E)

Note:
The graph is directed. Do not add reverse edges.
The starting node is included in the consecutive count.
=========================================================
*/
