/*
=========================================================
Date        : 16-08-2026
Problem Name: Stone Game IX
Platform    : LeetCode
Difficulty  : Medium
Tags        : Array, Math, Greedy, Game Theory, Counting

Problem Summary:
Alice and Bob take turns removing stones from an array, with Alice going first.
A player loses if their chosen stone causes the total sum of removed stones to be divisible by 3.
Bob automatically wins if all stones are removed without any player violating the divisibility rule.
The goal is to determine if Alice can force a win assuming optimal play from both players.

Key Observation:
Only the remainder modulo 3 of each stone value matters (count of 0s, 1s, and 2s).
Stones with modulo 0 act as turn-passers, while remaining stones follow a deterministic sequence.
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: State Simulation / Game Theory Greedy
---------------------------------------------------------
• Intuition:
  The value of each stone matters only by its remainder modulo 3 (c0, c1, c2).
  A stone with remainder 0 does not change the running sum mod 3, effectively acting as a turn-skipper.

• Approach:
  Count remainder frequencies: c0, c1, and c2.
  - If c0 is even:
    c0 stones can be paired up without changing player parity.
    Alice can win if both c1 > 0 and c2 > 0, because picking the smaller remainder side lets her control the alternating sequence.
  - If c0 is odd:
    An odd count of c0 stones reverses player parity once all 0s are played.
    Alice wins if the difference |c1 - c2| > 2, as Bob will eventually run out of valid moves first.

• Why it Works:
  After the initial choice (1 or 2), valid moves must strictly alternate to avoid reaching a running sum % 3 == 0 (e.g., 1 -> 1 -> 2 -> 1 -> 2...).
  The game becomes entirely deterministic based on the counts of c1, c2, and the parity of c0.

• Time Complexity (TC): O(N) — single pass to count stone remainders.
• Space Complexity (SC): O(1) — constant extra space for remainder counts.
---------------------------------------------------------
*/

/*
---------------------------------------------------------
FINAL APPROACH:
• Why this approach is chosen:
  It operates in linear time and constant space by reducing the game to remainder frequency analysis.
• Why it is better:
  Avoids costly minimax recursion or state search, directly computing the mathematical winning condition in O(1) auxiliary space.
---------------------------------------------------------
*/

#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;

class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        int count[3] = {0, 0, 0};
        for (int stone : stones) {
            count[stone % 3]++;
        }

        // When count of modulo 0 stones is even, 0s cancel each other out in parity.
        // Alice wins if she can pick a path and both 1s and 2s are available.
        if (count[0] % 2 == 0) {
            return count[1] >= 1 && count[2] >= 1;
        }

        // When count of modulo 0 stones is odd, parity is flipped.
        // Alice wins only if the difference between count[1] and count[2] is greater than 2.
        return abs(count[1] - count[2]) > 2;
    }
};
