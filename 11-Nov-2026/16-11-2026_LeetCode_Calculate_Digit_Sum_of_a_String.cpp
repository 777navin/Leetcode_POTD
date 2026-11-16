
/*
=========================================================
Date        : 16-11-2026
Problem Name: 2243. Calculate Digit Sum of a String
Platform    : LeetCode
Difficulty  : Easy
Tags        : String, Simulation

Problem Summary:
- Given a numeric string s and integer k.
- Divide s into consecutive groups of size k.
- Replace each group with the sum of its digits.
- Repeat until the string length is <= k.

Key Observation:
- Each round reduces the string by replacing groups
  with their digit sums.
- Direct simulation is sufficient.
=========================================================

APPROACH 1: BRUTE FORCE

- Intuition:
  Process each group and calculate its digit sum.

- Approach:
  Simulate the grouping and concatenation repeatedly.

- Why it Works:
  Every operation follows the problem statement exactly.

- TC: O(n * log n) approximately
- SC: O(n)


APPROACH 2: OPTIMIZED SIMULATION

- Intuition:
  Only one traversal of the current string is needed
  to construct the next string.

- Approach:
  Use a loop with steps of k and calculate each
  group's digit sum using a nested loop.

- Why it Works:
  All groups are processed in their original order,
  including the final smaller group.

- TC: O(n * log n) approximately
- SC: O(n)


FINAL APPROACH:
- Choose optimized simulation because it is simple
  and directly follows the required operations.
- No extra data structures or complex algorithms
  are required.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string digitSum(string s, int k) {

        while (s.size() > k) {

            string nextString = "";

            for (int i = 0; i < s.size(); i += k) {

                int sum = 0;

                for (int j = i; j < min((int)s.size(), i + k); j++) {
                    sum += s[j] - '0';
                }

                nextString += to_string(sum);
            }

            s = nextString;
        }

        return s;
    }
};

/*
=========================================================
Example:

Input:
s = "11111222223", k = 3

Round 1:
111 -> 3
112 -> 4
222 -> 6
23  -> 5

New string = "3465"

Round 2:
346 -> 13
5   -> 5

New string = "135"

Output: "135"
=========================================================
*/
