/*
Date: 22-06-2026
Problem Name: Maximum Number of Balloons
Platform: LeetCode
Difficulty: Easy
Tags: Hash Table, String, Counting

Problem Summary:
Given a string 'text', return the maximum number of instances of the word "balloon" 
that can be formed using the characters from 'text'. Each character can be used at most once.

Methods to Solve:
1. Frequency Counting (Optimal)

Method 1: Frequency Counting
- Intuition: To form the word "balloon", we need 1 'b', 1 'a', 2 'l's, 2 'o's, and 1 'n'. 
  We count the occurrences of these specific characters in the input string.
- Approach: Use a frequency array (or hash map) to store counts of all characters. 
  The limiting factor will be min(count['b'], count['a'], count['l']/2, count['o']/2, count['n']).
- Dry Run: text = "nlaebolko"
  b:1, a:1, l:2, o:2, n:1. Min(1, 1, 2/2, 2/2, 1) = 1.
- Time Complexity: O(N), where N is the length of the string.
- Space Complexity: O(1) (fixed size array of 26).
- When to use: When dealing with character frequency constraints.

Comparison Table:
Method             | TC    | SC   | Best Use Case
-------------------|-------|------|-------------------------
Frequency Counting | O(N)  | O(1) | Optimal for any string length

Final Recommended Solution: Frequency Counting
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

class Solution {
public:
    /**
     * Calculates the maximum number of "balloon" instances that can be formed.
     * * @param text The input string containing lowercase English letters.
     * @return The maximum number of "balloon" words.
     */
    int maxNumberOfBalloons(std::string text) {
        // Frequency array for lowercase English letters
        std::vector<int> counts(26, 0);
        
        for (char c : text) {
            counts[c - 'a']++;
        }
        
        // Requirements for "balloon": b:1, a:1, l:2, o:2, n:1
        int b = counts['b' - 'a'];
        int a = counts['a' - 'a'];
        int l = counts['l' - 'a'] / 2;
        int o = counts['o' - 'a'] / 2;
        int n = counts['n' - 'a'];
        
        // The result is constrained by the character with the minimum frequency
        return std::min({b, a, l, o, n});
    }
};
