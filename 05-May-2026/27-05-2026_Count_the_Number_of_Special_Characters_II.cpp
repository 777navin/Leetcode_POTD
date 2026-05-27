/*
Date: 27-05-2026
Problem Name: 3121. Count the Number of Special Characters II
Platform: LeetCode
Difficulty: Medium
Tags: Hash Table, String

Problem Summary:
You are given a string `word`. A letter is considered "special" if it appears in both lowercase and uppercase in `word`, AND every occurrence of its lowercase form appears strictly before the first occurrence of its uppercase form. Return the total count of special letters.

Methods to Solve:
1. Brute Force (String Search)
2. Better Approach (Index Tracking / Two-Pass)
3. Optimal Approach (State Machine / One-Pass)

For EACH method include:

Method 1: Brute Force (String Search)
- Intuition: For every character from 'a' to 'z', find the last occurrence of its lowercase version and the first occurrence of its uppercase version using built-in string search functions.
- Approach: Loop through 26 characters. Use `word.rfind()` for the lowercase character and `word.find()` for the uppercase character. Check if both exist and if the lowercase index is strictly less than the uppercase index.
- Dry Run (word = "aaAbcBC"):
  - 'a': last 'a' at idx 1, first 'A' at idx 2. Valid.
  - 'b': last 'b' at idx 3, first 'B' at idx 5. Valid.
  - 'c': last 'c' at idx 4, first 'C' at idx 6. Valid.
- Time Complexity: O(26 * N) = O(N) where N is the length of the string.
- Space Complexity: O(1)
- Why better than previous method: N/A (Baseline).
- When to use: When you want to write the quickest, shortest code using built-in library functions, though it traverses the string multiple times.

Method 2: Better Approach (Index Tracking / Two-Pass)
- Intuition: Instead of searching the string 26 times, we can traverse the string once to record the last seen index of every lowercase letter and the first seen index of every uppercase letter.
- Approach: Create two arrays `lastLower` and `firstUpper` of size 26 initialized to -1. Loop through `word` to populate them. Finally, loop through the 26 indices to check the condition `lastLower[i] < firstUpper[i]`.
- Dry Run (word = "AbBCab"):
  - 'A' seen at 0 -> firstUpper['a'] = 0
  - 'b' seen at 1 -> lastLower['b'] = 1
  - 'B' seen at 2 -> firstUpper['b'] = 2
  - 'C' seen at 3 -> firstUpper['c'] = 3
  - 'a' seen at 4 -> lastLower['a'] = 4
  - 'b' seen at 5 -> lastLower['b'] = 5
  - Check 'b': lastLower is 5, firstUpper is 2. 5 < 2 is False. Invalid.
- Time Complexity: O(N)
- Space Complexity: O(1)
- Why better than previous method: Only requires a single full string traversal to build the maps, significantly reducing constant factors compared to 26 string searches.
- When to use: When you prefer clear logic relying on index boundaries.

Method 3: Optimal Approach (State Machine / One-Pass)
- Intuition: We don't actually need to store indices; we only need to track the "validity state" of each of the 26 characters as we scan the string from left to right.
- Approach: Maintain a state array for 26 characters:
  -  0: Not seen yet
  -  1: Only lowercase seen (currently valid)
  -  2: Valid uppercase seen (lowercase was seen before it)
  - -1: Invalidated (uppercase appeared before lowercase, or lowercase appeared after uppercase)
  Traverse the string. Update states based on whether we see a lowercase or uppercase character. Finally, count how many characters ended up in state 2.
- Dry Run (word = "aaAbcBC"):
  - 'a' -> state['a'] = 1
  - 'a' -> state['a'] = 1
  - 'A' -> state['a'] = 2
  - 'b' -> state['b'] = 1
  - 'c' -> state['c'] = 1
  - 'B' -> state['b'] = 2
  - 'C' -> state['c'] = 2
  - Final count of state 2 is 3.
- Time Complexity: O(N)
- Space Complexity: O(1)
- Why better than previous method: Processes validity in a pure single pass without needing secondary comparisons of index values. Most elegant and uses minimal space.
- When to use: In technical interviews to demonstrate optimal state-tracking capabilities.

Comparison Table:
Method               | TC   | SC   | Best Use Case
-------------------------------------------------------
1. Brute Force       | O(N) | O(1) | Quick scripting
2. Index Tracking    | O(N) | O(1) | Standard array tracking
3. State Machine     | O(N) | O(1) | Production-ready one-pass execution

Final Recommended Solution: Method 3 (State Machine) for its clean logic and true one-pass nature.
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    // Method 2: Index Tracking Approach (Provided for reference)
    int solveIndexTracking(string word) {
        vector<int> lastLower(26, -1);
        vector<int> firstUpper(26, -1);

        for (int i = 0; i < word.length(); i++) {
            if (islower(word[i])) {
                lastLower[word[i] - 'a'] = i;
            } else {
                if (firstUpper[word[i] - 'A'] == -1) {
                    firstUpper[word[i] - 'A'] = i;
                }
            }
        }

        int count = 0;
        for (int i = 0; i < 26; i++) {
            if (lastLower[i] != -1 && firstUpper[i] != -1 && lastLower[i] < firstUpper[i]) {
                count++;
            }
        }
        return count;
    }

    // Method 3: State Machine Approach (Optimal)
    int solveStateMachine(string word) {
        // States:
        //  0: Unseen
        //  1: Lowercase seen (Valid so far)
        //  2: Uppercase seen after lowercase (Valid special character)
        // -1: Invalid (Upper before lower, or lower after upper)
        vector<int> state(26, 0);

        for (char c : word) {
            if (islower(c)) {
                int idx = c - 'a';
                if (state[idx] == 0) {
                    state[idx] = 1; 
                } else if (state[idx] == 2) {
                    // Lowercase appearing AFTER an uppercase invalidates the character
                    state[idx] = -1;
                }
            } else {
                int idx = c - 'A';
                if (state[idx] == 0) {
                    // Uppercase appearing BEFORE any lowercase invalidates it
                    state[idx] = -1;
                } else if (state[idx] == 1) {
                    // First valid uppercase after a lowercase
                    state[idx] = 2;
                }
                // If state is already 2 or -1, we do nothing.
            }
        }

        int specialCount = 0;
        for (int s : state) {
            if (s == 2) {
                specialCount++;
            }
        }
        
        return specialCount;
    }

    // LeetCode Driver Method
    int numberOfSpecialChars(string word) {
        return solveStateMachine(word);
    }
};
