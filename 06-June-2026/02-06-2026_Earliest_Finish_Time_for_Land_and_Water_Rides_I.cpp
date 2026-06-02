/*
Date: 02-06-2026
Problem Name: 3633. Earliest Finish Time for Land and Water Rides I
Platform: LeetCode
Difficulty: Easy
Tags: Array, Math, Brute Force, Simulation

Problem Summary: 
You are given the start times and durations for two types of rides: land and water. 
You must take exactly one of each. You can start a ride at its opening time or wait 
until later. Your goal is to find the minimum possible time to complete both rides, 
trying both possible sequences (Land -> Water and Water -> Land).

Methods to Solve:
1. Optimal Pairwise Comparison (Brute Force)

---------------------------------------------------------
Method 1: Optimal Pairwise Comparison (Brute Force)
---------------------------------------------------------
- Intuition:
  Since the constraints are very small ($N, M \le 100$), we can evaluate every possible 
  pairing of one land ride and one water ride. For every pair, there are two distinct 
  schedules: riding the land ride first, or riding the water ride first. We simply 
  calculate the finish time for both schedules and track the global minimum.

- Approach:
  1. Initialize `min_finish_time` to infinity.
  2. Use nested loops to iterate through every land ride $i$ and water ride $j$.
  3. Calculate schedule A (Land then Water):
     - Finish land ride at $t_1 = \text{landStartTime}[i] + \text{landDuration}[i]$.
     - Start water ride at $\max(t_1, \text{waterStartTime}[j])$.
     - Finish water ride at $\max(t_1, \text{waterStartTime}[j]) + \text{waterDuration}[j]$.
  4. Calculate schedule B (Water then Land):
     - Finish water ride at $t_2 = \text{waterStartTime}[j] + \text{waterDuration}[j]$.
     - Start land ride at $\max(t_2, \text{landStartTime}[i])$.
     - Finish land ride at $\max(t_2, \text{landStartTime}[i]) + \text{landDuration}[i]$.
  5. Update `min_finish_time` with the minimum of both schedules.
  6. Return `min_finish_time`.

- Dry Run (Example 1):
  landStartTime = [2, 8], landDuration = [4, 1]
  waterStartTime = [6], waterDuration = [3]
  
  Pair (Land 0, Water 0):
  - Land -> Water: Land finishes at 2+4 = 6. Water starts at max(6, 6) = 6, finishes at 6+3 = 9.
  - Water -> Land: Water finishes at 6+3 = 9. Land starts at max(9, 2) = 9, finishes at 9+4 = 13.
  Best for this pair = 9.
  
  Pair (Land 1, Water 0):
  - Land -> Water: Land finishes at 8+1 = 9. Water starts at max(9, 6) = 9, finishes at 9+3 = 12.
  - Water -> Land: Water finishes at 6+3 = 9. Land starts at max(9, 8) = 9, finishes at 9+1 = 10.
  Best for this pair = 10.
  
  Global Minimum = 9.

- Time Complexity:
  $O(N \times M)$ where $N$ is the number of land rides and $M$ is the number of water rides. 
  Given the constraint $\le 100$, this will take at most $10^4$ operations, running in ~0ms.

- Space Complexity:
  $O(1)$ as we only use a few integer variables to store current times and the global minimum.

- Why better than previous method:
  With $N, M \le 100$, this exhaustive search is both the brute force and the optimal 
  approach. Sorting or complex data structures would overcomplicate the logic without 
  providing meaningful performance gains.

- When to use:
  When dataset constraints are extremely small and pairwise evaluation yields the exact 
  optimal answer without risking a Time Limit Exceeded (TLE) error.

Comparison Table:
Method                              | TC           | SC   | Best Use Case
------------------------------------|--------------|------|---------------------------
Optimal Pairwise Comparison         | $O(N \times M)$ | $O(1)$ | Small constraints $\le 1000$

Final Recommended Solution: Optimal Pairwise Comparison
*/

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration, 
                           vector<int>& waterStartTime, vector<int>& waterDuration) {
        
        int min_finish_time = INT_MAX;
        int n = landStartTime.size();
        int m = waterStartTime.size();
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                
                // Option A: Land ride first, then Water ride
                int land_finish = landStartTime[i] + landDuration[i];
                int water_start_A = max(land_finish, waterStartTime[j]);
                int total_finish_A = water_start_A + waterDuration[j];
                
                // Option B: Water ride first, then Land ride
                int water_finish = waterStartTime[j] + waterDuration[j];
                int land_start_B = max(water_finish, landStartTime[i]);
                int total_finish_B = land_start_B + landDuration[i];
                
                // Update the global minimum
                min_finish_time = min({min_finish_time, total_finish_A, total_finish_B});
            }
        }
        
        return min_finish_time;
    }
};
