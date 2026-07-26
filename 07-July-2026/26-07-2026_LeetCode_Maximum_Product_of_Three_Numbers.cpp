/*
=========================================================
Date        : 26-07-2026
Problem Name: Maximum Product of Three Numbers
Platform: LeetCode
Difficulty: Easy
Tags: Array, Math, Sorting

Problem Summary:
Given an integer array nums, find three numbers whose product is maximum 
and return the maximum product.

Key Observation:
The maximum product will either be the product of the three largest positive numbers, 
or the two smallest (most negative) numbers multiplied by the largest positive number.
=========================================================
*/

/*
1. Brute Force (Sorting)
- Intuition: The largest products come from the extremes of the sorted array.
- Approach: Sort the array in ascending order. Compare the product of the last 3 elements with the product of the first 2 and the last element.
- Why it Works: Sorting naturally groups the largest positive and largest negative magnitudes at the ends.
- Time Complexity (TC): O(N log N) due to the sorting algorithm.
- Space Complexity (SC): O(1) or O(log N) depending on the sort implementation.

2. Most Optimal (Single Pass)
- Intuition: We only need the top 3 maximums and top 2 minimums; sorting the whole array is unnecessary.
- Approach: Iterate through the array once, continuously updating variables for max1, max2, max3 and min1, min2.
- Why it Works: Extracts exactly the required elements in a single traversal without rearranging the whole array.
- Time Complexity (TC): O(N) as we visit each element exactly once.
- Space Complexity (SC): O(1) because we only use a constant number of extra variables.
*/

/*
FINAL APPROACH
- The Most Optimal (Single Pass) approach is chosen.
- It is better than the sorting approach because it reduces the time complexity from O(N log N) to O(N).
- It runs strictly in linear time and uses constant space, making it the most efficient solution possible.
*/

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        int min1 = INT_MAX, min2 = INT_MAX;
        int max1 = INT_MIN, max2 = INT_MIN, max3 = INT_MIN;
        
        for (int n : nums) {
            // Update minimums
            if (n <= min1) {
                min2 = min1;
                min1 = n;
            } else if (n <= min2) {
                min2 = n;
            }
            
            // Update maximums
            if (n >= max1) {
                max3 = max2;
                max2 = max1;
                max1 = n;
            } else if (n >= max2) {
                max3 = max2;
                max2 = n;
            } else if (n >= max3) {
                max3 = n;
            }
        }
        
        // Return the maximum of the two possible combinations
        return max(max1 * max2 * max3, min1 * min2 * max1);
    }
};
