/*
=========================================================
Date        : 13-07-2026
Problem Name: 1291. Sequential Digits
Platform    : LeetCode
Difficulty  : Medium
Tags        : Enumeration, Sliding Window

Problem Summary:
An integer has sequential digits if each digit is exactly one more than the 
previous digit. Given a range [low, high], find and return a sorted list of 
all such sequential integers within this range inclusive.

Key Observation:
Since the digits must be sequential and increasing, all possible sequential 
digits are substrings of the template string "123456789". The maximum number 
of such integers is highly constrained (only 36 total combinations).
=========================================================
*/

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/*
=========================================================
APPROACH 1: Enumeration via Sliding Window (Optimized)
=========================================================
• Intuition:
  All sequential digits are fixed patterns depending on their length. We can 
  generate all valid sequential numbers by treating the string "123456789" 
  as a source and extracting substrings of varying lengths.

• Approach:
  - Loop through all possible lengths of numbers from the length of `low` to 
    the length of `high`.
  - For each length, use a sliding window over the string "123456789" to 
    extract substrings, convert them to integers, and check if they fall 
    within the range `[low, high]`.

• Why it Works:
  Since sequential numbers must strictly follow the `123...` progression, 
  generating them directly from the digits template guarantees that every 
  number generated is valid by definition, and they are inherently generated 
  in sorted order.

• Time Complexity (TC):
  O(1) - The number of digits is fixed (1 to 9). The nested loops run a maximum 
  of 36 times regardless of the input values.

• Space Complexity (SC):
  O(1) - Excluding the output list, only a few variables and temporary string 
  slices are used.
*/

/*
=========================================================
FINAL APPROACH CHOICE
=========================================================
The Enumeration/Sliding Window approach is chosen because the entire search 
space is mathematically bounded and exceptionally small (at most 36 possible 
sequential numbers between 10 and 10^9). It is optimally efficient, runs in 
constant time O(1), guarantees sorted order naturally, and avoids unnecessary 
recursive overhead.
*/

class Solution {
public:
    vector<int> sequentialDigits(int low, int high) {
        vector<int> result;
        string digits = "123456789";
        
        int lowLen = to_string(low).length();
        int highLen = to_string(high).length();
        
        // Iterate through all possible lengths within the range boundary lengths
        for (int length = lowLen; length <= highLen; ++length) {
            // Slide a window of 'length' over the digits string
            for (int start = 0; start <= 9 - length; ++start) {
                string sub = digits.substr(start, length);
                int num = stoi(sub);
                
                // Collect the number if it fits the range constraints
                if (num >= low && num <= high) {
                    result.push_back(num);
                }
            }
        }
        
        return result;
    }
};
