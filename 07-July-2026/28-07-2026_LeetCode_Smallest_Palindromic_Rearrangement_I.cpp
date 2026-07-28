/*
=========================================================
Date        : 28-07-2026
Problem Name: Smallest Palindromic Rearrangement I
Platform    : LeetCode
Difficulty  : Medium
Tags        : String, Greedy, Counting Sort, Two Pointers

Problem Summary:
Given a string 's' that can be rearranged into a palindrome,
find the lexicographically smallest palindromic permutation of 's'.

Key Observation:
Since we need the lexicographically smallest palindrome, we must place 
the smallest characters at the beginning (and symmetrically at the end).
Counting character frequencies allows us to greedily construct the string.
=========================================================
*/

/*
=========================================================
APPROACH 1: Brute Force (Generate Permutations)
=========================================================
* Intuition: Try all possible arrangements of the string and find the smallest palindrome.
* Approach: Sort the string, then generate all permutations. The first valid palindrome found is the answer.
* Why it Works: Sorting guarantees we check permutations in lexicographically increasing order.
* Time Complexity (TC): O(N * N!) - Generating all permutations and checking each takes factorial time. (Will TLE)
* Space Complexity (SC): O(1) - In-place generation.

=========================================================
APPROACH 2: Better (Frequency Array + String Concatenation)
=========================================================
* Intuition: A palindrome is mirrored. We only need to construct the left half.
* Approach: Count frequencies of characters. Build a 'left' string using half the count of each char from 'a' to 'z'. Extract the single odd-count char for the 'middle'. Reverse 'left' to get 'right'. Return left + middle + right.
* Why it Works: Building 'left' in alphabetical order guarantees the lexicographically smallest result.
* Time Complexity (TC): O(N) - One pass to count, and string building takes linear time.
* Space Complexity (SC): O(N) - Creating separate left, middle, and right strings requires extra space.

=========================================================
APPROACH 3: Most Optimal (Two Pointers In-Place Construction)
=========================================================
* Intuition: We can avoid creating temporary strings and concatenations by pre-allocating the final string.
* Approach: Create a string of size N filled with spaces. Use two pointers (start and end). Iterate from 'a' to 'z', placing pairs of characters at the pointers and moving inward. Place the odd character exactly in the middle.
* Why it Works: Directly assigning characters to their final indices avoids dynamic memory overhead and string copies.
* Time Complexity (TC): O(N) - We traverse the string once to count and once to fill it.
* Space Complexity (SC): O(1) - Auxiliary space is constant (size 26 frequency array). The string returned is part of the output.
*/

/*
=========================================================
FINAL APPROACH CHOSEN: Most Optimal (Two Pointers In-Place)
=========================================================
* We choose the Two Pointers approach because it avoids the overhead 
* of creating multiple temporary strings (left/right) and concatenating them. 
* It operates directly on a single pre-allocated string, making it the most 
* memory-efficient and fastest O(N) solution.
=========================================================
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    string smallestPalindrome(string s) {
        int n = s.size();
        
        // Step 1: Count character frequencies
        vector<int> count(26, 0);
        for (char c : s) {
            count[c - 'a']++;
        }
        
        // Step 2: Pre-allocate the final string to avoid concatenations
        string ans(n, ' '); 
        int left = 0;           
        int right = n - 1;      
        
        // Step 3: Fill characters greedily from 'a' to 'z'
        for (int i = 0; i < 26; i++) {
            char ch = i + 'a';
            
            // If the character frequency is odd, place one in the exact middle
            if (count[i] % 2 != 0) {
                ans[n / 2] = ch;
                count[i]--; // Decrement so the rest can be placed symmetrically
            }
            
            // Place the remaining characters symmetrically from ends towards the center
            while (count[i] > 0) {
                ans[left] = ch;
                ans[right] = ch;
                
                left++;
                right--;
                count[i] -= 2;
            }
        }
        
        return ans;
    }
};
