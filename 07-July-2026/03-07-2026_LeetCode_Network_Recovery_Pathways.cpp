PLATFORM DETECTED: LeetCodeC++/*
=========================================================
Date        : 03-07-2026
Problem Name: Network Recovery Pathways
Platform    : LeetCode
Difficulty  : Hard
Tags        : Array, Binary Search, Dynamic Programming, Graph Theory, Topological Sort, Shortest Path

Problem Summary:
Given a Directed Acyclic Graph (DAG) with edge costs, find a path from node 0 to node n-1. 
Only intermediate nodes that are "online" can be visited. The total cost of the path must be <= k.
The goal is to maximize the "score" (the minimum edge-cost on the chosen valid path).

Constraints:
- 2 <= n <= 5 * 10^4
- 0 <= m <= min(10^5, n * (n - 1) / 2)
- 0 <= cost_i <= 10^9
- 0 <= k <= 5 * 10^13
- Graph is a DAG.

Key Observation:
Since we want to maximize the minimum edge-cost, we can binary search for the answer. 
For a candidate answer 'mid', we ignore all edges with cost < mid. Since the graph is a DAG, 
we can use Dynamic Programming (DFS with memoization) to find the minimum total cost to reach 
n-1. If this cost is <= k, 'mid' is valid.
=========================================================
*/

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━STEP 3: INCLUDE EVERY POSSIBLE APPROACH━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━1. Binary Search + Dijkstra's AlgorithmIntuition: We need to maximize the bottleneck (minimum edge cost). We can guess this minimum cost using Binary Search. For a fixed guess mid, we must find if there exists a valid path using only edges $\ge$ mid that costs at most k. We can find the shortest path using Dijkstra's Algorithm.Idea: Filter edges dynamically and run standard shortest-path.Dry Run: Try mid = 5. Run Dijkstra ignoring edges $< 5$. If shortest path $\le k$, search higher. Else search lower.Why it works: Dijkstra guarantees the shortest path on graphs with non-negative weights.Time Complexity: $O(E \log V \cdot \log(\text{Max\_Cost}))$Space Complexity: $O(V + E)$Advantages: Conceptually straightforward if you are familiar with shortest paths.Disadvantages: Slower due to the $O(\log V)$ overhead of the priority queue. Doesn't exploit the DAG property.When to use: When the graph contains cycles.Why next approach is better: The graph is explicitly stated as a Directed Acyclic Graph (DAG). We can drop the priority queue and find the shortest path in linear time using DP.2. Binary Search + DP on DAG (Memoized DFS)Intuition: Because the graph is a DAG, we don't need a priority queue. We can just use Depth-First Search with Memoization (which is essentially DP) to compute the shortest path to $n-1$.Idea: Keep the binary search on the minimum edge weight. Inside the validation function check(mid), run a memoized DFS. Let memo[u] store the minimum cost to reach $n-1$ from $u$.Why it works: A DAG has a topological ordering. Memoization natively respects this ordering, computing the shortest path from $u$ to $n-1$ in $O(V+E)$ time.Time Complexity: $O((V + E) \cdot \log(\text{Max\_Cost}))$. Maximum cost is $10^9$, so the binary search runs ~30 times. $30 \times (50000 + 100000) \approx 4.5 \times 10^6$ operations, which easily runs in 1 second.Space Complexity: $O(V + E)$ for the adjacency list and recursion stack.Advantages: Extremely fast and optimal. Exploits all graph properties given in the problem.Disadvantages: Recursion limit issues in some languages (not an issue in C++).━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━STEP 4: COMPARISON TABLE━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━MethodIdeaTimeSpaceDifficultyRecommended1. Binary Search + DijkstraFilter edges & find shortest path with PQ$O(E \log V \cdot \log W)$$O(V + E)$MediumNo2. Binary Search + DPFilter edges & find shortest path via Memo DFS$O((V + E) \cdot \log W)$$O(V + E)$HardYes━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━STEP 5: FINAL RECOMMENDED APPROACH━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━Binary Search + DP on DAG (Memoized DFS) is the absolute best approach here. The problem strictly defines the graph as a Directed Acyclic Graph (DAG). Using Dijkstra introduces an unnecessary $O(\log V)$ factor per step of the binary search. By switching to DP, we strip away the priority queue overhead, optimizing the shortest path calculation from $O(E \log V)$ to $O(V + E)$. This guarantees the solution stays well within the strict time limits of LeetCode hard problems.━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━STEP 6 & 7: CODE GENERATION & QUALITY━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━C++#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    long long INF = 1e18; 
    int n;
    vector<vector<pair<int, long long>>> adj;

    // DP on DAG to find minimum cost path using edges with weight >= mid
    long long dfs(int u, int mid, const vector<bool>& online, vector<long long>& memo) {
        // Base case: Reached destination
        if (u == n - 1) return 0;
        
        // Return precomputed result (-1 denotes uninitialized)
        if (memo[u] != -1) return memo[u];

        long long min_cost = INF;
        
        // Traverse all outgoing edges
        for (const auto& edge : adj[u]) {
            int v = edge.first;
            long long weight = edge.second;

            // Ignore edges that drop our bottleneck score below 'mid'
            if (weight < mid) continue;
            
            // Ignore offline intermediate nodes
            if (v != n - 1 && !online[v]) continue;

            long long next_cost = dfs(v, mid, online, memo);
            
            // If a valid path exists from v, update min_cost
            if (next_cost != INF) {
                min_cost = min(min_cost, next_cost + weight);
            }
        }
        
        return memo[u] = min_cost;
    }

    // Validation function for Binary Search
    bool check(int mid, const vector<bool>& online, long long k) {
        vector<long long> memo(n, -1);
        long long total_cost = dfs(0, mid, online, memo);
        return total_cost <= k;
    }

public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        n = online.size();
        adj.resize(n);

        long long max_weight = 0;
        
        // Build Adjacency List
        for (const auto& e : edges) {
            int u = e[0], v = e[1];
            long long w = e[2];
            adj[u].push_back({v, w});
            max_weight = max(max_weight, w);
        }

        // Binary Search on the minimum edge cost
        long long low = 0, high = max_weight;
        int ans = -1;

        while (low <= high) {
            long long mid = low + (high - low) / 2;
            
            if (check(mid, online, k)) {
                ans = mid;        // 'mid' is possible, store it
                low = mid + 1;    // Try to find a larger minimum edge cost
            } else {
                high = mid - 1;   // 'mid' is too large, reduce it
            }
        }

        return ans;
    }
};
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━STEP 10: OUTPUT THE FILE NAME━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
