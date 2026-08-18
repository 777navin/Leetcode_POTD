/*
=========================================================
Date        : 18-08-2026
Problem Name: Find the Largest Almost Missing Integer (LeetCode 3471)
Platform    : LeetCode
Difficulty  : Easy
Tags        : Array, Hash Table, Counting

Problem Summary:
Given an integer array `nums` and an integer `k`, find the largest integer 
that appears in exactly one contiguous subarray of length `k`.
If no such integer exists, return -1.

Key Observation:
- When k = 1, elements with total frequency 1 appear in exactly 1 subarray.
- When k = n, all distinct elements appear in exactly 1 subarray.
- When 1 < k < n, only the boundary elements nums[0] and nums[n-1] can appear in exactly 1 subarray (if their overall frequency is 1).
=========================================================
*/

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 1: Brute Force (Subarray Frequency Map)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  Directly simulate the condition by iterating over all subarrays of length k 
  and counting how many distinct subarrays contain each number.

• Approach:
  1. For each starting index `i` from 0 to `n - k`, collect unique elements in `nums[i ... i + k - 1]`.
  2. For every unique element found in that subarray, increment its count in a frequency map.
  3. Scan the frequency map to find the maximum key with count == 1.

• Why it Works:
  It accurately mirrors the problem statement by counting subarray occurrences per distinct value.

• Time Complexity : O((n - k + 1) * k) -> O(n * k)
• Space Complexity: O(n)
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 2: Optimized Case Analysis (Optimal)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  Analyze the overlap of length-k sliding windows across indices:
  elements inside the array (0 < i < n - 1) always belong to at least 2 windows when 1 < k < n.

• Approach:
  1. Count total occurrences of every element in `nums`.
  2. Case 1 (k == 1): Return the maximum element with total frequency == 1.
  3. Case 2 (k == n): Return the maximum element present anywhere in `nums`.
  4. Case 3 (1 < k < n): Check candidates `nums[0]` and `nums[n - 1]`. 
     If an endpoint has total frequency == 1, it appears in exactly 1 subarray of length k.
     Return the maximum valid candidate, or -1 if none qualify.

• Why it Works:
  Window coverage analysis proves strictly which indices can have a subarray frequency of 1 without full simulation.

• Time Complexity : O(n)
• Space Complexity: O(1) auxiliary space (using a fixed-size frequency array / hash map up to 51)
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
FINAL APPROACH: Case Analysis (O(n) Time, O(1) Extra Space)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Case analysis reduces the problem to single-pass frequency counting.
• Avoids redundant window traversals and set allocations used in simulation.
• Provides optimal O(n) runtime and minimal memory footprint.
*/

class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, int> freq;
        for (int x : nums) {
            freq[x]++;
        }

        // Case 1: k == 1
        if (k == 1) {
            int ans = -1;
            for (const auto& [val, count] : freq) {
                if (count == 1) {
                    ans = max(ans, val);
                }
            }
            return ans;
        }

        // Case 2: k == n
        if (k == n) {
            int ans = -1;
            for (int x : nums) {
                ans = max(ans, x);
            }
            return ans;
        }

        // Case 3: 1 < k < n
        int ans = -1;
        if (freq[nums[0]] == 1) {
            ans = max(ans, nums[0]);
        }
        if (freq[nums[n - 1]] == 1) {
            ans = max(ans, nums[n - 1]);
        }

        return ans;
    }
};
