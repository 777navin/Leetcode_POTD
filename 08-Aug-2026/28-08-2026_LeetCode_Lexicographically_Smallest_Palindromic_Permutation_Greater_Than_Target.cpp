/*
=========================================================
Date        : 28-08-2026
Problem Name: Lexicographically Smallest Palindromic Permutation Greater Than Target
Platform    : LeetCode (Problem 3734)
Difficulty  : Hard
Tags        : Two Pointers, String, Enumeration, Greedy, Backtracking

Problem Summary:
Given two lowercase strings 's' and 'target' of length 'n', find the 
lexicographically smallest string that is both a palindromic permutation 
of 's' and strictly greater than 'target'. If no such permutation exists, 
return an empty string "".

Key Observation:
A palindrome is completely determined by its first half (and optional middle character).
We can construct the first half greedily from left to right, branching into matching 
target's prefix, putting an strictly larger character at the first divergence, or mirroring.
=========================================================
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 1: Brute Force (Generate All Palindromic Permutations)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  - Generate all unique palindromic permutations of 's', sort them lexicographically,
    and find the first one strictly greater than 'target'.

• Approach:
  - Extract available character counts, determine the half-string multiset, and generate
    permutations using recursion or std::next_permutation.
  - Form the full palindromes, sort them, and binary search / scan for > target.

• Why it Works:
  - Explores the entire valid palindromic search space exhaustively.

• Time Complexity (TC) : O(((n/2)!) * n) - TLE for n up to 300.
• Space Complexity (SC): O(((n/2)!) * n) to store permutations.
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 2: Greedy Prefix Matching with Suffix Fill (Optimal)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  - To be strictly greater than target, the palindrome must either:
    1. Match target on the first m positions (0 <= m <= n/2) and place a larger char at position m,
       then fill the remaining positions in the first half with the smallest available characters.
    2. Exactly match target's first half, place an equal or strictly greater character in the middle
       (if n is odd), and verify if the mirrored right half strictly exceeds target's right half.

• Approach:
  - Count character frequencies of 's'. Verify palindrome validity (at most 1 odd frequency).
  - Find the longest matching prefix of the first half with 'target'.
  - Try to diverge at index i from (n/2 - 1) down to 0:
    - Pick the smallest character c > target[i] available in the remaining counts.
    - Greedily fill the rest of the first half with smallest available characters.
    - Assemble the full palindrome and return the first valid result found.
  - Also check the exact prefix match scenario where the middle or right half creates strict greatness.

• Why it Works:
  - Trying divergence points from rightmost to leftmost guarantees finding the lexicographically 
    smallest valid palindrome that strictly exceeds 'target'.

• Time Complexity (TC) : O(n * Σ) where Σ = 26 (Alphabet size), running in O(n) overall.
• Space Complexity (SC): O(n) to construct the result string.
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
FINAL APPROACH SELECTION:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Approach 2 is selected as it directly constructs the answer in linear time O(26 * n).
• It avoids generating exponential permutations and easily handles the constraints (n <= 300).
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.length();
        vector<int> count(26, 0);
        for (char c : s) {
            count[c - 'a']++;
        }

        int odd_count = 0;
        int odd_char = -1;
        for (int i = 0; i < 26; ++i) {
            if (count[i] % 2 != 0) {
                odd_count++;
                odd_char = i;
            }
        }

        // A valid palindromic permutation must have at most 1 odd character count
        if (odd_count > 1) return "";
        if (n % 2 == 0 && odd_count > 0) return "";

        int half_len = n / 2;
        vector<int> half_count(26, 0);
        for (int i = 0; i < 26; ++i) {
            half_count[i] = count[i] / 2;
        }

        auto build_palindrome = [&](const string& first_half) -> string {
            string res = first_half;
            if (n % 2 == 1) {
                res += (char)('a' + odd_char);
            }
            string second_half = first_half;
            reverse(second_half.begin(), second_half.end());
            res += second_half;
            return res;
        };

        // Case 1: First half is identical to target's first half
        bool can_match_prefix = true;
        vector<int> cur_half_count = half_count;
        string exact_half = "";

        for (int i = 0; i < half_len; ++i) {
            int c = target[i] - 'a';
            if (cur_half_count[c] > 0) {
                cur_half_count[c]--;
                exact_half += target[i];
            } else {
                can_match_prefix = false;
                break;
            }
        }

        if (can_match_prefix) {
            string p = build_palindrome(exact_half);
            if (p > target) {
                // If this minimal palindrome is strictly greater, it could be our candidate.
                // We'll see if there's any smaller valid one by checking divergence prefixes.
                // But divergence prefixes at index i will be >= target up to i, and strictly > at i.
                // Any divergence at i < half_len produces a string lexicographically greater than target[0..i-1] + (target[i]+1),
                // which is strictly greater than p where p matches target up to half_len.
                // Thus p is the optimal candidate if valid.
                return p;
            }
        }

        // Case 2: Diverge at position i (from half_len - 1 down to 0)
        for (int i = half_len - 1; i >= 0; --i) {
            // Recompute available characters for prefix target[0...i-1]
            vector<int> rem_count = half_count;
            bool valid_prefix = true;
            for (int j = 0; j < i; ++j) {
                int c = target[j] - 'a';
                if (rem_count[c] > 0) {
                    rem_count[c]--;
                } else {
                    valid_prefix = false;
                    break;
                }
            }
            if (!valid_prefix) continue;

            // Try to place smallest character strictly greater than target[i] at index i
            int target_char = target[i] - 'a';
            for (int c = target_char + 1; c < 26; ++c) {
                if (rem_count[c] > 0) {
                    rem_count[c]--;
                    string first_half = target.substr(0, i);
                    first_half += (char)('a' + c);

                    // Fill remainder greedily with smallest available characters
                    for (int k = 0; k < 26; ++k) {
                        while (rem_count[k] > 0) {
                            first_half += (char)('a' + k);
                            rem_count[k]--;
                        }
                    }

                    return build_palindrome(first_half);
                }
            }
        }

        return "";
    }
};
