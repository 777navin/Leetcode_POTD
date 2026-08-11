/*
=========================================================
Date        : 11-08-2026
Problem Name: Smallest Missing Integer Greater Than Sequential Prefix Sum
Platform    : LeetCode
Difficulty  : Easy
Tags        : Array, Hash Table, Sorting

Problem Summary:
Find the sum of the longest contiguous sequential prefix starting at index 0.
Then, return the smallest integer greater than or equal to this sum that is missing from the array.

Key Observation:
The sequential prefix must strictly start at index 0, so we can stop accumulating the sum at the first non-sequential element.
=========================================================

1. Brute Force
- Intuition: Calculate the prefix sum, then repeatedly search the entire array to check if the candidate sum exists.
- Approach: Traverse the array to find the sequential prefix sum. Use a while loop with a nested linear search (`std::find`) to check for existence.
- Why it Works: It strictly simulates the problem statement but does redundant searches for the missing element.
- Time Complexity (TC): O(N^2) in the worst case due to repeated linear searches.
- Space Complexity (SC): O(1) as no extra space is used.

2. Most Optimal
- Intuition: Repeated linear searches are slow. A hash data structure provides O(1) lookups for existence checks.
- Approach: Calculate the longest sequential prefix sum. Store all array elements in an `unordered_set`. Increment the sum until it is not found in the set.
- Why it Works: The hash set quickly verifies if the current candidate exists in the array, avoiding nested loops.
- Time Complexity (TC): O(N) to build the set and find the prefix sum, O(N) worst-case to find the missing integer. Overall O(N).
- Space Complexity (SC): O(N) to store elements in the `unordered_set`.

=========================================================
FINAL APPROACH
We choose the Most Optimal approach using a Hash Set.
It is significantly better than the Brute Force method because it reduces the search time from O(N^2) to O(N) by trading a small O(N) spatial footprint for O(1) lookups.
=========================================================
*/

#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int missingInteger(vector<int>& nums) {
        int prefixSum = nums[0];
        
        // Find the sum of the longest sequential prefix starting from index 0
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == nums[i - 1] + 1) {
                prefixSum += nums[i];
            } else {
                break;
            }
        }
        
        // Store all elements in a hash set for O(1) lookups
        unordered_set<int> numSet(nums.begin(), nums.end());
        
        // Increment prefixSum until we find a value not present in the array
        while (numSet.count(prefixSum)) {
            prefixSum++;
        }
        
        return prefixSum;
    }
};
