/*
=========================================================
Date        : 06-08-2026
Problem Name: Smallest Divisible Digit Product I
Platform: LeetCode
Difficulty: Easy
Tags: Math, Enumeration

Problem Summary:
Given two integers n and t, find the smallest integer greater 
than or equal to n whose digit product is divisible by t.

Key Observation:
Every multiple of 10 has a digit product of 0, which is divisible 
by any t. Therefore, the answer will always be found within at most 10 increments.
=========================================================

1. Iterative Enumeration (Optimal for Constraints)
• Intuition: The distance to the next valid number is extremely small (max 10 steps).
• Approach: Iterate upwards from n, calculate the product of digits for each number, and check divisibility by t.
• Why it Works: We are guaranteed to hit a multiple of 10 (digit product 0) within 10 steps, ensuring rapid termination.
• Time Complexity (TC): O(1) - Maximum 10 iterations, each taking minimal digit extractions.
• Space Complexity (SC): O(1) - No extra space used.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
FINAL APPROACH
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• This iterative enumeration approach is chosen because the constraints are very small (n <= 100).
• It is highly efficient, cleanly bounded to O(1) practically, and avoids the unnecessary complexity of a closed-form mathematical approach for these constraints.
*/

class Solution {
public:
    int smallestNumber(int n, int t) {
        while (true) {
            int prod = 1;
            int temp = n;
            
            // Calculate the product of digits
            while (temp > 0) {
                prod *= (temp % 10);
                temp /= 10;
            }
            
            // Check if the product is divisible by t
            if (prod % t == 0) {
                return n;
            }
            
            // Move to the next number
            n++;
        }
    }
};
