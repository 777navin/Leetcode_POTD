/*
=========================================================
Date        : 10-10-2026
Problem Name: Minimum Sum of Squared Difference
Platform    : LeetCode
Difficulty  : Medium
Tags        : Array, Greedy, Hash Table, Counting

Problem Summary:
Given two arrays nums1 and nums2, we can perform at most k1 operations on nums1 and k2 operations on nums2 (each operation adds or subtracts 1 from an element). We need to minimize the sum of squared differences between corresponding elements of nums1 and nums2.

Key Observation:
Since operations are symmetric, we can pool all available operations into $K = k1 + k2$ and greedily reduce the largest absolute differences starting from the maximum possible difference down to 1.
=========================================================
*/

#include <vector>
#include <cmath>
#include <algorithm>

class Solution {
public:
    /*
    =========================================================
    Approach: Greedy with Frequency Array (Optimal Counting Approach)
    
    • Intuition: Decreasing a larger difference yields a quadratically greater reduction in the sum of squares than decreasing a smaller difference. Using a frequency array allows us to process differences efficiently in descending order.
    • Approach: 
      1. Calculate the absolute differences and store their frequencies in a `countDiff` array up to $10^5$.
      2. Combine operations into $K = k1 + k2$.
      3. Iterate backwards from $10^5$ down to 1, greedily reducing as many elements at `currDiff` as possible using $K$.
      4. Shift the reduced counts to `currDiff - 1` and decrement $K$.
      5. Compute the final sum of squared differences.
    • Why it Works: Greedily reducing the maximum current difference at each step ensures optimal reduction of the strictly convex sum of squares function.
    • Time Complexity (TC): O(n + M), where n is the size of the arrays and M is the maximum absolute difference ($10^5$).
    • Space Complexity (SC): O(M) to store the frequency array.
    =========================================================
    */
    long long minSumSquareDiff(std::vector<int>& nums1, std::vector<int>& nums2, int k1, int k2) {
        int n = nums1.size();
        
        // Take out all the diffs and find the counts
        std::vector<int> countDiff(1e5 + 1, 0);
        for (int i = 0; i < n; ++i) {
            int d = std::abs(nums1[i] - nums2[i]);
            countDiff[d]++;
        }

        int K = k1 + k2;

        for (int currDiff = 1e5; currDiff > 0 && K > 0; currDiff--) {
            int countOps = std::min(countDiff[currDiff], K);

            countDiff[currDiff] -= countOps; 
            countDiff[currDiff - 1] += countOps;
            K -= countOps;
        }

        long long result = 0;
        for (long long d = 1; d <= 1e5; d++) {
            result += (countDiff[d] * d * d);
        }

        return result;
    }
};
