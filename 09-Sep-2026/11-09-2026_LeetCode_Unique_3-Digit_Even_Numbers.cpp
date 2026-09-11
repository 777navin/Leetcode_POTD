/*
=========================================================
Date        : 11-09-2026
Problem Name: 3483. Unique 3-Digit Even Numbers
Platform    : LeetCode
Difficulty  : Easy
Tags        : Array, Hash Table, Enumeration

Problem Summary:
Given an integer array `digits`, find the count of distinct three-digit 
even numbers that can be formed using the elements. Each copy of a digit 
can only be used once per number, and leading zeros are not permitted.

Key Observation:
A valid 3-digit even number must lie strictly in the range [100, 998] with 
an even units digit; checking all such numbers against the available frequency 
of digits in `digits` is constant time O(1).
=========================================================
*/

#include <vector>
#include <unordered_set>

using namespace std;

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 1: Brute Force (Permutations of Triplets)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  Iterate over all unique index triplets (i, j, k) to form all possible 3-digit numbers.

• Approach:
  - Run three nested loops over the indices of `digits`.
  - Ensure i != j, j != k, and i != k.
  - Skip numbers with leading zeros (digits[i] == 0) or odd last digits (digits[k] % 2 != 0).
  - Insert valid numbers into a hash set to ensure uniqueness and return its size.

• Why it Works:
  Every valid number must be formed by selecting 3 distinct positions from the array.

• Time Complexity (TC):
  O(N^3), where N is the length of digits. Since N <= 10, N^3 <= 1000 operations.

• Space Complexity (SC):
  O(U), where U is the number of unique valid numbers stored in the hash set (at most 450).
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 2: Optimized (Digit Frequency Matching over [100, 998])
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  Instead of forming numbers from digits, iterate through all possible 3-digit even numbers 
  and check if they can be formed using the given digits.

• Approach:
  - Count the frequency of each digit (0-9) present in `digits`.
  - Iterate through all even numbers from 100 to 998 (step size of 2).
  - Decompose each number into its three digits and verify if the available frequencies suffice.
  - Increment the counter for each valid number.

• Why it Works:
  The range of 3-digit even numbers is fixed and small (exactly 450 candidates). Verifying 
  digit availability directly avoids duplicates and sorting.

• Time Complexity (TC):
  O(N + 450) = O(N), which is effectively O(1) given N <= 10.

• Space Complexity (SC):
  O(1), using fixed-size frequency arrays of size 10.
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
FINAL APPROACH:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Approach 2 (Digit Frequency Matching) is selected because:
- It eliminates the need for hash sets or deduplication logic.
- It runs in strictly bounded O(1) time after an O(N) frequency tally.
- It produces cleaner, more predictable code without nested index checks.
*/

class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        vector<int> count(10, 0);
        for (int d : digits) {
            count[d]++;
        }

        int total = 0;

        // Iterate over all 3-digit even numbers
        for (int num = 100; num <= 998; num += 2) {
            int d1 = num / 100;        // Hundreds digit
            int d2 = (num / 10) % 10;  // Tens digit
            int d3 = num % 10;         // Units digit

            vector<int> req(10, 0);
            req[d1]++;
            req[d2]++;
            req[d3]++;

            if (req[d1] <= count[d1] && 
                req[d2] <= count[d2] && 
                req[d3] <= count[d3]) {
                total++;
            }
        }

        return total;
    }
};
