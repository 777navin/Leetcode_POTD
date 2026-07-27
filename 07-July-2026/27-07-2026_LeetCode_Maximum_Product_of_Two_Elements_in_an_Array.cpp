/*
=========================================================
Date        : 27-07-2026
Problem Name: 1464. Maximum Product of Two Elements in an Array
Platform    : LeetCode
Difficulty  : Easy
Tags        : Array, Sorting, Heap (Priority Queue)

Problem Summary:
Given an array of positive integers 'nums', choose two different indices i and j.
Return the maximum possible value of (nums[i]-1) * (nums[j]-1).

Key Observation:
Since all elements are positive (>= 1), the maximum product will always come 
from the two largest elements in the array.
=========================================================
*/

/*
=========================================================
APPROACH 1: Brute Force (Not implemented below)
=========================================================
• Intuition: The simplest way is to try all possible pairs of indices.
• Approach : Use two nested loops to iterate through all unique pairs of (i, j).
• Why it Works: It exhaustively calculates the product for every valid pair and tracks the maximum.
• TC: O(N^2) where N is the size of the array.
• SC: O(1) as no extra space is used.

=========================================================
APPROACH 2: Sorting (Better) (Not implemented below)
=========================================================
• Intuition: The largest product comes from the two largest numbers.
• Approach : Sort the array in ascending order and multiply (last_element - 1) and (second_last_element - 1).
• Why it Works: Sorting guarantees the largest elements are at the end of the array.
• TC: O(N log N) due to the sorting algorithm.
• SC: O(1) or O(log N) depending on the sorting implementation.

=========================================================
APPROACH 3: Single Pass to find max two elements (Most Optimal)
=========================================================
• Intuition: We only need the top two largest elements, which can be found without fully sorting the array.
• Approach : Iterate through the array once while keeping track of the largest (m1) and second largest (m2) values.
• Why it Works: By updating the top two variables on the fly, we find the two largest numbers in a single linear scan.
• TC: O(N) as it requires only one traversal of the array.
• SC: O(1) since we only use two integer variables.
*/

/*
=========================================================
FINAL APPROACH EXPLANATION
=========================================================
We choose Approach 3 (Single Pass) because it is the most optimal in terms of 
time complexity. It reduces the O(N log N) sorting time to O(N) linear time, 
which is the theoretical lower bound for this problem since we must read every element.
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int m1 = 0; // Largest element
        int m2 = 0; // Second largest element
        
        for (int num : nums) {
            if (num > m1) {
                m2 = m1;     // Old largest becomes second largest
                m1 = num;    // Update largest
            } else if (num > m2) {
                m2 = num;    // Update second largest only
            }
        }
        
        return (m1 - 1) * (m2 - 1);
    }
};
