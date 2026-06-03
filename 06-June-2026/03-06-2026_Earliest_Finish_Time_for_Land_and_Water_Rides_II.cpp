/*
Date: 03-06-2026
Problem Name: Earliest Finish Time for Land and Water Rides II
Platform: LeetCode
Difficulty: Medium
Tags: Array, Two Pointers, Binary Search, Greedy, Sorting

Problem Summary:
You are given arrays representing the start times and durations for two types of rides: land and water.
A tourist must take exactly one of each, in any order. The tourist can start a ride at its open time 
or any time after. The objective is to find the minimum possible time the tourist finishes both rides.

Methods to Solve:
1. Brute Force
2. Optimal Approach (Sorting + Prefix/Suffix Arrays + Binary Search)

For EACH method include:

Method 1: Brute Force
- Intuition: Check all possible pairs of (land ride, water ride) in both sequences (Land -> Water and Water -> Land).
- Approach: Use nested loops. For every pair of rides, calculate the finish time. 
            If choosing Ride A then Ride B, the finish time of A is startA + durationA. 
            Then, Ride B can start at max(finishA, startB), finishing at start_time + durationB.
- Dry Run: 
    Land: S=[2], D=[4] | Water S=[6], D=[3]
    Pair 1: Land->Water. Land finishes at 2+4=6. Water starts at max(6,6)=6, finishes at 6+3=9.
- Time Complexity: O(N * M) where N is number of land rides and M is number of water rides.
- Space Complexity: O(1)
- Why better than previous method: N/A. (This approach will TLE given N, M <= 5*10^4).
- When to use: When array sizes are extremely small (<= 1000).

Method 2: Optimal Approach
- Intuition: Instead of comparing every pair, we can evaluate a sequence (e.g., First Rides -> Second Rides). 
             If we finish the first ride at time `finish1`, we want to pick a second ride to minimize the final finish time.
             The second ride will either:
             1. Open BEFORE or AT `finish1`. In this case, we start immediately. To minimize finish time, we just need the minimum duration among all such rides.
             2. Open AFTER `finish1`. In this case, we must wait until it opens. The finish time will just be its `start + duration`. We need the minimum `start + duration` among all such rides.
- Approach: 
    1. Group start times and durations into pairs and sort both lists by start times.
    2. Try both orders: (Land -> Water) and (Water -> Land).
    3. For the 'Second Rides' list, precompute two arrays:
       - `prefMinDur`: Prefix minimum of durations.
       - `suffMinFinish`: Suffix minimum of `start + duration`.
    4. Iterate over 'First Rides'. For each, compute `finish1 = start1 + duration1`.
    5. Use Binary Search (`upper_bound` logic) to find the partition in 'Second Rides' where start times exceed `finish1`.
    6. Take the minimum of (finish1 + min_duration_left) and (min_finish_right).
- Dry Run: 
    Land: [(5, 3)] (Finish1 = 8)
    Water: [(1, 10)] (Sorted)
    Binary Search for 8 in Water starts: Water ride 0 starts at 1 (<= 8). 
    Condition 1 applies: start immediately. Finish = 8 + 10 = 18.
- Time Complexity: O(N log N + M log M) due to sorting and O(N log M + M log N) for binary searches. Overall O(N log N + M log M).
- Space Complexity: O(N + M) to store pairs and prefix/suffix arrays.
- Why better than previous method: Reduces nested iteration to binary search, passing large constraints.
- When to use: This is the optimal and recommended approach.

Comparison Table:
Method         | TC                       | SC       | Best Use Case
-------------------------------------------------------------------------
Brute Force    | O(N * M)                 | O(1)     | Small constraints
Optimal Search | O(N log N + M log M)     | O(N + M) | Large constraints (N, M <= 50,000)

Final Recommended Solution
*/

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
private:
    // Helper function to calculate the minimum time if we do firstRides then secondRides
    int solveSequence(vector<pair<int, int>>& firstRides, vector<pair<int, int>>& secondRides) {
        int n = firstRides.size();
        int m = secondRides.size();

        // prefMinDur[i] = minimum duration among secondRides from index 0 to i
        vector<int> prefMinDur(m);
        prefMinDur[0] = secondRides[0].second;
        for (int i = 1; i < m; ++i) {
            prefMinDur[i] = min(prefMinDur[i - 1], secondRides[i].second);
        }

        // suffMinFinish[i] = minimum (start + duration) among secondRides from index i to m-1
        vector<int> suffMinFinish(m);
        suffMinFinish[m - 1] = secondRides[m - 1].first + secondRides[m - 1].second;
        for (int i = m - 2; i >= 0; --i) {
            suffMinFinish[i] = min(suffMinFinish[i + 1], secondRides[i].first + secondRides[i].second);
        }

        int minTotalTime = INT_MAX;

        for (int i = 0; i < n; ++i) {
            int finish1 = firstRides[i].first + firstRides[i].second;

            // Binary search to find the first ride in secondRides that starts strictly after finish1
            int low = 0, high = m - 1;
            int idx = m; // Default to m if all rides start <= finish1
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (secondRides[mid].first > finish1) {
                    idx = mid;
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }

            int currentFinish = INT_MAX;

            // Option 1: We pick a second ride that opens BEFORE or EXACTLY AT finish1
            // In this case, we don't have to wait. We start it exactly at finish1.
            if (idx > 0) {
                currentFinish = min(currentFinish, finish1 + prefMinDur[idx - 1]);
            }

            // Option 2: We pick a second ride that opens AFTER finish1
            // We have to wait. The finish time is solely determined by its start + duration.
            if (idx < m) {
                currentFinish = min(currentFinish, suffMinFinish[idx]);
            }

            minTotalTime = min(minTotalTime, currentFinish);
        }

        return minTotalTime;
    }

public:
    int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration, vector<int>& waterStartTime, vector<int>& waterDuration) {
        int n = landStartTime.size();
        int m = waterStartTime.size();

        // Pair start times and durations, then sort them by start time
        vector<pair<int, int>> landRides(n);
        for (int i = 0; i < n; ++i) {
            landRides[i] = {landStartTime[i], landDuration[i]};
        }
        sort(landRides.begin(), landRides.end());

        vector<pair<int, int>> waterRides(m);
        for (int i = 0; i < m; ++i) {
            waterRides[i] = {waterStartTime[i], waterDuration[i]};
        }
        sort(waterRides.begin(), waterRides.end());

        // Try both sequences: Land -> Water OR Water -> Land
        int landThenWater = solveSequence(landRides, waterRides);
        int waterThenLand = solveSequence(waterRides, landRides);

        return min(landThenWater, waterThenLand);
    }
};
