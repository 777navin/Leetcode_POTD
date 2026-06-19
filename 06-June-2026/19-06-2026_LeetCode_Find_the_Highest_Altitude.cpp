/*
Date: 19-06-2026
Problem Name: 19-06-2026_LeetCode_Find_the_Highest_Altitude.cpp
Platform: LeetCode
Difficulty: Easy
Tags: Array, Prefix Sum

Problem Summary:
A biker goes on a road trip starting at altitude 0. You are given an integer array `gain` 
where `gain[i]` is the net gain in altitude between points `i` and `i + 1`. 
Return the highest altitude reached during the trip.

Methods to Solve:
1. Prefix Sum / Running Total (Optimal Approach)

For EACH method include:

- Intuition: 
  The current altitude at any point is simply the cumulative sum of all previous 
  altitude gains (and drops). To find the highest point, we can just maintain a 
  running sum of the altitudes and keep track of the maximum value observed so far.
  Since we start at altitude 0, the maximum altitude is initialized to 0.

- Approach:
  1. Initialize `current_altitude = 0` and `max_altitude = 0`.
  2. Iterate through each value in the `gain` array.
  3. Add the `gain[i]` to `current_altitude`.
  4. Update `max_altitude` to be the maximum of itself and `current_altitude`.
  5. Return `max_altitude` after the loop.

- Dry Run (small example):
  Input: gain = [-5, 1, 5, 0, -7]
  Start: current_altitude = 0, max_altitude = 0
  Step 1 (-5): current = -5, max = 0
  Step 2 ( 1): current = -4, max = 0
  Step 3 ( 5): current =  1, max = 1
  Step 4 ( 0): current =  1, max = 1
  Step 5 (-7): current = -6, max = 1
  Result: 1

- Time Complexity: O(N) where N is the length of the gain array. We iterate through it once.
- Space Complexity: O(1) as we only use two integer variables.
- Why better than previous method: This is the singular optimal solution for this problem.
- When to use: Whenever cumulative calculations (prefix sums) determine a state or peak.

Comparison Table:
Method             | TC    | SC    | Best Use Case
-------------------|-------|-------|-------------------------
Prefix Sum         | O(N)  | O(1)  | Direct, highly optimal approach

Final Recommended Solution:
The prefix sum approach accurately models the problem and hits the theoretical optimal bounds for time and space.
*/

#include <vector>
#include <algorithm>

class Solution {
public:
    int largestAltitude(std::vector<int>& gain) {
        int current_altitude = 0;
        int max_altitude = 0;
        
        for (int g : gain) {
            current_altitude += g;
            max_altitude = std::max(max_altitude, current_altitude);
        }
        
        return max_altitude;
    }
};
