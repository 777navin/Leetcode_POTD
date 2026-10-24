/*
=========================================================
Date        : 24-10-2026
Problem Name: Count Days Spent Together
Platform    : LeetCode
Difficulty  : Easy
Tags        : Math, String

Problem Summary:
- Alice and Bob arrive and leave Rome on given dates in format "MM-DD" during a non-leap year.
- We need to calculate the total number of overlapping calendar days both are in Rome together.

Key Observation:
- Converting each "MM-DD" date into the absolute day of the year simplifies the range overlap problem to finding the intersection of two intervals [start1, end1] and [start2, end2].
=========================================================
*/

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

class Solution {
public:
    /*
    =====================================================
    APPROACH 1: Day of Year Conversion & Interval Overlap
    =====================================================

    • Intuition:
      Convert each date string ("MM-DD") into its corresponding day number of the year (from 1 to 365).
      Then, the overlapping days between Alice's stay [arriveAlice, leaveAlice] and Bob's stay [arriveBob, leaveBob] can be computed directly.

    • Approach:
      1. Use a precomputed array of days in each month for a non-leap year.
      2. Write a helper function to convert any "MM-DD" string into an integer day of the year.
      3. Find the latest arrival date: max(arriveAlice, arriveBob).
      4. Find the earliest departure date: min(leaveAlice, leaveBob).
      5. The number of overlapping days is (earliest_departure - latest_arrival + 1). If latest_arrival > earliest_departure, there is no overlap, so return 0.

    • Why it Works:
      The intersection of two inclusive time intervals [S1, E1] and [S2, E2] is given by the interval [max(S1, S2), min(E1, E2)].
      If the start of the intersection is less than or equal to its end, the length of the intersection is `end - start + 1`. Otherwise, it is 0.

    • Time Complexity (TC): O(1) because the number of months is constant (12 months) and string processing takes fixed time.
    • Space Complexity (SC): O(1) auxiliary space.
    */

    int countDaysTogether(std::string arriveAlice, std::string leaveAlice, std::string arriveBob, std::string leaveBob) {
        // Days in each month for a non-leap year
        std::vector<int> daysInMonths = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        auto dateToDayOfYear = [&](const std::string& date) {
            int month = std::stoi(date.substr(0, 2));
            int day = std::stoi(date.substr(3, 2));
            int dayOfYear = day;
            for (int i = 0; i < month - 1; ++i) {
                dayOfYear += daysInMonths[i];
            }
            return dayOfYear;
        };

        int arriveAliceDay = dateToDayOfYear(arriveAlice);
        int leaveAliceDay = dateToDayOfYear(leaveAlice);
        int arriveBobDay = dateToDayOfYear(arriveBob);
        int leaveBobDay = dateToDayOfYear(leaveBob);

        // Find the latest arrival and earliest departure
        int latestArrival = std::max(arriveAliceDay, arriveBobDay);
        int earliestDeparture = std::min(leaveAliceDay, leaveBobDay);

        // Calculate overlapping days
        if (latestArrival <= earliestDeparture) {
            return earliestDeparture - latestArrival + 1;
        }
        
        return 0;
    }
};
