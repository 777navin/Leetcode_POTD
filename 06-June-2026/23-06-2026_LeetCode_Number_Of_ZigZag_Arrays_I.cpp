/*
Date: 23-06-2026
Problem Name: Number of ZigZag Arrays I
Platform: LeetCode
Difficulty: Hard
Tags: Dynamic Programming, Prefix Sum

Problem Summary:
Given length `n` and a range `[l, r]`, construct an array where no two adjacent elements are equal, and no three consecutive elements form a strictly increasing or decreasing sequence. Find the total number of valid arrays modulo 10^9 + 7. The requirement that no three consecutive elements increase or decrease strictly essentially forces the array to strictly alternate directions (ZigZag: UP-DOWN-UP-DOWN...).

Methods to Solve:
1. Brute Force (Recursion with Memoization)
2. Better Approach (2D DP)
3. Optimal Approach (Space-Optimized DP with Prefix/Suffix Sums)

For EACH method include:

--- Method 1: Brute Force (Recursion + Memoization) ---
- Intuition: At each step, we must keep track of the current element's value and the required direction for the next move (UP or DOWN) to maintain the ZigZag property.
- Approach: Use a recursive function `solve(idx, last_val, req_dir)` that tries all valid values for the current index and accumulates the possibilities. Memoize the states.
- Dry Run: For n=3, range [1, 3], if first element is 2 and we go UP to 3, the next required direction becomes DOWN, so we can pick 1 or 2.
- Time Complexity: O(n * m^2), where m = (r - l + 1). At each state, we loop through up to m values.
- Space Complexity: O(n * m) for the recursion stack and memoization table.
- Why better than previous method: Prevents exponential time complexity of pure recursion.
- When to use: When n and m are very small (e.g., <= 100).

--- Method 2: Better Approach (Tabulation DP) ---
- Intuition: Convert the recursive memoization into a bottom-up DP. Let `dp[i][dir][v]` be the count of prefixes of length i ending in value v, with the next required move being `dir` (0 for down, 1 for up).
- Approach: For each layer `i`, to calculate `dp[i][0][y]` (next move DOWN), we iterate through `x < y` and sum `dp[i-1][1][x]`.
- Dry Run: To end at 3 with next move DOWN, previous move must have been UP from 1 or 2.
- Time Complexity: O(n * m^2) due to the inner loop calculating transitions.
- Space Complexity: O(n * m) for the 3D DP table.
- Why better than previous method: Eliminates recursion overhead.
- When to use: If memory constraints allow O(n * m) space.

--- Method 3: Optimal Approach (DP with Prefix/Suffix Sums) ---
- Intuition: Notice that in Method 2, the inner loops are just calculating prefix sums (for x < y) or suffix sums (for x > y). We can precalculate these sums in O(m) time per layer.
- Approach: Maintain only the DP states for the previous length. Use prefix sums to update the `next_down` array and suffix sums to update the `next_up` array.
- Dry Run: Instead of looping `x` from 1 to `y-1` to find sums of `dp_up[x]`, maintain a running `pref` sum as `y` increases.
- Time Complexity: O(n * m). Each layer takes exactly O(m) operations.
- Space Complexity: O(m). We only need two arrays of size m for the current and next DP states.
- Why better than previous method: Drastically reduces time complexity from O(n * m^2) to O(n * m) and space from O(n * m) to O(m).
- When to use: Required for constraints n, m <= 2000 to pass within time limits.

Comparison Table:
Method         | TC         | SC       | Best Use Case
---------------|------------|----------|---------------------------
Memoization    | O(n * m^2) | O(n * m) | Small inputs
Tabulation DP  | O(n * m^2) | O(n * m) | Moderate inputs
Optimal DP     | O(n * m)   | O(m)     | Large constraints (n, m <= 2000)

Final Recommended Solution: Method 3 (Optimal Approach)
*/

#include <vector>

using namespace std;

class Solution {
public:
    // Method 1 & 2 concepts are optimized directly into Method 3 below for LeetCode constraints
    int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;
        
        // Edge case: sequence of length 1 has no adjacent constraints
        if (n == 1) return m % 1000000007;

        long long MOD = 1e9 + 7;

        // dp_down[y] stores the count of valid sequences ending at value y, 
        // where the NEXT required move is DOWN.
        vector<long long> dp_down(m + 1, 1);
        
        // dp_up[y] stores the count of valid sequences ending at value y,
        // where the NEXT required move is UP.
        vector<long long> dp_up(m + 1, 1);

        for (int i = 2; i <= n; i++) {
            vector<long long> next_down(m + 1, 0);
            vector<long long> next_up(m + 1, 0);

            // 1. Compute next_down using a running prefix sum of dp_up
            // If next move is DOWN, current transition was UP, meaning x < y
            long long pref = 0;
            for (int y = 1; y <= m; y++) {
                next_down[y] = pref;
                pref = (pref + dp_up[y]) % MOD;
            }

            // 2. Compute next_up using a running suffix sum of dp_down
            // If next move is UP, current transition was DOWN, meaning x > y
            long long suff = 0;
            for (int y = m; y >= 1; y--) {
                next_up[y] = suff;
                suff = (suff + dp_down[y]) % MOD;
            }

            dp_down = next_down;
            dp_up = next_up;
        }

        // Sum up all valid arrays ending at any value, going in either direction next
        long long total = 0;
        for (int y = 1; y <= m; y++) {
            total = (total + dp_down[y]) % MOD;
            total = (total + dp_up[y]) % MOD;
        }

        return total;
    }
};
