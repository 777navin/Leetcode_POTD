/*
=========================================================
Date        : 03-09-2026
Problem Name: 3876. Construct Uniform Parity Array II
Platform    : LeetCode
Difficulty  : Medium
Tags        : Array, Math, Greedy

Problem Summary:
Given an array nums1 of n distinct positive integers, determine if an array nums2 
can be constructed such that all its elements have uniform parity (all odd or all even).
For each index i, set nums2[i] = nums1[i] or nums2[i] = nums1[i] - nums1[j] (where nums1[i] - nums1[j] >= 1).

Key Observation:
Subtracting an odd number flips the parity, while subtracting an even number keeps parity unchanged.
The minimum element of nums1 cannot have anything subtracted from it, so its original parity must be achievable.
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Check Target Parity Independently (Optimal)
---------------------------------------------------------
• Intuition:
  - If all elements in nums1 already share the same parity, the answer is immediately true.
  - Otherwise, nums1 contains both odd and even elements.
  - The smallest element in nums1, min_val, cannot be reduced because nums1[i] - nums1[j] >= 1 requires a strictly smaller element.
  - Thus, if min_val is odd, can we make all elements odd?
    * Odd numbers stay odd without subtraction: nums2[i] = nums1[i].
    * Even numbers can be made odd by subtracting an odd number strictly smaller than them: nums1[i] - min_val (even - odd = odd).
    * Since min_val is the global minimum and odd, every even number is strictly greater than min_val. Thus, all can become odd!
  - If min_val is even, can we make all elements even?
    * Even numbers stay even.
    * Odd numbers would need an odd number strictly smaller than them subtracted (odd - odd = even).
    * But if there exists an odd number smaller than min_val, min_val wouldn't be the global minimum.
    * Specifically, the smallest odd element cannot subtract any smaller odd element, so it can never become even.
    * Hence, if min_val is even and odd numbers exist, it's impossible to make all elements even or odd.
  - Therefore, return true if either all elements share the same parity, or if the global minimum element is odd.

• Approach:
  - Find the minimum element in nums1 and count how many odd numbers exist.
  - If odd count is 0 or n (all even or all odd), return true.
  - If the global minimum element is odd, return true.
  - Otherwise, return false.

• Why it Works:
  - Any even number greater than min_odd can be transformed into an odd number via (even - min_odd = odd > 0).
  - The minimum odd number can never become even because no smaller odd number exists in the array.

• Time Complexity (TC):
  - O(n): Single pass over the array to find min and check parities.

• Space Complexity (SC):
  - O(1): Only constant extra variables used.
---------------------------------------------------------
*/

/*
---------------------------------------------------------
FINAL APPROACH:
- Approach 1 runs in linear O(n) time and O(1) auxiliary space, which is optimal given the input constraints (n <= 10^5).
- It handles all parity transitions greedily with minimal operations.
---------------------------------------------------------
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int min_val = nums1[0];
        int odd_count = 0;
        int n = nums1.size();

        for (int x : nums1) {
            if (x < min_val) {
                min_val = x;
            }
            if (x % 2 != 0) {
                odd_count++;
            }
        }

        // Case 1: All elements already have the same parity
        if (odd_count == 0 || odd_count == n) {
            return true;
        }

        // Case 2: Mixed parities; can make all elements odd iff the global minimum is odd
        return (min_val % 2 != 0);
    }
};
