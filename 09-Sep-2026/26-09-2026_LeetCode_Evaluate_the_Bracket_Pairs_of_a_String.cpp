/*
=========================================================
Date        : 26-09-2026
Problem Name: Evaluate the Bracket Pairs of a String
Platform    : LeetCode
Difficulty  : Medium
Tags        : Array, Hash Table, String

Problem Summary:
Given a string s containing bracket pairs and a 2D array knowledge 
containing key-value pairs, evaluate all bracket pairs by replacing 
each key with its corresponding value. If the key is not in knowledge, 
replace it with '?'.

Key Observation:
Use an unordered_map (hash table) to store key-value pairs for O(1) 
lookups, then iterate through the string once while building the result.
=========================================================
*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

/*
---------------------------------------------------------
APPROACH 1: Hash Map + String Parsing
---------------------------------------------------------
• Intuition:
  - We need fast lookups for keys encountered between '(' and ')'.
  - Preprocessing 'knowledge' into a hash map provides average O(1) lookup time per key.

• Approach:
  - Insert all key-value pairs from 'knowledge' into an unordered_map.
  - Traverse string s character by character using a result buffer.
  - When '(' is encountered, extract the key until ')' and look it up in the map.
  - Append either the found value or '?' to the result buffer.

• Why it Works:
  - Hash map allows constant time retrieval of values for keys.
  - Non-nested brackets ensure a single sequential pass can correctly parse every bracket pair.

• Time Complexity (TC):
  - O(N + K), where N is the length of string s and K is the total number of characters in knowledge.

• Space Complexity (SC):
  - O(K) to store the hash map and O(N) for the resulting output string.
---------------------------------------------------------
*/

/*
=========================================================
FINAL APPROACH SELECTION
=========================================================
• This Hash Map + String Parsing approach is chosen because it 
  achieves linear time complexity O(N + K) and single-pass traversal.
• It is optimal since every character in s and knowledge must 
  be processed at least once.
=========================================================
*/

class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> mp;
        for (const auto& kv : knowledge) {
            mp[kv[0]] = kv[1];
        }

        string result = "";
        int n = s.length();
        int i = 0;

        while (i < n) {
            if (s[i] == '(') {
                i++;
                string key = "";
                while (i < n && s[i] != ')') {
                    key += s[i];
                    i++;
                }
                i++; // Skip ')'
                
                auto it = mp.find(key);
                if (it != mp.end()) {
                    result += it->second;
                } else {
                    result += '?';
                }
            } else {
                result += s[i];
                i++;
            }
        }

        return result;
    }
};
