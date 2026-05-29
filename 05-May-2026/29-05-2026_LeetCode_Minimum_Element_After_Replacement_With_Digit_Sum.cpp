/*
Date: 29-05-2026
Problem Name: 3300. Minimum Element After Replacement With Digit Sum
Platform: LeetCode
Difficulty: Easy
Tags: Array, Math

Problem Summary:
You are given an integer array `nums`. You must replace each element in the array with the sum of its individual digits. The objective is to return the minimum element found in the array after all replacements are completed.

Methods to Solve:
1. String Conversion Approach
2. Optimal Mathematical Approach

For EACH method include:

---------------------------------------------------------
Method 1: String Conversion Approach
- Intuition: The most straightforward way to isolate digits is by converting the integer into a string format and processing each character individually.
- Approach: Iterate through the array. For each number, convert it to a `std::string`. Iterate through the characters of the string, subtract the ASCII value of '0' to get the integer digit, and keep a running sum. Track the minimum sum across all numbers.
- Dry Run (small example):
    Input: nums = [10, 12]
    - '10' -> '1' - '0' = 1, '0' - '0' = 0. Sum = 1. min_val = 1.
    - '12' -> '1' - '0' = 1, '2' - '0' = 2. Sum = 3. min_val = 1.
    Result = 1
- Time Complexity: O(N * D) where N is the number of elements in `nums` and D is the number of digits in the largest element.
- Space Complexity: O(D) to store the string representation of each number during the iteration.
- Why better than previous method: N/A (Baseline brute-force approach).
- When to use: When working in languages or constraints where string manipulation is safer or mathematical operations overflow (not an issue here).

---------------------------------------------------------
Method 2: Optimal Mathematical Approach
- Intuition: Extracting digits mathematically using the modulo (`%`) and division (`/`) operators is much faster and entirely avoids the overhead of dynamic memory allocation required by strings.
- Approach: Initialize `min_val` to `INT_MAX`. Iterate through each number. Use a `while` loop to extract the last digit (`num % 10`), add it to a local sum, and truncate the number (`num /= 10`). Update `min_val` with the minimum between itself and the local sum.
- Dry Run (small example):
    Input: nums = [10, 12]
    - num = 10: 10 % 10 = 0 -> 10 / 10 = 1 -> 1 % 10 = 1 -> 1 / 10 = 0. Sum = 1. min_val = 1.
    - num = 12: 12 % 10 = 2 -> 12 / 10 = 1 -> 1 % 10 = 1 -> 1 / 10 = 0. Sum = 3. min_val = 1.
    Result = 1
- Time Complexity: O(N * D) where N is the number of elements and D is the maximum number of digits. Modulo/division operations run significantly faster at the CPU level than string allocations.
- Space Complexity: O(1) strictly, as we only use primitive integer variables for counting.
- Why better than previous method: Zero memory allocation overhead, leading to a much faster execution time.
- When to use: This is the industry-standard and most optimal way to process digits of an integer in C++.

Comparison Table:
Method                      | TC       | SC   | Best Use Case
-----------------------------------------------------------------------------------
1. String Conversion        | O(N * D) | O(D) | When code readability is favored over strict performance.
2. Optimal Mathematical     | O(N * D) | O(1) | Competitive programming and production environments.

Final Recommended Solution: Method 2 (Optimal Mathematical Approach)
*/

#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    // Method 1: String Conversion Approach
    int minElement_stringConversion(vector<int>& nums) {
        int min_val = INT_MAX;
        
        for (int num : nums) {
            string s = to_string(num);
            int current_sum = 0;
            
            for (char c : s) {
                current_sum += (c - '0');
            }
            
            min_val = min(min_val, current_sum);
        }
        
        return min_val;
    }

    // Method 2: Optimal Mathematical Approach (Recommended)
    int minElement(vector<int>& nums) {
        int min_val = INT_MAX;
        
        for (int num : nums) {
            int current_sum = 0;
            int temp = num;
            
            // Extract and sum digits mathematically
            while (temp > 0) {
                current_sum += temp % 10;
                temp /= 10;
            }
            
            // Track the minimum digit sum found so far
            min_val = min(min_val, current_sum);
        }
        
        return min_val;
    }
};
