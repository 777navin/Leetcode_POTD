/*
=========================================================
Date        : 07-07-2026
Problem Name: Concatenate Non-Zero Digits and Multiply by Sum I
Platform    : LeetCode
Difficulty  : Easy
Tags        : Math, String, Simulation

Problem Summary:
Given an integer n, calculate the sum of its digits.
Form a new number by concatenating all non-zero digits of n.
Return the result of multiplying this new number by the digit sum.

Key Observation:
If the number contains only zeros (like 0, 10, 100), the concatenated 
string will be empty. We must handle this case to avoid runtime errors.
=========================================================
*/

#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
    /**
     * Approach:
     * 1. Intuition: Convert the number to a string to iterate through digits.
     * 2. Approach: Iterate through the string; if a character is not '0', 
     * append it to a result string. Maintain a running sum of all digits.
     * 3. Why it Works: This directly simulates the problem statement constraints.
     * 4. Time Complexity (TC): O(D), where D is the number of digits in n.
     * 5. Space Complexity (SC): O(D) to store the string of non-zero digits.
     */
    long long sumAndMultiply(int n) {
        std::string s = std::to_string(n);
        std::string nonZeroDigits = "";
        long long digitSum = 0;
        
        for (char c : s) {
            if (c != '0') {
                nonZeroDigits += c;
            }
            digitSum += (c - '0');
        }
        
        // If nonZeroDigits is empty (e.g., n = 0, 10, 100), per problem constraints, return 0.
        if (nonZeroDigits.empty()) {
            return 0;
        }
        
        // Use stoll (string to long long) to prevent overflow for large inputs.
        long long concatenatedVal = std::stoll(nonZeroDigits);
        
        return concatenatedVal * digitSum;
    }
};

/*
Final Approach Explanation:
The chosen approach uses a single pass to collect non-zero digits and calculate 
the sum simultaneously. Storing the digits in a string and converting it to 
long long using stoll() ensures safety against potential integer overflows 
when the concatenated number is large.
*/

// Filename: 07-07-2026_LeetCode_Concatenate_Non-Zero_Digits_and_Multiply_by_Sum_I.cpp
