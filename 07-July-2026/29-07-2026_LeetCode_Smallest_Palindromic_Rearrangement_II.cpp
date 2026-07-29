/*
=========================================================
Date        : 29-07-2026
Problem Name: 3518. Smallest Palindromic Rearrangement II
Platform    : LeetCode
Difficulty  : Hard
Tags        : Hash Table, Math, String, Combinatorics, Counting

Problem Summary:
Given a palindromic string and an integer k, find the k-th 
lexicographically smallest palindromic permutation of the string. 
If fewer than k permutations exist, return an empty string.

Key Observation:
Since it's a palindrome, we only need to construct the first 
half of the string and mirror it. We can find the k-th permutation 
by using combinatorics to count available arrangements at each step.
=========================================================

1. Combinatorics & Prefix Building (Most Optimal)
---------------------------------------------------------
* Intuition:
  Building the full string lexicographically is too slow. Instead, 
  we can build just the first half by deciding character by character,
  skipping permutations mathematically if they are fewer than k.

* Approach:
  - Count character frequencies and divide by 2 to get the pool for the first half.
  - Precompute combinations (nCr) up to length 5000, capping values at 10^6 + 5 to avoid overflow.
  - At each position, try placing characters 'a' to 'z'. If placing a character yields >= k remaining permutations, fix it. Otherwise, subtract the permutations from k and try the next character.

* Why it Works:
  By counting how many valid permutations exist for a chosen prefix, 
  we can decisively skip branches of the search space, effectively finding
  the k-th sequence in O(L * 26) time.

* Time Complexity (TC): 
  O(L^2) for precomputing combinations once + O(L * 26) per query, 
  where L = N/2 (approx 5000). Total time is fast and well within limits.

* Space Complexity (SC):
  O(L^2) to store the combinations DP table, which takes ~100MB, 
  plus O(1) for frequency maps.
*/

/*
=========================================================
FINAL APPROACH
=========================================================
The Combinatorics & Prefix Building approach is chosen because it avoids 
generating all permutations, effectively bypassing TLE. Precomputing 
capped combinations perfectly handles large factorial numbers safely.
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int INF = 1e6 + 5;
int C[5005][5005];
bool is_precomputed = false;

void precompute_nCr() {
    if (is_precomputed) return;
    for (int i = 0; i <= 5000; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
            if (C[i][j] > INF) C[i][j] = INF; 
        }
    }
    is_precomputed = true;
}

class Solution {
    long long calculate_permutations(const vector<int>& counts, int length) {
        long long ways = 1;
        int remaining_len = length;
        for (int c : counts) {
            if (c == 0) continue;
            ways = ways * C[remaining_len][c];
            if (ways > INF) return INF; 
            remaining_len -= c;
        }
        return ways;
    }

public:
    string smallestPalindrome(string s, int k) {
        precompute_nCr();
        
        vector<int> freq(26, 0);
        for (char c : s) {
            freq[c - 'a']++;
        }
        
        int odd_count = 0;
        char mid_char = 0;
        vector<int> half_pool(26, 0);
        
        for (int i = 0; i < 26; i++) {
            if (freq[i] % 2 != 0) {
                odd_count++;
                mid_char = i + 'a';
            }
            half_pool[i] = freq[i] / 2;
        }
        
        if (odd_count > 1) return "";
        
        int half_len = s.length() / 2;
        long long total_perms = calculate_permutations(half_pool, half_len);
        
        if (k > total_perms) return "";
        
        string half_str = "";
        for (int i = 0; i < half_len; i++) {
            for (int c = 0; c < 26; c++) {
                if (half_pool[c] > 0) {
                    half_pool[c]--;
                    
                    long long perms_in_branch = calculate_permutations(half_pool, half_len - 1 - i);
                    
                    if (k <= perms_in_branch) {
                        half_str += (char)(c + 'a');
                        break; 
                    } else {
                        k -= perms_in_branch;
                        half_pool[c]++; 
                    }
                }
            }
        }
        
        string result = half_str;
        if (odd_count == 1) {
            result += mid_char;
        }
        
        string rev_half = half_str;
        reverse(rev_half.begin(), rev_half.end());
        result += rev_half;
        
        return result;
    }
};
