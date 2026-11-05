/*
=========================================================
Date        : 05-11-2026
Problem Name: 1385. Find the Distance Value Between Two Arrays
Platform    : LeetCode
Difficulty  : Easy
Tags        : Array, Binary Search, Sorting

Problem Summary:
Count elements in arr1 whose absolute difference from
EVERY element in arr2 is strictly greater than d.

Key Observation:
Sort arr2 and use lower_bound to find the closest
element that is greater than or equal to each arr1[i].
Check its previous element as well.
=========================================================

APPROACH 1: BRUTE FORCE
---------------------------------------------------------
- Intuition:
  Check every element of arr1 against every element of arr2.

- Approach:
  Count an element only if all absolute differences are > d.

- Why it Works:
  Directly checks the given condition for every pair.

- Time Complexity (TC): O(n * m)
- Space Complexity (SC): O(1)


APPROACH 2: SORTING + BINARY SEARCH (OPTIMIZED)
---------------------------------------------------------
- Intuition:
  The closest element in sorted arr2 must be either
  the lower_bound element or its previous element.

- Approach:
  1. Sort arr2.
  2. For each element x in arr1, find lower_bound(x).
  3. Check the difference with the returned element.
  4. Check its previous element if it exists.
  5. Count x if neither difference is <= d.

- Why it Works:
  Binary search identifies the closest possible candidates.
  If both candidates are farther than d, all other
  elements must also be farther than d.

- Time Complexity (TC): O(m log m + n log m)
- Space Complexity (SC): O(log m) auxiliary space
  for sorting, excluding the input arrays.


FINAL APPROACH:
---------------------------------------------------------
- Sorting + Binary Search is selected.
- It improves the brute-force O(n * m) approach.
- Each element of arr1 requires only O(log m) searching.
- Efficient and suitable for the given constraints.

=========================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1,
                             vector<int>& arr2,
                             int d) {

        // Sort the second array for binary search.
        sort(arr2.begin(), arr2.end());

        int distanceValue = 0;

        for (int x : arr1) {

            // Find the first element >= x.
            auto it = lower_bound(arr2.begin(), arr2.end(), x);

            bool valid = true;

            // Check the lower_bound element.
            if (it != arr2.end() && abs(*it - x) <= d) {
                valid = false;
            }

            // Check the previous element.
            if (it != arr2.begin() && abs(*prev(it) - x) <= d) {
                valid = false;
            }

            // Count if no element is within distance d.
            if (valid) {
                distanceValue++;
            }
        }

        return distanceValue;
    }
};

/*
=========================================================
Example 1:

Input:
arr1 = [4,5,8]
arr2 = [10,9,1,8]
d = 2

Output:
2

Example 2:

Input:
arr1 = [1,4,2,3]
arr2 = [-4,-3,6,10,20,30]
d = 3

Output:
2

=========================================================
*/
