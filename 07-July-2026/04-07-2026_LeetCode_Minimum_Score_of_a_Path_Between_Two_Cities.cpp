/*
Date        : 04-07-2026
Problem Name: Minimum Score of a Path Between Two Cities
Platform    : LeetCode
Difficulty  : Medium
Tags        : Depth-First Search, Breadth-First Search, Union-Find, Graph Theory

Problem Summary:
Given n cities and bidirectional roads with specific distances, find the minimum
score of a path between city 1 and city n. The score of a path is the minimum
edge weight in that path.

Constraints:

2 <= n <= 10^5

1 <= roads.length <= 10^5

1 <= distance_i <= 10^4

Key Observation: Since we can visit edges and cities multiple times, any edge that is part of the same connected component as city 1 and city n can be included in the path. Therefore, the problem reduces to finding the minimum edge weight in the connected component containing nodes 1 and n.
*/

#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

/

Approaches:

Breadth-First Search (BFS) / Depth-First Search (DFS):

Intuition: Traverse the entire connected component containing node 1.

Idea: Start from node 1, visit all reachable nodes using BFS/DFS.

Keep track of the minimum edge weight encountered during this traversal.

Time Complexity: O(V + E), where V is cities and E is roads.

Space Complexity: O(V + E) to store the graph.

Union-Find (Disjoint Set Union):

Intuition: Group all connected cities into sets.

Idea: Process all edges to union the cities. Then, find the component

containing 1 and iterate over all edges to find the minimum weight

among those where both endpoints belong to that component.

Time Complexity: O(E * alpha(V)).

Space Complexity: O(V).

Comparison Table:

Method         | Idea              | Time     | Space    | Recommended

BFS/DFS        | Traversal         | O(V+E)   | O(V+E)   | Yes

Union-Find     | Component grouping| O(E*α(V))| O(V)     | Yes

Final Recommended Approach:

BFS/DFS is chosen here for its simplicity and efficiency in traversing

the component directly. Since we only care about edges in the component

connected to 1 (which must also include n, as guaranteed by the problem),

traversing from node 1 is sufficient.
*/

class Solution {
public:
int minScore(int n, vector<vector<int>>& roads) {
// Build the graph
vector<vector<pair<int, int>>> adj(n + 1);
for (const auto& road : roads) {
adj[road[0]].push_back({road[1], road[2]});
adj[road[1]].push_back({road[0], road[2]});
}

    int min_score = INT_MAX;
    vector<bool> visited(n + 1, false);
    queue<int> q;

    // BFS to traverse the connected component
    q.push(1);
    visited[1] = true;

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        for (auto& edge : adj[curr]) {
            int neighbor = edge.first;
            int weight = edge.second;

            // Update min score with the edge weight
            min_score = min(min_score, weight);

            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    return min_score;
}
};
