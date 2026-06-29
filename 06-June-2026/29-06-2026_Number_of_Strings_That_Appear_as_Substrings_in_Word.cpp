/*
Date: 29-06-2026
Problem Name: Number of Strings That Appear as Substrings in Word
Platform: LeetCode
Difficulty: Easy
Tags: Array, String

Problem Summary:
Given an array of strings 'patterns' and a string 'word', 
count the number of strings in 'patterns' that exist as a substring in 'word'.

Methods to Solve:
1. Brute Force (Using find())
2. Using STL Search (count_if)

For EACH method include:

- Intuition: Check each pattern one by one to see if it exists within the 'word'.
- Approach: Iterate through the 'patterns' vector. For each pattern, use string::find(). If the result is not string::npos, increment the counter.
- Dry Run (small example):
  patterns = ["a","abc","bc","d"], word = "abc"
  - "a" in "abc"? Yes. (Count = 1)
  - "abc" in "abc"? Yes. (Count = 2)
  - "bc" in "abc"? Yes. (Count = 3)
  - "d" in "abc"? No.
  Result: 3
- Time Complexity: O(N * M * K) where N = number of patterns, M = length of word, K = max length of a pattern.
- Space Complexity: O(1) auxiliary space.

Comparison Table:
Method | TC | SC | Best Use Case
Brute Force | O(N*M*K) | O(1) | General purpose
STL count_if | O(N*M*K) | O(1) | Clean, readable code

Final Recommended Solution: Method 1 (Simple loop with find)
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    /**
     * Method 1: Iterative search
     * Checks each string in patterns to see if it exists in word.
     */
    int numOfStrings(vector<string>& patterns, string word) {
        int count = 0;
        for (const string& pattern : patterns) {
            // string::find returns the index or string::npos if not found
            if (word.find(pattern) != string::npos) {
                count++;
            }
        }
        return count;
    }

    /**
     * Method 2: Functional approach
     * Uses std::count_if for cleaner, more modern C++ style.
     */
    int numOfStringsFunctional(vector<string>& patterns, string word) {
        return count_if(patterns.begin(), patterns.end(), [&](const string& p) {
            return word.find(p) != string::npos;
        });
    }
};

// Example usage
int main() {
    Solution sol;
    vector<string> patterns = {"a", "abc", "bc", "d"};
    string word = "abc";
    
    cout << "Number of substrings found: " << sol.numOfStrings(patterns, word) << endl;
    
    return 0;
}
