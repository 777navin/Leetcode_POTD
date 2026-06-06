/*
Date: 06-06-2026
Problem Name: Left and Right Sum Differences
Platform: LeetCode
Difficulty: Easy
Tags: Array, Prefix Sum

Problem Summary
You are given a 0-indexed integer array `nums` of size `n`. 
Define two arrays `leftSum` and `rightSum` where:
- `leftSum[i]` is the sum of elements to the left of index `i`. If no such element, `leftSum[i] = 0`.
- `rightSum[i]` is the sum of elements to the right of index `i`. If no such element, `rightSum[i] = 0`.
Return an array `answer` where `answer[i] = |leftSum[i] - rightSum[i]|`.

Methods to Solve:
1. Brute Force
2. Optimal Approach (Prefix Sum/Running Sum)

For EACH method include:

- Brute Force:
  - Intuition: For every index `i`, iterate through all elements to the left to calculate `leftSum` and all elements to the right to calculate `rightSum`.
  - Approach: Nested loops for each index `i` to compute sums.
  - Time Complexity: O(n^2)
  - Space Complexity: O(n)

- Optimal Approach:
  - Intuition: Notice that `leftSum[i]` is the running sum of elements from `0` to `i-1`. `rightSum[i]` can be calculated as `totalSum - leftSum[i] - nums[i]`.
  - Approach: Calculate the total sum once. Iterate through the array, maintaining a `currentLeftSum`. For each index, calculate `rightSum` using the formula above, compute the absolute difference, and store it.
  - Dry Run: nums = [10, 4, 8, 3], TotalSum = 25
    i=0: left=0, right=25-0-10=15, diff=15
    i=1: left=10, right=25-10-4=11, diff=1
    i=2: left=14, right=25-14-8=3, diff=11
    i=3: left=22, right=25-22-3=0, diff=22
  - Time Complexity: O(n)
  - Space Complexity: O(1) (excluding output array)

Comparison Table:
Method      | TC    | SC    | Best Use Case
Brute Force | O(n^2)| O(n)  | Small constraints
Optimal     | O(n)  | O(1)  | Production/Competitive

Final Recommended Solution: Optimal Approach (O(n))
*/

#include <vector>
#include <cmath>
#include <numeric>

using namespace std;

class Solution {
public:
    /**
     * Optimal Approach using Prefix Sum logic
     * Time Complexity: O(n)
     * Space Complexity: O(1) (ignoring output vector)
     */
    vector<int> leftRightDifference(vector<int>& nums) {
        int n = nums.size();
        vector<int> answer(n);
        
        // Calculate total sum of the array
        int totalSum = accumulate(nums.begin(), nums.end(), 0);
        
        int currentLeftSum = 0;
        
        for (int i = 0; i < n; ++i) {
            // rightSum is totalSum minus leftSum and the current element
            int currentRightSum = totalSum - currentLeftSum - nums[i];
            
            // Calculate absolute difference
            answer[i] = abs(currentLeftSum - currentRightSum);
            
            // Update leftSum for the next iteration
            currentLeftSum += nums[i];
        }
        
        return answer;
    }
};
