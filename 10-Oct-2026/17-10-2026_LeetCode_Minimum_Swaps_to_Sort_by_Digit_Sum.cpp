/*
=========================================================
Date        : 17-10-2026
Problem Name: Minimum Swaps to Sort by Digit Sum
Platform    : LeetCode
Difficulty  : Medium
Tags        : Array, Hash Table, Sorting, Graph

Problem Summary:
- Given an array of distinct positive integers, sort them in increasing order based on their digit sum.
- If two numbers share the same digit sum, the smaller numerical value comes first.
- Return the minimum number of swaps required to rearrange the array into this sorted order.

Key Observation:
- Sorting elements and mapping each original position to its target sorted position creates permutation cycles.
- The minimum swaps required to sort an array via swaps is equal to (total elements - number of independent cycles).
=========================================================
*/

/*
=========================================================
APPROACH 1: Optimized Cycle-Based Permutation
=========================================================

• Intuition:
  - Each element belongs in a specific destination index after sorting. Tracking where elements move forms disjoint cycles.
  - To resolve a cycle of length L with minimum swaps, we need (L - 1) swaps.

• Approach:
  - Store pairs of (digit_sum, value, original_index) and sort them to find the correct target positions.
  - Use a visited array to track visited indices and traverse each permutation cycle.
  - For every unvisited index, traverse its cycle to count its size.

• Why it Works:
  - Graph cycle decomposition guarantees the minimum number of swaps to place each element into its sorted position.

• Time Complexity (TC):
  - O(N log N) for sorting the array elements based on digit sums and values.

• Space Complexity (SC):
  - O(N) for storing pairs, indices, and the visited array.

---------------------------------------------------------
FINAL APPROACH SELECTION:
---------------------------------------------------------
- The cycle-decomposition approach is chosen because it runs in optimal O(N log N) time and computes the exact minimum swaps required without simulating every single swap.
=========================================================
*/

#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
private:
    int getDigitSum(int n) {
        int sum = 0;
        while (n > 0) {
            sum += n % 10;
            n /= 10;
        }
        return sum;
    }

public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        
        // Store elements with their digit sum, original value, and original index
        vector<pair<pair<int, int>, int>> arr(n);
        for (int i = 0; i < n; ++i) {
            arr[i] = {{getDigitSum(nums[i]), nums[i]}, i};
        }
        
        // Sort based on digit sum first, then numerical value
        sort(arr.begin(), arr.end());
        
        // Find minimum swaps using cycle detection
        vector<bool> visited(n, false);
        int swaps = 0;
        
        for (int i = 0; i < n; ++i) {
            // If already visited or already in the correct position
            if (visited[i] || arr[i].second == i) {
                continue;
            }
            
            // Traverse the cycle
            int cycle_size = 0;
            int curr = i;
            while (!visited[curr]) {
                visited[curr] = true;
                curr = arr[curr].second;
                cycle_size++;
            }
            
            if (cycle_size > 1) {
                swaps += (cycle_size - 1);
            }
        }
        
        return swaps;
    }
};
