/*
Date: 04-06-2026
Problem Name: Total Waviness of Numbers in Range I
Platform: LeetCode
Difficulty: Medium
Tags: Math, Dynamic Programming, Enumeration

Problem Summary:
Given an inclusive range [num1, num2], calculate the total "waviness" of all numbers in the range. 
A number's waviness is the count of its peaks and valleys.
- Peak: Digit strictly greater than both neighbors.
- Valley: Digit strictly less than both neighbors.
- First and last digits cannot be peaks or valleys.
- Numbers with fewer than 3 digits have a waviness of 0.

Methods to Solve:
1. Brute Force (Iterative)
2. Digit DP (Optimal for larger constraints)

For Method 1 (Brute Force):
- Intuition: Iterate through every number from num1 to num2, convert to string/digits, and check each digit (index 1 to len-2) to see if it satisfies the peak or valley condition.
- Approach: Loop from num1 to num2. For each number, check digits at i where 1 <= i < len-1. Increment count if digits[i-1] < digits[i] > digits[i+1] (peak) or digits[i-1] > digits[i] < digits[i+1] (valley).
- Time Complexity: O(N * D), where N is the range size and D is the number of digits.
- Space Complexity: O(D) to store digits.
- Why better: Simple to implement for the given constraints (num <= 10^5).
- When to use: When constraints are small.

For Method 2 (Digit DP):
- Intuition: If constraints were larger (e.g., 10^18), we would use Digit DP to count waviness by processing digits position by position.
- Time Complexity: O(D * 10 * 10 * 2 * 2), where D is the number of digits.
- Space Complexity: O(D * 10 * 10 * 2 * 2).

Comparison Table:
Method | TC | SC | Best Use Case
-------|----|----|--------------
Brute Force | O(N*D) | O(D) | Small ranges (e.g., 10^5)
Digit DP | O(D) | O(D) | Large ranges (e.g., 10^18)

Final Recommended Solution: Brute Force (due to N <= 10^5)
*/

#include <iostream>
#include <vector>
#include <string>

class Solution {
public:
    /**
     * Calculates the total waviness in range [num1, num2].
     * Given the constraint num2 <= 10^5, a direct iteration is efficient.
     */
    int totalWaviness(int num1, int num2) {
        int totalWavinessSum = 0;
        
        for (int i = num1; i <= num2; ++i) {
            totalWavinessSum += getWaviness(i);
        }
        
        return totalWavinessSum;
    }

private:
    int getWaviness(int n) {
        std::string s = std::to_string(n);
        int len = s.length();
        
        if (len < 3) return 0;
        
        int count = 0;
        // Check digits from index 1 to len-2 (excluding first and last)
        for (int i = 1; i < len - 1; ++i) {
            int prev = s[i - 1] - '0';
            int curr = s[i] - '0';
            int next = s[i + 1] - '0';
            
            // Peak condition
            if (curr > prev && curr > next) {
                count++;
            }
            // Valley condition
            else if (curr < prev && curr < next) {
                count++;
            }
        }
        return count;
    }
};
