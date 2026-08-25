/*
=========================================================
Date        : 25-08-2026
Problem Name: Smallest Missing Multiple of K
Platform    : LeetCode
Difficulty  : Easy
Tags        : Array, Hash Table

Problem Summary:
Given an array of integers nums and an integer k, find the smallest 
positive multiple of k (i.e., k, 2k, 3k, ...) that does not appear in nums.

Key Observation:
Since we only need to check multiples starting from k in ascending order, 
we can efficiently look up each multiple in a hash set until the first 
missing multiple is found.
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Brute Force (Linear Search)
---------------------------------------------------------
• Intuition:
  Iterate through multiples of k (k, 2k, 3k, ...) and search for each 
  linearly in the array nums until one is not found.

• Approach:
  Start with multiple = k. For each multiple, loop through the entire 
  nums array. If not found, return it; otherwise, increment by k.

• Why it Works:
  Guarantees that multiples are checked in strictly increasing order, 
  finding the smallest missing one first.

• Time Complexity (TC) : O(M * N), where N is nums.size() and M is the 
                         number of multiples checked.
• Space Complexity (SC): O(1) auxiliary space.

---------------------------------------------------------
APPROACH 2: Hash Set Lookup (Optimal)
---------------------------------------------------------
• Intuition:
  Linear scans can be avoided by inserting all elements of nums into 
  a hash set for O(1) average lookup time.

• Approach:
  1. Insert all elements of nums into an unordered_set.
  2. Start a variable `ans = k`.
  3. While `ans` is present in the set, increment `ans += k`.
  4. Return `ans` once it is not found.

• Why it Works:
  The first multiple not present in the set is guaranteed to be the 
  smallest positive missing multiple.

• Time Complexity (TC) : O(N + M) on average, where N is nums.size() 
                         and M is the number of multiples checked.
• Space Complexity (SC): O(N) to store distinct elements in the hash set.
---------------------------------------------------------
*/

/*
=========================================================
FINAL APPROACH: Hash Set Lookup
=========================================================
• Chosen because it provides O(1) average membership checks.
• Avoids repeated O(N) array traversals used in the brute-force approach.
• Clean, robust, and optimal for both small and large constraint ranges.
=========================================================
*/

#include <vector>
#include <unordered_set>

class Solution {
public:
    int missingMultiple(std::vector<int>& nums, int k) {
        std::unordered_set<int> present(nums.begin(), nums.end());
        int candidate = k;
        
        while (present.count(candidate)) {
            candidate += k;
        }
        
        return candidate;
    }
};
