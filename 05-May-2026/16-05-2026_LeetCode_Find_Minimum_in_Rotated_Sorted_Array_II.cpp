/*
Date: 16-05-2026
Problem Name: Find Minimum in Rotated Sorted Array II
Platform: LeetCode (Problem 154)
Difficulty: Hard
Tags: Array, Binary Search

Problem Summary:
Suppose an array of length n sorted in ascending order is rotated between 1 and n times. 
Given the sorted rotated array 'nums' that may contain duplicates, return the minimum 
element of this array. The objective is to minimize the number of operation steps.

Methods to Solve:

1. Brute Force (Linear Search)
- Intuition: Since we need the minimum element, we can traverse the entire array once.
- Approach: Iterate through the array from index 0 to n-1 and maintain a variable to track the minimum value.
- Dry Run: nums = [2,2,2,0,1] -> min starts at 2, stays 2, stays 2, becomes 0, stays 0. Return 0.
- Time Complexity: $O(n)$
- Space Complexity: $O(1)$
- Why better than previous method: N/A (Baseline)
- When to use: When the array is small or nearly all elements are identical.

2. Optimal Approach (Modified Binary Search)
- Intuition: Utilize the sorted property. In a rotated sorted array, binary search usually 
  takes $O(\log n)$. However, duplicates complicate the decision-making at the pivot.
- Approach: 
    - Use two pointers, 'low' and 'high'. 
    - Compare nums[mid] with nums[high].
    - If nums[mid] > nums[high]: The minimum must be in the right half (low = mid + 1).
    - If nums[mid] < nums[high]: The minimum is mid or in the left half (high = mid).
    - If nums[mid] == nums[high]: We cannot determine which side to pick. However, 
      since nums[mid] is the same as nums[high], we can safely ignore nums[high] and decrement 'high'.
- Dry Run: [3, 3, 1, 3] -> low=0, high=3, mid=1. nums[1]==nums[3], high=2. Next: mid=0, nums[0]>nums[2], low=1...
- Time Complexity: $O(\log n)$ average, $O(n)$ worst-case (e.g., all elements are the same).
- Space Complexity: $O(1)$
- Why better than previous method: Provides logarithmic performance for most cases while handling duplicates.
- When to use: Standard approach for rotated sorted arrays with duplicates.

Comparison Table:
Method         | TC            | SC     | Best Use Case
---------------|---------------|--------|-----------------------------
Brute Force    | $O(n)$        | $O(1)$ | Small arrays
Binary Search  | $O(\log n)$ * | $O(1)$ | General/Large scale cases
* Worst case $O(n)$ with duplicates.

Final Recommended Solution: Modified Binary Search.
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    /**
     * Finds the minimum element in a rotated sorted array that may contain duplicates.
     * Uses a modified Binary Search to achieve optimal performance.
     */
    int findMin(vector<int>& nums) {
        int low = 0;
        int high = nums.size() - 1;

        while (low < high) {
            int mid = low + (high - low) / 2;

            if (nums[mid] > nums[high]) {
                // Minimum must be in the right unsorted part
                low = mid + 1;
            } 
            else if (nums[mid] < nums[high]) {
                // Minimum is in the left part or is mid itself
                high = mid;
            } 
            else {
                // When nums[mid] == nums[high], we can't be sure where the minimum is.
                // However, we know nums[high] is duplicated at nums[mid], 
                // so we can safely reduce the search space by shrinking the right bound.
                high--;
            }
        }

        // The loop terminates when low == high, pointing to the minimum element.
        return nums[low];
    }
};
