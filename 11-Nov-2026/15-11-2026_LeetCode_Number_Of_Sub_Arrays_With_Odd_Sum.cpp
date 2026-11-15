
/*
=========================================================
Date        : 15-11-2026
Problem Name: Number of Sub-arrays With Odd Sum
Platform    : LeetCode
Difficulty  : Medium
Tags        : Array, Math, Prefix Sum, Dynamic Programming

Problem Summary:
- Given an integer array, count contiguous subarrays having odd sums.
- Return the answer modulo 1e9 + 7.

Key Observation:
- Odd + Even = Odd.
- Even + Even = Even.
- A subarray has an odd sum when its two prefix sums
  have different parities.
=========================================================

APPROACH 1: BRUTE FORCE

Intuition:
- Generate every possible contiguous subarray.

Approach:
- Fix a starting index and calculate sums for every ending index.
- Count subarrays whose sum is odd.

Why it Works:
- Every possible subarray is considered exactly once.

TC: O(N^2)
SC: O(1)

APPROACH 2: OPTIMIZED PREFIX SUM

Intuition:
- Use prefix sum parity instead of calculating complete sums.

Approach:
- Maintain counts of even and odd prefix sums.
- If current prefix is odd, add previous even prefixes.
- If current prefix is even, add previous odd prefixes.

Why it Works:
- Different prefix parities always produce an odd subarray sum.

TC: O(N)
SC: O(1)

FINAL APPROACH:
- Choose optimized prefix parity counting.
- It processes each element only once.
- It uses constant extra space and handles large answers
  using modulo 1e9 + 7.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        const int MOD = 1e9 + 7;

        long long even = 1;
        long long odd = 0;
        long long prefixSum = 0;
        long long ans = 0;

        for (int num : arr) {
            prefixSum += num;

            if (prefixSum % 2 == 0) {
                ans = (ans + odd) % MOD;
                even++;
            } else {
                ans = (ans + even) % MOD;
                odd++;
            }
        }

        return static_cast<int>(ans);
    }
};
