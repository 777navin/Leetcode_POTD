/*
=========================================================
Date        : 08-07-2026
Problem Name: 3756. Concatenate Non-Zero Digits and Multiply by Sum II
Platform    : LeetCode
Difficulty  : Medium
Tags        : Math, String, Prefix Sum

Problem Summary:
Given a string s consisting of digits and a series of queries [L, R]. For each query, 
form an integer x by concatenating all non-zero digits in s[L..R] in order, and 
calculate the total sum of these digits. Return (x * sum) % (10^9 + 7).

Key Observation:
Instead of dealing with zeros, we can map original string indices to an array containing 
only non-zero digits. Substring values can then be retrieved using prefix hashes/math 
and precomputed powers of 10 modulo 10^9 + 7.
=========================================================
*/

#include <vector>
#include <string>

using namespace std;

/*
---------------------------------------------------------
Approach 1: Optimized Prefix Hash and Mapping (Most Optimal)
---------------------------------------------------------
• Intuition:
  Iterating through the substring for each query is too slow due to O(M * Q). We need an O(1) 
  method to extract the concatenated non-zero integer and its sum. By compressing the string to 
  ignore '0's, we can use prefix sums for the digit sum and a positional prefix-value array 
  (similar to rolling hash) to get any subarray value in constant time.

• Approach:
  1. Filter out all non-zero characters, tracking their original indices, digit sums, and 
     prefix numeric values modulo 10^9 + 7.
  2. Maintain two mapping arrays: `next_nz[i]` (index of the first non-zero digit at or after `i`) 
     and `prev_nz[i]` (index of the last non-zero digit at or before `i`).
  3. For each query `[L, R]`, find the mapped bounds in our non-zero arrays using `next_nz[L]` 
     and `prev_nz[R]`. If no valid non-zero elements exist, return 0.
  4. Compute the value of the non-zero substring using: 
     val = (pref_val[r + 1] - (pref_val[l] * pow10[r - l + 1]) % MOD + MOD) % MOD.
  5. Compute the sum using `pref_sum[r + 1] - pref_sum[l]`.

• Why it Works:
  Standard prefix range retrieval gives us the exact value of the slice from the non-zero array, 
  and multiplying the left prefix by $10^{\text{len}}$ aligns the digits perfectly for subtraction.

• Time Complexity (TC) : O(M + Q) - Precomputation takes O(M) and each query is processed in O(1).
• Space Complexity (SC): O(M) - To store prefix values, prefix sums, power arrays, and mapping tables.
*/

/*
=========================================================
Final Approach Choice:
This approach is chosen because the constraints (M, Q <= 10^5) strictly prohibit any 
linear scanning per query. Precomputing the positional mapping and utilizing prefix math 
guarantees optimal performance, passing well within time boundaries.
=========================================================
*/

class Solution {
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        int m = s.length();
        long long MOD = 1e9 + 7;
        
        // Filter and collect non-zero details
        vector<int> digits;
        vector<int> orig_idx;
        for (int i = 0; i < m; ++i) {
            if (s[i] != '0') {
                digits.push_back(s[i] - '0');
                orig_idx.push_back(i);
            }
        }
        
        int n = digits.size();
        vector<long long> pref_sum(n + 1, 0);
        vector<long long> pref_val(n + 1, 0);
        vector<long long> pow10(n + 1, 1);
        
        for (int i = 0; i < n; ++i) {
            pref_sum[i + 1] = pref_sum[i] + digits[i];
            pref_val[i + 1] = (pref_val[i] * 10 + digits[i]) % MOD;
            pow10[i + 1] = (pow10[i] * 10) % MOD;
        }
        
        // Map original positions to non-zero array indices
        vector<int> next_nz(m, -1);
        int last = -1;
        for (int i = m - 1; i >= 0; --i) {
            if (s[i] != '0') {
                last = lower_bound(orig_idx.begin(), orig_idx.end(), i) - orig_idx.begin();
            }
            next_nz[i] = last;
        }
        
        vector<int> prev_nz(m, -1);
        last = -1;
        for (int i = 0; i < m; ++i) {
            if (s[i] != '0') {
                last = lower_bound(orig_idx.begin(), orig_idx.end(), i) - orig_idx.begin();
            }
            prev_nz[i] = last;
        }
        
        // Process queries
        vector<int> ans;
        ans.reserve(queries.size());
        
        for (const auto& q : queries) {
            int L = q[0], R = q[1];
            int l = next_nz[L];
            int r = prev_nz[R];
            
            // If there are no non-zero elements in the range
            if (l == -1 || r == -1 || l > r) {
                ans.push_back(0);
                continue;
            }
            
            // Calculate substring number x % MOD
            long long x = (pref_val[r + 1] - (pref_val[l] * pow10[r - l + 1]) % MOD + MOD) % MOD;
            
            // Calculate sum of digits
            long long sum = pref_sum[r + 1] - pref_sum[l];
            
            long long current_ans = (x * (sum % MOD)) % MOD;
            ans.push_back(current_ans);
        }
        
        return ans;
    }
};
