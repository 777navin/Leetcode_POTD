/*
=========================================================
Date        : 14-09-2026
Problem Name: Rectangle Overlap
Platform: LeetCode
Difficulty: Easy
Tags: Math, Geometry

Problem Summary:
Given two axis-aligned rectangles represented by their bottom-left 
and top-right coordinates, determine if they overlap.
Touching at the corners or edges does not count as overlapping.

Key Observation:
Instead of finding where they overlap, it is mathematically much 
easier to check the conditions under which they definitely DO NOT overlap.
=========================================================
*/

#include <vector>
#include <algorithm>

using namespace std;

/*
1. Check Intersection Area
• Intuition: If two rectangles overlap, their intersecting region will also be a valid rectangle with positive width and height.
• Approach: Calculate the overlapping width by taking the min of right edges minus the max of left edges. Do the same for height.
• Why it Works: A positive width and height mean a physical intersection area exists.
• Time Complexity (TC): O(1)
• Space Complexity (SC): O(1)

2. Check Non-Overlapping Conditions
• Intuition: Two rectangles cannot overlap if one is completely to the left, right, top, or bottom of the other.
• Approach: Check if rec1 is strictly left of rec2, right of rec2, below rec2, or above rec2. Negate this result.
• Why it Works: If none of the mutually exclusive separation conditions are met, the rectangles must be intersecting.
• Time Complexity (TC): O(1)
• Space Complexity (SC): O(1)
*/

/*
FINAL APPROACH
• We choose the Non-Overlapping Conditions approach.
• It avoids subtraction and min/max operations, relying purely on simple logical comparisons.
• It is highly intuitive to read and computationally lightweight.
*/

class Solution {
public:
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        // rec1[0], rec1[1] -> bottom-left (x1, y1)
        // rec1[2], rec1[3] -> top-right (x2, y2)
        
        // Check if rec1 is completely to the left of rec2
        bool isLeft = rec1[2] <= rec2[0];
        
        // Check if rec1 is completely to the right of rec2
        bool isRight = rec1[0] >= rec2[2];
        
        // Check if rec1 is completely below rec2
        bool isBelow = rec1[3] <= rec2[1];
        
        // Check if rec1 is completely above rec2
        bool isAbove = rec1[1] >= rec2[3];
        
        // If any of the above conditions are true, they do not overlap.
        // Therefore, we return the negation.
        return !(isLeft || isRight || isBelow || isAbove);
    }
};/*
=========================================================
Date        : 14-09-2026
Problem Name: Rectangle Overlap
Platform: LeetCode
Difficulty: Easy
Tags: Math, Geometry

Problem Summary:
Given two axis-aligned rectangles represented by their bottom-left 
and top-right coordinates, determine if they overlap.
Touching at the corners or edges does not count as overlapping.

Key Observation:
Instead of finding where they overlap, it is mathematically much 
easier to check the conditions under which they definitely DO NOT overlap.
=========================================================
*/

#include <vector>
#include <algorithm>

using namespace std;

/*
1. Check Intersection Area
• Intuition: If two rectangles overlap, their intersecting region will also be a valid rectangle with positive width and height.
• Approach: Calculate the overlapping width by taking the min of right edges minus the max of left edges. Do the same for height.
• Why it Works: A positive width and height mean a physical intersection area exists.
• Time Complexity (TC): O(1)
• Space Complexity (SC): O(1)

2. Check Non-Overlapping Conditions
• Intuition: Two rectangles cannot overlap if one is completely to the left, right, top, or bottom of the other.
• Approach: Check if rec1 is strictly left of rec2, right of rec2, below rec2, or above rec2. Negate this result.
• Why it Works: If none of the mutually exclusive separation conditions are met, the rectangles must be intersecting.
• Time Complexity (TC): O(1)
• Space Complexity (SC): O(1)
*/

/*
FINAL APPROACH
• We choose the Non-Overlapping Conditions approach.
• It avoids subtraction and min/max operations, relying purely on simple logical comparisons.
• It is highly intuitive to read and computationally lightweight.
*/

class Solution {
public:
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        // rec1[0], rec1[1] -> bottom-left (x1, y1)
        // rec1[2], rec1[3] -> top-right (x2, y2)
        
        // Check if rec1 is completely to the left of rec2
        bool isLeft = rec1[2] <= rec2[0];
        
        // Check if rec1 is completely to the right of rec2
        bool isRight = rec1[0] >= rec2[2];
        
        // Check if rec1 is completely below rec2
        bool isBelow = rec1[3] <= rec2[1];
        
        // Check if rec1 is completely above rec2
        bool isAbove = rec1[1] >= rec2[3];
        
        // If any of the above conditions are true, they do not overlap.
        // Therefore, we return the negation.
        return !(isLeft || isRight || isBelow || isAbove);
    }
};
