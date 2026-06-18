/*
Date: 18-06-2026
Problem Name: 18-06-2026_LeetCode_Angle_Between_Hands_of_a_Clock.cpp
Platform: LeetCode
Difficulty: Medium
Tags: Math

Problem Summary:
Given two numbers, hour and minutes, calculate the smaller angle (in degrees) 
formed between the hour and the minute hand of an analog clock.

Methods to Solve:
1. Mathematical Calculation:
   - Calculate positions of both hands relative to 12 o'clock (0°).
   - Hour hand: Each hour represents 30° (360°/12). It also moves 0.5° for every minute passed (30°/60 mins).
   - Minute hand: Each minute represents 6° (360°/60 mins).
   - Compute absolute difference and return the smaller angle (min(diff, 360-diff)).

Comparison Table:
Method             | TC    | SC    | Best Use Case
-------------------|-------|-------|-------------------------
Mathematical       | O(1)  | O(1)  | Optimal approach

Final Recommended Solution:
Direct mathematical calculation is O(1) and covers all cases efficiently.
*/

#include <iostream>
#include <algorithm>
#include <cmath>

class Solution {
public:
    /**
     * Calculates the smaller angle between clock hands.
     * @param hour: 1 to 12
     * @param minutes: 0 to 59
     * @return: smallest angle as double
     */
    double angleClock(int hour, int minutes) {
        // Normalize hour to 0 if it is 12
        int h = hour % 12;
        
        // Hour hand position: 30 degrees per hour + 0.5 degrees per minute
        double hourAngle = (h * 30.0) + (minutes * 0.5);
        
        // Minute hand position: 6 degrees per minute
        double minuteAngle = minutes * 6.0;
        
        // Absolute difference
        double diff = std::abs(hourAngle - minuteAngle);
        
        // Return smaller angle
        return std::min(diff, 360.0 - diff);
    }
};

int main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    Solution sol;
    
    // Example test case: 3:15
    int hour = 3, minutes = 15;
    std::cout << "Angle at " << hour << ":" << minutes << " is: " 
              << sol.angleClock(hour, minutes) << " degrees." << std::endl;

    return 0;
}

