/*
Date: 28-06-2026
Problem Name: Maximum Element After Decreasing and Rearranging
Platform: LeetCode
Difficulty: Medium
Tags: Array, Greedy, Sorting

Problem Summary:
Given an array of positive integers 'arr', perform operations to satisfy:
1. The first element must be 1.
2. The absolute difference between any two adjacent elements must be <= 1.
Operations:
- Decrease any element to a smaller positive integer.
- Rearrange elements in any order.
Goal: Return the maximum possible value of an element in the modified array.

Methods to Solve:
1. Sorting + Greedy
   - Intuition: To maximize the values, we should keep the smallest numbers as small as possible (starting with 1) and try to increase the rest greedily.
   - Approach: 
     1. Sort the array.
     2. Set the first element to 1.
     3. Iterate through the array; if the current element is more than 1 greater than the previous element, decrease it to (previous + 1).
     4. The last element will be the maximum possible value.
   - Time Complexity: O(N log N) due to sorting.
   - Space Complexity: O(1) or O(N) depending on sort implementation.

Comparison Table:
Method         | TC       | SC   | Best Use Case
---------------|----------|------|--------------
Sorting+Greedy | O(N log N)| O(1)| General case

Final Recommended Solution: Sorting + Greedy approach.
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    /**
     * Method: Sorting and Greedy Approach
     * * Strategy:
     * 1. Sort the array to process elements in non-decreasing order.
     * 2. Ensure the first element is 1.
     * 3. For every subsequent element, ensure it is at most 1 greater than the previous.
     */
    int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
        // Step 1: Sort the array
        sort(arr.begin(), arr.end());
        
        // Step 2: Set the first element to 1
        arr[0] = 1;
        
        // Step 3: Adjust the remaining elements
        for (size_t i = 1; i < arr.size(); ++i) {
            if (arr[i] > arr[i - 1] + 1) {
                arr[i] = arr[i - 1] + 1;
            }
        }
        
        // The last element is the maximum possible value
        return arr.back();
    }
};
