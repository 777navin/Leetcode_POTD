/*
Date: 11-05-2026
Problem Name: Separate the Digits in an Array
Platform: LeetCode (Problem #2553)
Difficulty: Easy
Tags: Array, Simulation, Math

Problem Summary:
Given an array of positive integers 'nums', return an array 'answer' that consists 
of the digits of each integer in 'nums' in the same order they appear.

Methods to Solve:
1. String Conversion (Simpler Implementation)
2. Mathematical Extraction (Optimal Memory)

---------------------------------------------------------------------------
1. String Conversion
- Intuition: Convert each integer to a string to easily access each digit character-by-character.
- Approach: Iterate through the array. For each number, convert it to a string, 
  loop through the string, and push the integer value of each character into the result.
- Dry Run: nums = [13, 25]
  - 13 -> "13" -> result: [1, 3]
  - 25 -> "25" -> result: [1, 3, 2, 5]
- Time Complexity: O(n * k), where n is the size of nums and k is the average number of digits.
- Space Complexity: O(k) for the temporary string storage (excluding result array).
- Why better than previous method: N/A (Baseline).
- When to use: When implementation speed and readability are prioritized.

---------------------------------------------------------------------------
2. Mathematical Extraction (Optimal)
- Intuition: Use modulo (%) and division (/) to extract digits without string overhead.
- Approach: For each number, extract digits from right to left using 'num % 10'. 
  Store these in a temporary vector, reverse it to get the correct order, and append to the result.
- Dry Run: nums = [13]
  - 13 % 10 = 3, 13 / 10 = 1
  - 1 % 10 = 1, 1 / 10 = 0
  - Temp: [3, 1] -> Reverse: [1, 3] -> Result: [1, 3]
- Time Complexity: O(n * k).
- Space Complexity: O(k) for the temporary vector (excluding result array).
- Why better than previous method: Avoids the overhead of string object creation and memory allocation.
- When to use: In memory-constrained environments or high-performance competitive programming.

Comparison Table:
Method                  | TC       | SC       | Best Use Case
---------------------------------------------------------------------------
String Conversion       | O(n * k) | O(k)     | Rapid prototyping
Mathematical Extraction | O(n * k) | O(k)     | Memory efficiency / Interview optimal

Final Recommended Solution: Mathematical Extraction for its clean logic and efficiency.
*/

#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class Solution {
public:
    /**
     * @brief Separates digits using the Mathematical Extraction approach.
     * This is generally preferred in interviews to show understanding of numeric manipulation.
     */
    vector<int> separateDigits(vector<int>& nums) {
        vector<int> result;
        
        for (int num : nums) {
            // Temporary storage to hold digits in reverse order
            vector<int> currentDigits;
            
            while (num > 0) {
                currentDigits.push_back(num % 10);
                num /= 10;
            }
            
            // Reverse the digits to maintain original order [e.g., 13 -> 3,1 -> 1,3]
            reverse(currentDigits.begin(), currentDigits.end());
            
            // Insert into the final result vector
            result.insert(result.end(), currentDigits.begin(), currentDigits.end());
        }
        
        return result;
    }

    /**
     * @brief Alternative approach using String Conversion.
     * Included for completeness as per rule #6.
     */
    vector<int> separateDigitsString(vector<int>& nums) {
        vector<int> result;
        for (int num : nums) {
            string s = to_string(num);
            for (char c : s) {
                result.push_back(c - '0'); // Convert char digit to int
            }
        }
        return result;
    }
};
