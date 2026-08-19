/*
=========================================================
Date        : 19-08-2026
Problem Name: Cinema Seat Allocation
Platform    : LeetCode
Difficulty  : Medium
Tags        : Array, Hash Table, Greedy, Bit Manipulation

Problem Summary:
A cinema has n rows (each with 10 seats). Four-person groups must sit 
together in seats [2,3,4,5], [4,5,6,7], or [6,7,8,9]. Find the maximum 
number of four-person groups that can be seated given reserved seats.

Key Observation:
Seats 1 and 10 do not impact any 4-person block. Rows without any reservations 
can always accommodate 2 groups. Rows with reservations need only bitmask checks 
for three specific 4-seat ranges.
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Full Simulation / Row-by-Row Array Tracking
---------------------------------------------------------
• Intuition:
  Represent each row as an array/boolean vector of 10 seats, mark reserved seats,
  and check greedily how many groups can be placed row by row.

• Approach:
  Iterate from row 1 to n, store reserved seats per row, and check if [2..5] and [6..9]
  can be placed, or fallback to [4..7].

• Why it Works:
  Directly simulates physical seating and greedy assignment rules.

• Time Complexity (TC) : O(n) - Exceeds time limit since n <= 10^9.
• Space Complexity (SC): O(n) - Memory limit exceeded for n = 10^9.
---------------------------------------------------------
APPROACH 2: Hash Map with Bitmasking for Reserved Rows Only (Most Optimal)
---------------------------------------------------------
• Intuition:
  Since n <= 10^9 but reserved seats <= 10^4, only rows with reserved seats need inspection.
  Every unreserved row contributes exactly 2 groups.

• Approach:
  1. Map each modified row to a bitmask representing occupied seats (bits 2 to 9).
  2. For completely untouched rows, add 2 * (n - reserved_rows_count) to the answer.
  3. For each recorded row:
     - Check if both Left [2,3,4,5] and Right [6,7,8,9] are free -> add 2.
     - Else, check if Left [2..5], Right [6..9], or Middle [4..7] is free -> add 1.
     - Otherwise -> add 0.

• Why it Works:
  Bitwise operations allow O(1) overlap checks per row while ignoring empty rows avoids TLE/MLE.

• Time Complexity (TC) : O(M) where M is the number of reserved seats (<= 10^4).
• Space Complexity (SC): O(R) where R is the number of unique reserved rows (<= M).
---------------------------------------------------------
*/

/*
=========================================================
FINAL APPROACH:
Hash Map + Bitmasking is chosen because n is up to 10^9 while reservedSeats 
length is at most 10^4. Filtering only processed rows guarantees O(M) time and 
space, completely avoiding TLE and MLE.
=========================================================
*/

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        // Map row number to a bitmask representing occupied seats
        unordered_map<int, int> rowMasks;
        
        for (const auto& seat : reservedSeats) {
            int row = seat[0];
            int col = seat[1];
            // Seats 1 and 10 do not affect any 4-seat allocation
            if (col >= 2 && col <= 9) {
                rowMasks[row] |= (1 << col);
            }
        }
        
        // Rows with no reservations can always accommodate 2 families
        int maxFamilies = (n - static_cast<int>(rowMasks.size())) * 2;
        
        // Bitmask definitions for valid 4-seat blocks:
        // Left:   seats 2, 3, 4, 5 -> (1<<2)|(1<<3)|(1<<4)|(1<<5) = 60
        // Right:  seats 6, 7, 8, 9 -> (1<<6)|(1<<7)|(1<<8)|(1<<9) = 960
        // Middle: seats 4, 5, 6, 7 -> (1<<4)|(1<<5)|(1<<6)|(1<<7) = 240
        const int leftMask = 60;
        const int rightMask = 960;
        const int middleMask = 240;
        
        for (const auto& [row, mask] : rowMasks) {
            bool leftPossible = (mask & leftMask) == 0;
            bool rightPossible = (mask & rightMask) == 0;
            bool middlePossible = (mask & middleMask) == 0;
            
            if (leftPossible && rightPossible) {
                maxFamilies += 2;
            } else if (leftPossible || rightPossible || middlePossible) {
                maxFamilies += 1;
            }
        }
        
        return maxFamilies;
    }
};
