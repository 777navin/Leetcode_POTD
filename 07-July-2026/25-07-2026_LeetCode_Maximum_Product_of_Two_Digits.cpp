/*
=========================================================
Date        : 25-07-2026
Problem Name: Maximum Product of Two Digits
Platform    : LeetCode
Difficulty  : Easy
Tags        : Math, Sorting

Problem Summary:
Given a positive integer n, return the maximum product of 
any two digits present in n. A digit can be used twice if 
it appears more than once in n.

Key Observation:
Extracting all digits, sorting them in non-decreasing order, 
and multiplying the last two elements gives the maximum product.
=========================================================
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
=========================================================
APPROACH EXPLANATION
=========================================================

1. Sorting Approach (Vector Storage & Sorting)
• Intuition:
  - Extract all digits of n, store them in a vector, and sort the vector.
  - The largest two digits will end up at the end of the vector.
• Approach:
  - Loop while n > 0, extracting digits using (n % 10) and pushing into a vector.
  - Sort the vector in ascending order.
  - Multiply the last two elements (highest two digits) and return the product.
• Why it Works:
  - Sorting brings the largest digits to the highest indices, ensuring their product is maximal.
• Time Complexity (TC): O(d log d), where d is the number of digits in n (d <= 10).
• Space Complexity (SC): O(d) to store the digits in a vector.

2. Two-Pointer / Two-Pass Optimal Approach (Single-Pass Tracking)
• Intuition:
  - Instead of storing and sorting all digits, track the two largest digits in a single pass.
• Approach:
  - Maintain two variables, max1 and max2, initialized to 0.
  - Iterate through digits of n; update max1 and max2 accordingly.
  - Return max1 * max2.
• Why it Works:
  - We only need the top two largest digits to compute the maximum product.
• Time Complexity (TC): O(d), where d is the number of digits.
• Space Complexity (SC): O(1) auxiliary space.
*/

/*
=========================================================
FINAL APPROACH CHOSEN
=========================================================
• Approach Chosen: Sorting Approach (Extract to Vector and Sort)
• Reason: Explicitly requested by the user ("extract storer in vecvtor sort then last 2 digit product").
  Since the maximum number of digits is 10 (as n <= 10^9), the vector size is tiny, 
  making sorting extremely simple and running virtually instantaneously.
=========================================================
*/

class Solution {
public:
    int maxProduct(int n) {
        vector<int> digits;
        
        // Extract digits and store in a vector
        while (n > 0) {
            digits.push_back(n % 10);
            n /= 10;
        }
        
        // Sort digits in ascending order
        sort(digits.begin(), digits.end());
        
        // Product of the last two digits (largest two)
        int sz = digits.size();
        return digits[sz - 1] * digits[sz - 2];
    }
};
