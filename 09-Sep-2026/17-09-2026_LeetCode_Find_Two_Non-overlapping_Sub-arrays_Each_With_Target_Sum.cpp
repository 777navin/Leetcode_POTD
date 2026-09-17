/*
=========================================================
Date        : 17-09-2026
Problem Name: Find Two Non-overlapping Sub-arrays Each With Target Sum
Platform    : LeetCode
Difficulty  : Medium
Tags        : Array, Dynamic Programming, Sliding Window

Problem Summary:
- Given an array of integers `arr` and an integer `target`.
- Find two non-overlapping sub-arrays each having a sum equal to `target`.
- Return the minimum sum of their lengths, or -1 if no such pair exists.

Key Observation:
- We can precalculate the minimum length of a valid sub-array ending at or before each index, and starting at or after each index, using a sliding window approach.
=========================================================
*/

/*
=========================================================
APPROACH EXPLANATION
=========================================================

1. Sliding Window + Prefix Minimum Array
   • Intuition: Find all valid sub-arrays with sum equal to target using a sliding window, and record their lengths.
   • Approach: 
     - Maintain a sliding window to find valid sub-arrays summing to `target`.
     - Create a `min_len` array where `min_len[i]` stores the minimum length of a valid sub-array ending at or before index `i`.
     - Iterate through the array a second time with the sliding window to find a second valid sub-array starting at or after index `i`, and combine it with `min_len[i - 1]`.
   • Why it Works: It independently tracks the shortest valid sub-array on the left and right of every split point in O(N) time.
   • Time Complexity (TC): O(N)
   • Space Complexity (SC): O(N)

=========================================================
FINAL APPROACH SELECTION
=========================================================
• We choose the Sliding Window with Prefix Minimum array approach because it avoids the O(N^2) overhead of checking all pairs.
• It efficiently computes the optimal answer in a single pass for window tracking and a linear scan for combination.
=========================================================
*/

#include <vector>
#include <algorithm>
#include <climits>

class Solution {
public:
    int minSumOfLengths(std::vector<int>& arr, int target) {
        int n = arr.size();
        // min_from_start[i] stores the minimum length of a valid sub-array in range [0, i]
        std::vector<int> min_from_start(n, INT_MAX);
        
        int current_sum = 0;
        int left = 0;
        int min_len = INT_MAX;
        int result = INT_MAX;
        
        for (int right = 0; right < n; ++right) {
            current_sum += arr[right];
            while (current_sum > target) {
                current_sum -= arr[left++];
            }
            
            if (current_sum == target) {
                int current_sub_len = right - left + 1;
                min_len = std::min(min_len, current_sub_len);
            }
            
            min_from_start[right] = min_len;
        }
        
        current_sum = 0;
        left = n - 1;
        min_len = INT_MAX;
        
        for (int right = n - 1; right >= 0; --right) {
            current_sum += arr[right];
            while (current_sum > target) {
                current_sum -= arr[left--];
            }
            
            if (current_sum == target) {
                int current_sub_len = left - right + 1;
                min_len = std::min(min_len, current_sub_len);
            }
            
            // If there is a valid sub-array to the left of the current window
            if (right > 0 && min_len != INT_MAX && min_from_start[right - 1] != INT_MAX) {
                result = std::min(result, min_len + min_from_start[right - 1]);
            }
        }
        
        return result == INT_MAX ? -1 : result;
    }
};
