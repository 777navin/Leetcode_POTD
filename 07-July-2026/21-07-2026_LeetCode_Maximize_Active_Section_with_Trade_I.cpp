/*
=========================================================
Date        : 21-07-2026
Problem Name: 3499. Maximize Active Section with Trade I
Platform    : LeetCode
Difficulty  : Medium
Tags        : String, Enumeration, Sliding Window

Problem Summary:
Given a binary string s where '1' represents active sections and '0' inactive ones.
Treat s as if augmented with '1' at both ends ('1' + s + '1').
You can make at most one trade: convert a contiguous block of '1's surrounded by '0's to '0's, 
and then convert a contiguous block of '0's surrounded by '1's to '1's.
Return the maximum number of '1's achievable after making the optimal trade.

Key Observation:
Performing a trade effectively combines two adjacent '0'-segments separated by a '1'-segment 
and flips the middle '1'-segment along with the two '0'-segments into all '1's.
The gain (delta) in active sections by choosing a middle '1'-segment is equal to 
the sum of the lengths of its neighboring '0'-segments.
=========================================================
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

/*
---------------------------------------------------------
1. OPTIMIZED APPROACH (Segment Grouping & Delta Max)
---------------------------------------------------------
• Intuition:
  Augmenting s with '1' at both ends creates alternating blocks of '1's and '0's.
  Replacing a block of '1's surrounded by '0's with '0's merges those '0's with the 
  middle block, which can then all be flipped to '1's. The net increase of '1's is 
  the combined length of the two adjacent '0' blocks.

• Approach:
  1. Compress s into consecutive alternating segment counts of '1's and '0's.
  2. Count the total number of original '1's in s.
  3. Iterate through every '1'-segment that is surrounded by two '0'-segments.
  4. Calculate the potential gain as (length of left '0'-segment + length of right '0'-segment).
  5. Find the maximum gain and add it to the initial total count of '1's.

• Why it Works:
  Flipping the middle '1'-segment to '0's joins the left and right '0'-segments into 
  one contiguous '0'-block surrounded by '1's, which is then flipped entirely to '1's.

• Time Complexity (TC): O(N) — Single pass to count segments and another pass to compute max delta.
• Space Complexity (SC): O(N) — Stores segment lengths.
---------------------------------------------------------
*/

/*
---------------------------------------------------------
FINAL APPROACH SELECTION
---------------------------------------------------------
• Chosen Approach : Segment Decomposition & Delta Maximization
• Why Chosen     : It solves the problem in optimal linear time O(N) and uses minimal extra memory.
• Advantages     : Direct enumeration of candidates guarantees finding the global maximum without redundant computations.
---------------------------------------------------------
*/

class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int n = s.length();
        int totalOnes = 0;
        for (char c : s) {
            if (c == '1') totalOnes++;
        }

        // Augmented s with '1' at both ends
        // Build array of segments: {type (1 or 0), length}
        vector<pair<int, int>> segments;
        
        // Start with augmented '1'
        segments.push_back({1, 1});
        
        int i = 0;
        while (i < n) {
            int j = i;
            while (j < n && s[j] == s[i]) {
                j++;
            }
            int len = j - i;
            int val = s[i] - '0';
            
            if (segments.back().first == val) {
                segments.back().second += len;
            } else {
                segments.push_back({val, len});
            }
            i = j;
        }
        
        // End with augmented '1'
        if (segments.back().first == 1) {
            segments.back().second += 1;
        } else {
            segments.push_back({1, 1});
        }

        int maxDelta = 0;

        // Look for a '1'-segment surrounded by two '0'-segments
        // Pattern: [0-segment, 1-segment, 0-segment]
        for (size_t idx = 1; idx + 1 < segments.size(); ++idx) {
            if (segments[idx].first == 1) {
                if (segments[idx - 1].first == 0 && segments[idx + 1].first == 0) {
                    int leftZeros = segments[idx - 1].second;
                    int rightZeros = segments[idx + 1].second;
                    maxDelta = max(maxDelta, leftZeros + rightZeros);
                }
            }
        }

        return totalOnes + maxDelta;
    }
};
