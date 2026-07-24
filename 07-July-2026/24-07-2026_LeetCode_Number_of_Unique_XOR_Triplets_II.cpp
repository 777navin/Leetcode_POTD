/*
=========================================================
Date        : 24-07-2026
Problem Name: 3514. Number of Unique XOR Triplets II
Platform    : LeetCode
Difficulty  : Medium
Tags        : Array, Math, Bit Manipulation, Enumeration

Problem Summary:
Given an integer array nums, a XOR triplet is defined as nums[i] ^ nums[j] ^ nums[k]
where i <= j <= k. Return the number of unique XOR triplet values obtained across
all possible index triplets (i, j, k).

Key Observation:
Since we only care about unique XOR values and order doesn't matter, we can first 
extract unique elements from nums. We can then simulate building XOR sums 1 element at 
a time across 3 rounds, starting from {0}.
=========================================================
*/

#include <vector>
#include <unordered_set>
#include <set>
#include <algorithm>

using namespace std;

/*
---------------------------------------------------------
APPROACH 1: Set Expansion / BFS Simulation
---------------------------------------------------------
• Intuition:
  XORing 3 elements is equivalent to applying the XOR operation 3 times starting from 0.
  Duplicates in the initial array don't create new XOR values, so we can work with unique numbers.

• Approach:
  1. Reduce nums to a set/vector of unique values.
  2. Start with a set `current = {0}`.
  3. Perform 3 rounds: in each round, create a `next_set` containing all values `x ^ num`
     for `x` in `current` and `num` in unique values.
  4. Return the size of the set after 3 rounds.

• Why it Works:
  XOR is associative and commutative. Taking all possible values at step 1, step 2, and step 3 
  covers every valid XOR combination of 3 elements.

• Time Complexity (TC):
  O(3 * |Unique| * Max_XOR_Values) -> O(N * K) where N <= 1500 and K <= 2048.
  
• Space Complexity (SC):
  O(Max_XOR_Values) -> O(K) where K <= 2048.
---------------------------------------------------------
*/

/*
---------------------------------------------------------
FINAL APPROACH SELECTION
---------------------------------------------------------
• Why this approach is chosen:
  It avoids computing duplicate triplets and O(N^3) or O(N^2) loops over array indices.
  Since max element <= 1500, the maximum possible XOR value is < 2048.
  Expanding sets of reachable XOR sums up to length 3 is extremely fast and cleanly fits within limits.
---------------------------------------------------------
*/

class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        // Collect unique values from input
        unordered_set<int> unique_nums(nums.begin(), nums.end());
        
        unordered_set<int> current = {0};
        
        // Expand 3 times to represent 3 picks
        for (int round = 0; round < 3; ++round) {
            unordered_set<int> next_set;
            for (int val : current) {
                for (int num : unique_nums) {
                    next_set.insert(val ^ num);
                }
            }
            current = move(next_set);
        }
        
        return current.size();
    }
};
