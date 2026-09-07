/*
=========================================================
Date        : 07-09-2026
Problem Name: Distinct Subsequences II
Platform    : LeetCode
Difficulty  : Hard
Tags        : String, Dynamic Programming

Problem Summary:
Given a string s, return the number of distinct non-empty subsequences modulo 10^9 + 7.
A subsequence is formed by deleting zero or more characters without changing relative order.

Key Observation:
Appending a character c doubles the total number of subsequences, but duplicates 
the subsequences previously formed by the last occurrence of c.
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Dynamic Programming with Substring Prefix Tracking (Better)
---------------------------------------------------------
• Intuition:
  - Let dp[i] be the count of distinct non-empty subsequences using prefix s[0...i-1].
  - When extending with s[i-1], every existing subsequence can append s[i-1], plus s[i-1] itself forms a new 1-length subsequence.

• Approach:
  - Set dp[i] = (2 * dp[i - 1] + 1) % MOD.
  - If s[i-1] was seen previously at index j, subtract (dp[j - 1] + 1) to remove duplicates.
  - Track last seen indices in an array of size 26.

• Why it Works:
  - Subsequences ending at the previous occurrence of s[i-1] are duplicated exactly when s[i-1] is appended to those prefixes again.

• Time Complexity (TC): O(n), where n is the length of s.
• Space Complexity (SC): O(n) for the dp array.
*/

/*
---------------------------------------------------------
APPROACH 2: Constant Space DP Tracking by Ending Character (Most Optimal)
---------------------------------------------------------
• Intuition:
  - Instead of a prefix array, track the total number of distinct subsequences ending with each character 'a'-'z'.
  - When character c arrives, it can extend all currently known distinct subsequences plus the empty subsequence.

• Approach:
  - Maintain an array `ends_with[26]` and `current_total_sum`.
  - When seeing char c, the new distinct count ending in c becomes (current_total_sum + 1) % MOD.
  - Update `current_total_sum` by adding the new count and subtracting the previous `ends_with[c]`.

• Why it Works:
  - Distinct subsequences are uniquely partitioned by their last character; overwriting ends_with[c] naturally eliminates all previous duplicates ending in c.

• Time Complexity (TC): O(n), scanning the string once.
• Space Complexity (SC): O(1), uses fixed array of size 26.
*/

/*
---------------------------------------------------------
FINAL APPROACH:
---------------------------------------------------------
• Approach 2 is selected as it runs in O(n) time and O(1) auxiliary space.
• It avoids storing an O(n) DP table while keeping modular arithmetic straightforward.
*/

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int distinctSubseqII(string s) {
        const int MOD = 1e9 + 7;
        vector<long long> ends_with(26, 0);
        long long total_subsequences = 0;

        for (char ch : s) {
            int idx = ch - 'a';
            // All existing distinct subsequences + the single character subsequence itself
            long long new_ends_with = (total_subsequences + 1) % MOD;
            
            // Total increases by new sequences minus the old sequences ending with this character
            total_subsequences = (total_subsequences + new_ends_with - ends_with[idx] + MOD) % MOD;
            
            ends_with[idx] = new_ends_with;
        }

        return total_subsequences;
    }
};
