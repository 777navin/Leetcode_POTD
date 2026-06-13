/*
Date: 13-06-2026
Problem Name: Weighted Word Mapping
Platform: LeetCode
Difficulty: Easy
Tags: Array, String, Simulation

Problem Summary:
Given an array of strings 'words' and an array of 26 integers 'weights', calculate the weight 
of each word as the sum of its character weights. Then, map (weight % 26) to a character 
using reverse alphabetical order (0 -> 'z', 1 -> 'y', ..., 25 -> 'a'). Return the 
concatenated string of these mapped characters.

Methods to Solve:
1. Direct Simulation:
   - Intuition: Iterate through each word, sum the weights of its characters, apply modulo 26, 
     and map to the corresponding character.
   - Approach: For each word, initialize `sum = 0`. For each character `c`, add `weights[c - 'a']` 
     to `sum`. Calculate `mapped = sum % 26`. The target character is `'z' - mapped`.
   - Dry Run: "abcd" with weights [5,3,12,14...]. Sum = 5+3+12+14 = 34. 34 % 26 = 8. 
     'z' - 8 = 'r'.
   - Time Complexity: O(N * L), where N is the number of words and L is the max length of a word.
   - Space Complexity: O(N) to store the result string.
   - Why better: This is the optimal approach as we must process every character at least once.
   - When to use: Always, as it is simple and efficient.

Comparison Table:
Method | TC | SC | Best Use Case
-------|----|----|--------------
Simulation | O(N*L) | O(N) | General purpose

Final Recommended Solution: Simulation
*/

#include <iostream>
#include <vector>
#include <string>

class Solution {
public:
    /**
     * @brief Maps words to characters based on weighted sums.
     * * @param words Vector of input strings.
     * @param weights Vector of 26 integers representing character weights.
     * @return A string formed by concatenating the mapped characters.
     */
    std::string mapWordWeights(std::vector<std::string>& words, std::vector<int>& weights) {
        std::string result = "";
        
        for (const std::string& word : words) {
            long long current_weight_sum = 0;
            
            // Calculate total weight of the word
            for (char c : word) {
                current_weight_sum += weights[c - 'a'];
            }
            
            // Determine mapping index
            int mapped_val = current_weight_sum % 26;
            
            // Map 0 -> 'z', 1 -> 'y', ..., 25 -> 'a'
            char mapped_char = 'z' - mapped_val;
            
            result += mapped_char;
        }
        
        return result;
    }
};
