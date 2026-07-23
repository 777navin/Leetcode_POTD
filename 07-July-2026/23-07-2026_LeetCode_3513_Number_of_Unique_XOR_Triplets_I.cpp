/*
=========================================================
Date        : 23-07-2026
Problem Name: 3513. Number of Unique XOR Triplets I
Platform    : LeetCode
Difficulty  : Medium
Tags        : Array, Math, Bit Manipulation

Problem Summary:
Given an array `nums` of length `n` which is a permutation of numbers from 1 to `n`.
A XOR triplet is defined as nums[i] ^ nums[j] ^ nums[k] for i <= j <= k.
We need to find the count of unique XOR triplet values possible across all index triplets.

Key Observation:
For n >= 3, three numbers can combine via bit manipulation to generate all values in 
the range [0, 2^(MSB(n)+1) - 1], where MSB(n) is the most significant bit index of n.
Small cases (n = 1, 2) must be handled separately.
=========================================================
*/

#include <iostream>
#include <vector>

using namespace std;

/*
---------------------------------------------------------
1. Brute Force Approach
---------------------------------------------------------
• Intuition:
  Iterate through all possible index triplets (i, j, k) with i <= j <= k, calculate 
  nums[i] ^ nums[j] ^ nums[k], and store the results in an unordered_set to count unique values.

• Approach:
  Use three nested loops to traverse all combinations, insert XOR sums into a hash set, 
  and return the size of the set.

• Why it Works:
  Directly checks all possible triplets and counts unique XOR combinations.

• Time Complexity (TC): O(N^3)
• Space Complexity (SC): O(2^B) where B is bit-length of N.
---------------------------------------------------------
*/

/*
---------------------------------------------------------
2. Most Optimal Approach (Mathematical / Bitwise Observation)
---------------------------------------------------------
• Intuition:
  Since `nums` contains a complete permutation from 1 to `n`, taking XOR of 3 elements 
  allows us to toggle bits freely using combinations of numbers.
  For n >= 3, any integer from 0 to (2^k - 1) can be formed, where 2^k is the smallest 
  power of 2 strictly greater than n.

• Approach:
  - If n == 1: Only 1 ^ 1 ^ 1 = 1 is possible -> output 1.
  - If n == 2: Possible XOR values from {1, 2} are {1, 2} -> output 2.
  - If n >= 3: The answer is 2^(msb(n) + 1), which equals 1 << (__builtin_clz(1) - __builtin_clz(n) + 1)
    or simply the next power of 2 greater than n.

• Why it Works:
  With n >= 3, we have enough freedom using basis vectors and single bit toggles to achieve 
  every single binary pattern from 0 up to 2^(MSB(n)+1) - 1.

• Time Complexity (TC): O(1)
• Space Complexity (SC): O(1)
---------------------------------------------------------
*/

/*
=========================================================
FINAL APPROACH CHOICE:
We choose the Most Optimal (O(1)) Bitwise / Math Approach because N can be up to 10^5.
Brute force O(N^3) will lead to Time Limit Exceeded (TLE).
The mathematical observation guarantees full range coverage in constant time.
=========================================================
*/

class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();
        
        // Base case for n = 1
        if (n == 1) {
            return 1;
        }
        
        // Base case for n = 2
        if (n == 2) {
            return 2;
        }
        
        // For n >= 3, the answer is 2^(MSB(n) + 1)
        // Find highest set bit of n
        int msb = 31 - __builtin_clz(n);
        
        return 1 << (msb + 1);
    }
};
