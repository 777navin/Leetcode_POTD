/*
=========================================================
Date        : 17-07-2026
Problem Name: 3312. Sorted GCD Pair Queries
Platform    : LeetCode
Difficulty  : Hard
Tags        : Array, Hash Table, Math, Binary Search, Combinatorics, Counting, Number Theory, Prefix Sum

Problem Summary:
Given an array `nums` of length `n`, we calculate the GCD of all possible pairs `(nums[i], nums[j])` 
where `0 <= i < j < n`. These values are stored in an array `gcdPairs` and sorted in ascending order. 
For each index query in `queries`, we need to return the value at `gcdPairs[queries[i]]`.

Key Observation:
Instead of generating all $O(n^2)$ pairs explicitly, which causes TLE/MLE, we count how many pairs 
have a specific GCD value $g$ using frequency counts and a reverse inclusion-exclusion technique 
from the maximum possible element down to 1.
=========================================================
*/

#include <vector>
#include <algorithm>

using namespace std;

/*
---------------------------------------------------------
Approach 1: Optimized Counting with Inclusion-Exclusion & Binary Search
---------------------------------------------------------
• Intuition:
  The maximum possible value in `nums` is $M = 50000$. Instead of computing GCDs for all pairs, 
  we can compute how many pairs have a GCD that is a multiple of $g$, and then filter out the 
  multiples to find the exact number of pairs with GCD equal to $g$.

• Approach:
  1. Count the frequencies of each number in `nums` and calculate a prefix-like frequency array 
     to determine how many numbers in `nums` are multiples of any given number $i$.
  2. For each $i$ from $M$ down to 1, the total pairs whose GCD is a multiple of $i$ is given by 
     $cnt = \text{multiples}[i]$, which yields $\frac{cnt \times (cnt - 1)}{2}$ total pairs.
  3. Deduct pairs that have a GCD of $2i, 3i, \dots$ to get the exact count of pairs with $\text{GCD} = i$.
  4. Build a prefix sum of these exact counts to construct a sorted range map of pair counts.
  5. For each query, use binary search (`upper_bound`) to find which GCD value covers the requested index.

• Why it Works:
  Every pair with $\text{GCD} = i$ is counted in the total pairs formed by multiples of $i$. By processing 
  from largest to smallest value, any pair with a larger common divisor has already been correctly 
  isolated, allowing seamless inclusion-exclusion via harmonic-like iterations.

• Time Complexity (TC):
  - Frequency counting and multiple counting: $O(N + M \log M)$ where $M = \max(\text{nums})$.
  - Inclusion-Exclusion sieve: $O(M \log M)$.
  - Prefix Sum & Queries: $O(M + Q \log M)$.
  - Total TC: $O(N + (M + Q) \log M)$, which comfortably runs within the time limit.

• Space Complexity (SC):
  - Count arrays and prefix sum arrays up to size $M$: $O(M)$.
  - Total SC: $O(M)$ auxiliary space.
---------------------------------------------------------
*/

// Final Approach Selection:
// This approach is chosen because generating all $O(N^2)$ pairs takes $O(10^{10})$ operations, 
// causing Time and Memory Limit Exceeded errors. By transitioning the problem space from the 
// size of the array $N$ to the maximum value constraints $M$, it processes the queries optimally 
// within linear-logarithmic time constraints.

class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int max_val = *max_element(nums.begin(), nums.end());
        
        // Count frequencies of each number
        vector<long long> count(max_val + 1, 0);
        for (int num : nums) {
            count[num]++;
        }
        
        // Count how many elements are multiples of each number i
        vector<long long> multiples(max_val + 1, 0);
        for (int i = 1; i <= max_val; ++i) {
            for (int j = i; j <= max_val; j += i) {
                multiples[i] += count[j];
            }
        }
        
        // gcd_pairs[i] will store the exact number of pairs with GCD equal to i
        vector<long long> gcd_pairs(max_val + 1, 0);
        for (int i = max_val; i >= 1; --i) {
            long long total_multiples = multiples[i];
            long long total_pairs = total_multiples * (total_multiples - 1) / 2;
            
            // Inclusion-Exclusion: subtract pairs that have a GCD strictly greater than i (multiples of i)
            for (int j = 2 * i; j <= max_val; j += i) {
                total_pairs -= gcd_pairs[j];
            }
            gcd_pairs[i] = total_pairs;
        }
        
        // Compute prefix sums of the pair counts to enable binary search
        vector<long long> prefix_sums(max_val + 1, 0);
        for (int i = 1; i <= max_val; ++i) {
            prefix_sums[i] = prefix_sums[i - 1] + gcd_pairs[i];
        }
        
        // Process each query using binary search
        vector<int> answer;
        answer.reserve(queries.size());
        for (long long q : queries) {
            // Find the first GCD value whose prefix sum is strictly greater than the 0-indexed query q
            auto it = upper_bound(prefix_sums.begin(), prefix_sums.end(), q);
            int gcd_val = distance(prefix_sums.begin(), it);
            answer.push_back(gcd_val);
        }
        
        return answer;
    }
};
