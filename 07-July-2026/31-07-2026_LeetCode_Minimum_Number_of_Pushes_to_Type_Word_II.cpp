/*
=========================================================
Date        : 31-07-2026
Problem Name: Minimum Number of Pushes to Type Word II
Platform    : LeetCode
Difficulty  : Medium
Tags        : Hash Table, String, Greedy, Sorting, Counting

Problem Summary:
Given a string `word` consisting of lowercase English letters, we need to map characters to 
8 telephone keypad keys (keys 2 to 9). Each key can map to any number of letters, but each 
letter is assigned to exactly one key. We need to find the minimum total key pushes needed 
to type the string after remapping the keys.

Key Observation:
Letters with higher frequencies should be assigned to the first position of the keys to minimize 
pushes. Since 8 keys are available, the 8 most frequent letters require 1 push each, the next 
8 require 2 pushes each, the next 8 require 3 pushes each, and the remaining require 4 pushes each.
=========================================================
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
=========================================================
APPROACH 1: Frequency Counting + Sorting (Optimal)
=========================================================

• Intuition:
  To minimize the overall pushes, we should give priority to high-frequency letters by 
  assigning them to single-push key positions. Letters appearing less frequently can be 
  placed in multi-push positions.

• Approach:
  1. Count the frequency of each lowercase letter in the string using a frequency array of size 26.
  2. Sort the frequencies in descending order.
  3. Iterate through the sorted frequencies and calculate the required pushes:
     - The first 8 letters take 1 push each (index 0 to 7 -> (i / 8) + 1 = 1).
     - The next 8 letters take 2 pushes each (index 8 to 15 -> (i / 8) + 1 = 2).
     - The next 8 letters take 3 pushes each (index 16 to 23 -> (i / 8) + 1 = 3).
     - The remaining letters take 4 pushes each (index 24 to 25 -> (i / 8) + 1 = 4).
  4. Sum up (frequency * pushes) for all characters to get the answer.

• Why it Works:
  This greedy strategy guarantees the minimal total pushes because it minimizes the coefficient 
  (pushes per letter) for the largest terms (frequencies) in the sum.

• Time Complexity (TC):
  O(N) where N is the length of the string `word` to compute character frequencies. 
  Sorting an array of fixed size 26 takes O(1) time. Overall TC: O(N).

• Space Complexity (SC):
  O(1) auxiliary space, as the frequency array size is fixed at 26 for lowercase English letters.
*/

/*
=========================================================
FINAL APPROACH SELECTION
=========================================================
• Why this approach is chosen:
  It directly leverages the greedy choice property by sorting character frequencies.
• Why it is better than previous ones:
  This is already the optimal solution with O(N) time and O(1) extra space, making it both 
  time-efficient and space-optimal.
=========================================================
*/

class Solution {
public:
    int minimumPushes(string word) {
        vector<int> freq(26, 0);
        
        // Count frequency of each letter
        for (char c : word) {
            freq[c - 'a']++;
        }
        
        // Sort frequencies in descending order
        sort(freq.rbegin(), freq.rend());
        
        int totalPushes = 0;
        
        // Calculate total pushes required
        for (int i = 0; i < 26; ++i) {
            if (freq[i] == 0) break; // No more letters present
            
            int pushes = (i / 8) + 1;
            totalPushes += freq[i] * pushes;
        }
        
        return totalPushes;
    }
};
