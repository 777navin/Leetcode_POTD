/*
=========================================================
Date        : 13-09-2026
Problem Name: Image Overlap
Platform    : LeetCode
Difficulty  : Medium
Tags        : Array, Matrix, Hash Table

Problem Summary:
Given two n x n binary matrices, img1 and img2.
Translate img1 in any 2D direction (up, down, left, right) without rotation.
Return the maximum possible number of overlapping 1s between both images.

Key Observation:
Two 1s at img1[r1][c1] and img2[r2][c2] overlap under a translation (dr, dc)
if and only if dr = r2 - r1 and dc = c2 - c1.
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Brute Force (Shift Simulation)
---------------------------------------------------------
• Intuition:
  Try all possible translations (dr, dc) where -n < dr < n and -n < dc < n,
  and for each translation count overlapping 1s.

• Approach:
  Iterate through all valid shifts dr and dc.
  For each shift, iterate over all overlapping coordinates and count matching 1s.
  Keep track of the global maximum overlap.

• Why it Works:
  The space of possible rigid translations in a discrete n x n grid is finite
  and bounded by (2n - 1) * (2n - 1).

• Time Complexity (TC) : O(n^4)
• Space Complexity (SC): O(1)
---------------------------------------------------------

---------------------------------------------------------
APPROACH 2: Optimized (Displacement Vector Frequency Map)
---------------------------------------------------------
• Intuition:
  Instead of checking empty or 0-cells across all shifts, only 1s matter.
  Every pair of 1s defines a unique translation vector required to align them.

• Approach:
  1. Extract coordinates of all 1s in img1 and img2 into two lists.
  2. For every pair (p1, p2), compute displacement vector (r2 - r1, c2 - c1).
  3. Count vector frequencies using a hash map or 2D array offset.
  4. The maximum frequency is the maximum achievable overlap.

• Why it Works:
  Any shift that aligns k pairs of 1s will be counted exactly k times by the
  corresponding relative displacement vector.

• Time Complexity (TC) : O(L1 * L2 + n^2), where L1, L2 <= n^2 are counts of 1s (O(n^4) worst case, much faster on sparse matrices).
• Space Complexity (SC): O(L1 + L2 + Unique Shifts) = O(n^2).
---------------------------------------------------------
*/

/*
=========================================================
FINAL APPROACH:
We choose Approach 2 (Displacement Vector Frequency Map).
It avoids scanning full grids for shifts where few or no 1s match,
making it significantly faster on typical sparse matrices while running well
within time limits in the worst case (n <= 30 -> n^4 <= 8.1 x 10^5 operations).
=========================================================
*/

#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
        int n = img1.size();
        vector<pair<int, int>> ones1, ones2;

        // Step 1: Collect coordinates of all 1-bits
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (img1[r][c] == 1) ones1.push_back({r, c});
                if (img2[r][c] == 1) ones2.push_back({r, c});
            }
        }

        // Step 2: Map displacement vectors to their frequency counts
        // Encode (dr, dc) into an integer key: (dr + 100) * 1000 + (dc + 100)
        unordered_map<int, int> shift_count;
        int max_overlap = 0;

        for (const auto& [r1, c1] : ones1) {
            for (const auto& [r2, c2] : ones2) {
                int dr = r2 - r1;
                int dc = c2 - c1;
                int key = (dr + 100) * 1000 + (dc + 100);
                shift_count[key]++;
                max_overlap = max(max_overlap, shift_count[key]);
            }
        }

        return max_overlap;
    }
};
