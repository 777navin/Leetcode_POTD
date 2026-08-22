/*
=========================================================
Date        : 22-08-2026
Problem Name: Check Divisibility by Digit Sum and Product
Platform    : LeetCode
Difficulty  : Easy
Tags        : Math

Problem Summary:
Given a positive integer n, calculate the sum of its digits and the product of its digits.
Add the digit sum and digit product together.
Check if n is divisible by this combined value.

Key Observation:
Extracting digits using modulo (% 10) and integer division (/ 10) allows calculating both sum and product in a single pass.
=========================================================
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH EXPLANATION
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

1. Optimal Simulation
• Intuition:
  Iterate through every digit of n to compute both the sum and the product concurrently.
• Approach:
  - Initialize sum to 0 and product to 1.
  - While temporary n > 0, extract the last digit with % 10, update sum and product, and divide n by 10.
  - Check if n % (sum + product) == 0.
• Why it Works:
  - Standard arithmetic extraction correctly evaluates each digit without string overhead.
• Time Complexity (TC):
  - O(log10(n)) since the loop runs for the number of digits in n.
• Space Complexity (SC):
  - O(1) auxiliary space as only basic integer variables are used.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
FINAL APPROACH
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• This approach directly computes the required values in a single pass with optimal time and space complexity.
• It avoids extra string conversion overhead and uses O(1) auxiliary memory.
*/

class Solution {
public:
    bool checkDivisibility(int n) {
        int temp = n;
        int digitSum = 0;
        int digitProduct = 1;

        while (temp > 0) {
            int digit = temp % 10;
            digitSum += digit;
            digitProduct *= digit;
            temp /= 10;
        }

        int totalSum = digitSum + digitProduct;
        return (n % totalSum == 0);
    }
};
