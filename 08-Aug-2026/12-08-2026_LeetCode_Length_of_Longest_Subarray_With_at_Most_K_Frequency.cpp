/*
=========================================================
Date        : 12-08-2026
Problem Name: Length of Longest Subarray With at Most K Frequency
Platform: LeetCode
Difficulty: Medium
Tags: Array, Hash Table, Sliding Window

Problem Summary:
Find the maximum length of a contiguous subarray in which the frequency 
of each unique element is less than or equal to k.

Key Observation:
Since elements are contiguous and we only care about maintaining a condition 
(frequency <= k), a sliding window dynamically bounded by left and right pointers is ideal.
=========================================================
*/

/*
1. Brute Force
- Intuition: Check every possible subarray to see if it satisfies the frequency condition.
- Approach: Use two nested loops to define subarrays, count frequencies using a hash map, and update the max length if valid.
- Why it Works: It exhaustively evaluates all subarrays.
- Time Complexity (TC): O(N^2) worst case to build the frequency map for every starting point.
- Space Complexity (SC): O(N) to store frequencies in the worst case (all unique elements).

2. Optimized (Sliding Window)
- Intuition: Instead of recalculating frequencies from scratch, incrementally update a running frequency map.
- Approach: Use two pointers (`left` and `right`). Expand `right` to include elements. If `nums[right]` exceeds `k` occurrences, increment `left` until the condition is met again.
- Why it Works: We only ever shrink the window from the left just enough to make it valid again, ensuring we find the maximal valid length ending at `right`.
- Time Complexity (TC): O(N) because each element is processed at most twice (once by `right`, once by `left`).
- Space Complexity (SC): O(N) to store frequencies in an unordered_map.
*/

/*
Final Approach
- Why this approach is chosen: The constraints (N = 10^5) will cause a Brute Force approach to Time Limit Exceed (TLE). The Sliding Window approach guarantees a linear time execution.
- Why it is better than the previous ones: It eliminates redundant iterations and frequency counts by maintaining a single, dynamically resizing valid window.
*/

#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        int max_len = 0;
        int left = 0;
        int n = nums.size();
        
        for (int right = 0; right < n; ++right) {
            // Expand the window by including the current element
            freq[nums[right]]++;
            
            // Shrink the window from the left if the condition is violated
            while (freq[nums[right]] > k) {
                freq[nums[left]]--;
                left++;
            }
            
            // The window [left, right] is now guaranteed to be valid
            max_len = max(max_len, right - left + 1);
        }
        
        return max_len;
    }
};
