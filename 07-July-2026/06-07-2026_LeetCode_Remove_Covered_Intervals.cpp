/*
=========================================================
Date        : 06-07-2026
Problem Name: Remove Covered Intervals
Platform    : LeetCode
Difficulty  : Medium
Tags        : Array, Sorting

Problem Summary:
Given a list of intervals [l, r), remove all intervals that are covered by another interval in the list.
An interval [a, b) is covered by [c, d) if c <= a and b <= d.
Return the number of remaining intervals.

Key Observation:
If we sort intervals by start time in ascending order, and by end time in descending order for ties,
we can easily identify covered intervals by keeping track of the maximum end time encountered so far.
=========================================================
*/

#include <vector>
#include <algorithm>

using namespace std;

/*
Approach: Sorting + Greedy
1. Intuition: 
   - By sorting by start time, we ensure that for any two intervals, the second one starts 
     at or after the first one. 
   - By sorting end time in descending order for ties, a covering interval will always 
     appear before the intervals it covers.

2. Approach:
   - Sort the intervals: Sort by start time ascending. If start times are equal, 
     sort by end time descending.
   - Iterate through the sorted intervals and maintain the current maximum end time (`maxEnd`) 
     seen so far.
   - For each interval, if its end time is <= `maxEnd`, it is covered; otherwise, 
     it is not covered, and we update `maxEnd`.

3. Why it Works:
   - Since we sorted, any interval encountered later cannot have a start time earlier 
     than the current `maxEnd`'s starting interval.
   - The greedy check `current_end <= maxEnd` effectively detects if the current interval 
     is completely contained within a previously processed one.

4. Complexity:
   - Time Complexity (TC): O(N log N) due to sorting, where N is the number of intervals.
   - Space Complexity (SC): O(1) or O(N) depending on the sorting implementation's space usage.
*/

/*
Final Approach:
We use the sorting strategy mentioned above. It is optimal because it reduces the problem 
to a single linear pass after an initial O(N log N) sort, avoiding the O(N^2) comparison 
of every pair.
*/

class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        // Sort: start time ascending, end time descending
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] == b[0]) return a[1] > b[1];
            return a[0] < b[0];
        });

        int count = 0;
        int maxEnd = 0;

        for (const auto& interval : intervals) {
            // If the current interval ends after the maxEnd seen so far, 
            // it is not covered.
            if (interval[1] > maxEnd) {
                count++;
                maxEnd = interval[1];
            }
            // If interval[1] <= maxEnd, it is covered, so we do nothing.
        }

        return count;
    }
};
