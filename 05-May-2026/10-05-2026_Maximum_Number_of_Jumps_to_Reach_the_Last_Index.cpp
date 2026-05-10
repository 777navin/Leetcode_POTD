/*
Date: 10-05-2026
Problem Name: Maximum Number of Jumps to Reach the Last Index
Platform: LeetCode
Difficulty: Medium
Tags: Array, Dynamic Programming

Problem Summary:
You are given a 0-indexed integer array `nums` of size `n` and an integer `target`.
You start at index 0. You can jump from index `i` to index `j` if $0 \le i < j < n$ 
and $-target \le nums[j] - nums[i] \le target$. 
The goal is to return the maximum number of jumps to reach the last index (`n - 1`). 
If it's impossible to reach the last index, return -1.

Methods to Solve:
1. Brute Force (Simple Recursion)
2. Better Approach (Recursion with Memoization)
3. Optimal Approach (Bottom-Up Dynamic Programming)

---------------------------------------------------------
Method 1: Brute Force (Simple Recursion)
---------------------------------------------------------
Intuition:
At every index `i`, we can try jumping to all possible future indices `j` that satisfy 
the condition. We explore all valid paths to the end and find the one with the maximum steps.

Approach:
Write a recursive function that takes the current index.
Loop through all possible next indices. If the jump condition is met, make a recursive 
call. Add 1 to the result of the recursive call. Keep track of the maximum jumps.

Dry Run (small example):
nums = [1,3,6,4], target = 3
- Start at index 0 (val 1). Valid jumps to: index 1 (val 3, diff 2).
- From index 1, valid jump to: index 3 (val 4, diff 1).
- Reached end. Total jumps = 2.

Time Complexity: $O(2^n)$ in the worst case, as we might explore all subsets of indices.
Space Complexity: $O(n)$ for the recursion stack.
Why better than previous method: N/A (Baseline).
When to use: Only for very small constraints (e.g., $n \le 20$).

---------------------------------------------------------
Method 2: Better Approach (Recursion with Memoization)
---------------------------------------------------------
Intuition:
The brute force approach recalculates the maximum jumps from the same index multiple times. 
We can cache these results.

Approach:
Initialize a `memo` array of size `n` with -1.
In the recursive function, before computing, check if `memo[index]` is already calculated.
If yes, return it. Otherwise, compute the max jumps, store it in `memo[index]`, and return.

Time Complexity: $O(n^2)$. We calculate the answer for each of the $n$ states exactly once, 
and computing each state takes an $O(n)$ loop.
Space Complexity: $O(n)$ for the recursion stack + $O(n)$ for the memoization array.
Why better than previous method: Drastically reduces time complexity by eliminating redundant calculations.
When to use: When you prefer a top-down logical flow and constraints allow $O(n^2)$ time.

---------------------------------------------------------
Method 3: Optimal Approach (Bottom-Up Dynamic Programming)
---------------------------------------------------------
Intuition:
We can build the solution iteratively from the beginning to the end. For any index `i`, 
the maximum jumps to reach it depend on the maximum jumps to reach all valid previous indices `j`.

Approach:
1. Create a `dp` array of size `n`, initialized to -1 (indicating unreachable).
2. Set `dp[0] = 0`, since we start at index 0 with 0 jumps.
3. Use a nested loop: 
   - Outer loop `i` from 1 to `n-1` (current position to calculate).
   - Inner loop `j` from 0 to `i-1` (previous positions to jump from).
4. If `dp[j] != -1` (meaning index `j` is reachable) and the absolute difference 
   between `nums[i]` and `nums[j]` is $\le target$, update `dp[i] = max(dp[i], dp[j] + 1)`.
5. Return `dp[n-1]`.

Time Complexity: $O(n^2)$. Two nested loops iterating up to $n$.
Space Complexity: $O(n)$. We only need a 1D array of size $n$ to store states.
Why better than previous method: Avoids recursion stack overhead entirely. Cleaner and iterative.
When to use: This is the optimal solution for this problem given the constraint $n \le 1000$.

---------------------------------------------------------
Comparison Table:
Method       | TC       | SC     | Best Use Case
---------------------------------------------------------
Brute Force  | $O(2^n)$ | $O(n)$ | Never (TLE for $n > 20$)
Memoization  | $O(n^2)$ | $O(n)$ | Good for top-down thinkers
Bottom-Up DP | $O(n^2)$ | $O(n)$ | Best practical performance
---------------------------------------------------------

Final Recommended Solution: Optimal Approach (Bottom-Up Dynamic Programming)
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maximumJumps(vector<int>& nums, int target) {
        int n = nums.size();
        
        // dp[i] stores the max jumps to reach index i. 
        // Initialized to -1 to represent unreachable states.
        vector<int> dp(n, -1);
        
        // Base case: 0 jumps to reach the starting index
        dp[0] = 0;
        
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                // If index j is reachable, check if we can jump from j to i
                // Casting to long long prevents potential overflow when calculating the difference
                if (dp[j] != -1 && abs((long long)nums[i] - nums[j]) <= target) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        
        return dp[n - 1];
    }
};

// Driver code to allow immediate local testing
int main() {
    Solution sol;
    
    // Test Case 1
    vector<int> nums1 = {1, 3, 6, 4, 1, 2};
    int target1 = 2;
    cout << "Test Case 1 Output: " << sol.maximumJumps(nums1, target1) << "\n"; 
    // Expected: 3

    // Test Case 2
    vector<int> nums2 = {1, 3, 6, 4, 1, 2};
    int target2 = 3;
    cout << "Test Case 2 Output: " << sol.maximumJumps(nums2, target2) << "\n"; 
    // Expected: 5

    // Test Case 3
    vector<int> nums3 = {1, 3, 6, 4, 1, 2};
    int target3 = 0;
    cout << "Test Case 3 Output: " << sol.maximumJumps(nums3, target3) << "\n"; 
    // Expected: -1

    return 0;
}
