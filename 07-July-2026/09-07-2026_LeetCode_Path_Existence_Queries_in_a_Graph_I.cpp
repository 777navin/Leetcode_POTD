/*
=========================================================
Date        : 09-07-2026
Problem Name: Path Existence Queries in a Graph I
Platform    : LeetCode
Difficulty  : Medium
Tags        : Array, Graph Theory, Greedy

Problem Summary:
Given an array `nums` sorted in non-decreasing order, an undirected edge exists 
between indices i and j if |nums[i] - nums[j]| <= maxDiff. 
Determine if a path exists between queried pairs [u, v].

Key Observation:
Since `nums` is sorted, if |nums[i] - nums[i+1]| <= maxDiff, these nodes belong 
to the same connected component. We can treat contiguous segments of indices 
that satisfy this condition as a single component.
=========================================================
*/

/*
Approach:
1. Linear Scan / Component Labeling
   - Intuition: If |nums[i] - nums[i-1]| <= maxDiff, node i is connected to i-1. 
     We can group nodes into components where each consecutive pair satisfies the condition.
   - Approach: Create a component ID array. Iterate through `nums`; if the difference 
     between current and previous is > maxDiff, increment the component ID.
   - Why it Works: Because the array is sorted, the graph structure is effectively a set 
     of disjoint intervals. If two nodes have the same component ID, they are reachable.
   - Time Complexity (TC): O(n + q)
   - Space Complexity (SC): O(n)
*/

/*
Final Approach:
The linear scan is chosen because it is highly efficient (O(n)) and avoids the overhead 
of DSU or complex graph algorithms. By assigning each index a component ID based 
on the `maxDiff` constraint, we can answer each query in O(1) time by checking 
if `comp[u] == comp[v]`.
*/

class Solution {
public:
    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        // comp stores the component ID for each node index
        vector<int> comp(n, 0);
        
        // Assign component IDs
        // Nodes are in the same component if they are part of a sequence where 
        // every adjacent pair has a difference <= maxDiff
        for (int i = 1; i < n; ++i) {
            if (nums[i] - nums[i - 1] <= maxDiff) {
                comp[i] = comp[i - 1];
            } else {
                comp[i] = comp[i - 1] + 1;
            }
        }
        
        int q = queries.size();
        vector<bool> answer(q);
        
        // Process queries: if both nodes have the same ID, a path exists
        for (int i = 0; i < q; ++i) {
            answer[i] = (comp[queries[i][0]] == comp[queries[i][1]]);
        }
        
        return answer;
    }
};
