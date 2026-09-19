/*
=========================================================
Date        : 19-09-2026
Problem Name: Circle and Rectangle Overlapping
Platform    : LeetCode
Difficulty  : Medium
Tags        : Math, Geometry

Problem Summary:
Given a circle defined by its radius and center coordinates (xCenter, yCenter), 
and an axis-aligned rectangle defined by its bottom-left (x1, y1) and top-right (x2, y2) corners,
determine if there exists at least one point common to both shapes.

Key Observation:
Finding if the two shapes overlap is equivalent to finding the single point on or inside the rectangle 
closest to the circle's center and checking if its Euclidean distance to the center is <= radius.
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Clamping Coordinates (Most Optimal)
---------------------------------------------------------
• Intuition:
  The point on or inside an axis-aligned rectangle closest to (xCenter, yCenter) can be found 
  independently along the x and y axes by clamping the circle center's coordinates to the rectangle's bounds.

• Approach:
  - Find closest X: clamp xCenter within [x1, x2] using max(x1, min(x2, xCenter)) or std::clamp.
  - Find closest Y: clamp yCenter within [y1, y2] using max(y1, min(y2, yCenter)) or std::clamp.
  - Compute dx = xCenter - closestX and dy = yCenter - closestY.
  - Check if dx * dx + dy * dy <= radius * radius.

• Why it Works:
  - Because the rectangle is axis-aligned, projections onto orthogonal axes are decoupled.
  - If the center lies inside the rectangle, the closest point is the center itself (distance 0 <= radius).
  - If outside, clamping yields the exact boundary point with minimal Euclidean distance.

• Time Complexity (TC) : O(1) — constant time arithmetic operations.
• Space Complexity (SC): O(1) — no auxiliary data structures allocated.
---------------------------------------------------------
*/

/*
---------------------------------------------------------
FINAL APPROACH:
The coordinate clamping technique is chosen because it solves the problem analytically in O(1) time
without requiring floating-point operations or checking individual edges/corners separately.
---------------------------------------------------------
*/

#include <algorithm>

class Solution {
public:
    bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2) {
        // Find the point on/inside the rectangle closest to the circle's center
        int closestX = std::clamp(xCenter, x1, x2);
        int closestY = std::clamp(yCenter, y1, y2);

        // Calculate horizontal and vertical distances
        int dx = xCenter - closestX;
        int dy = yCenter - closestY;

        // Check if squared Euclidean distance is within squared radius
        return (dx * dx + dy * dy) <= (radius * radius);
    }
};
