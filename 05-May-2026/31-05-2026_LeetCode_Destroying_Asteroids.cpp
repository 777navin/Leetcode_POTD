/*
Date: 31-05-2026
Problem Name: 2126. Destroying Asteroids
Platform: LeetCode
Difficulty: Medium
Tags: Array, Greedy, Sorting

Problem Summary:
Given an integer `mass` representing the original mass of a planet and an array `asteroids` representing the masses of various asteroids, determine if the planet can destroy all the asteroids. The planet can destroy an asteroid if its mass is greater than or equal to the asteroid's mass, after which it absorbs the asteroid's mass. The asteroids can be collided with in any arbitrary order. Return true if all can be destroyed, otherwise false.

Methods to Solve:
1. Brute Force (Greedy Selection without Sorting)
2. Optimal Approach (Sorting + Greedy)

For EACH method include:

--- Method 1: Brute Force (Greedy Selection without Sorting) ---
Intuition:
Since we can choose any arbitrary order, we should always try to consume the smallest available asteroid that our planet can destroy. This ensures we build up our mass to tackle the larger asteroids later.
Approach:
Find the smallest asteroid in the array that is <= current mass. If found, add it to mass, mark it as destroyed, and repeat. If at any point we cannot find a valid asteroid and there are still asteroids left, return false.
Dry Run:
mass = 5, asteroids = [4, 9, 23, 4]
- Pass 1: find min <= 5. It's 4. mass = 5 + 4 = 9. asteroids left = [9, 23, 4]
- Pass 2: find min <= 9. It's 4. mass = 9 + 4 = 13. asteroids left = [9, 23]
- Pass 3: find min <= 13. It's 9. mass = 13 + 9 = 22. asteroids left = [23]
- Pass 4: find min <= 22. None available. Return false.
Time Complexity: $O(N^2)$ in the worst case (finding the minimum valid asteroid $N$ times).
Space Complexity: $O(1)$ auxiliary space if we modify the array, $O(N)$ if we keep a visited array.
Why better than previous method: N/A (Baseline).
When to use: Only conceptual or when $N$ is extremely small. This will cause a Time Limit Exceeded (TLE) on LeetCode.

--- Method 2: Optimal Approach (Sorting + Greedy) ---
Intuition:
Instead of repeatedly searching the array for the smallest valid asteroid, we can simply sort the asteroids in non-decreasing order. This allows us to process them greedily in a single pass.
Approach:
1. Sort the `asteroids` array in ascending order.
2. Initialize a `long long` variable `current_mass` with the initial `mass` to prevent integer overflow during addition (as mass can grow up to 10^10).
3. Iterate through the sorted array. If `current_mass` is greater than or equal to the current asteroid, add its mass to `current_mass`.
4. If it's strictly less, we can't destroy it (nor any subsequent larger ones), so return false.
5. If the loop completes successfully, return true.
Dry Run:
mass = 10, asteroids = [3, 9, 19, 5, 21]
- Sorted asteroids = [3, 5, 9, 19, 21]
- mass = 10 >= 3 -> mass = 13
- mass = 13 >= 5 -> mass = 18
- mass = 18 >= 9 -> mass = 27
- mass = 27 >= 19 -> mass = 46
- mass = 46 >= 21 -> mass = 67
All destroyed, return true.
Time Complexity: $O(N \log N)$ due to sorting. The linear scan takes $O(N)$ time.
Space Complexity: $O(1)$ auxiliary space (or $O(\log N)$ depending on the underlying sorting algorithm).
Why better than previous method: Reduces the time complexity from $O(N^2)$ to $O(N \log N)$, easily passing the constraints ($N \le 10^5$).
When to use: This is the optimal solution and should be used in competitive programming and interviews.

Comparison Table:
Method          | TC          | SC          | Best Use Case
----------------|-------------|-------------|-----------------------------
Brute Force     | $O(N^2)$    | $O(1)$      | Educational purposes only
Optimal         | $O(N \log N)$| $O(1)$      | Standard solution, passes all tests

Final Recommended Solution: Method 2 (Optimal Approach)
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool asteroidsDestroyed(int mass, vector<int>& asteroids) {
        // Use long long to avoid integer overflow as mass can accumulate up to 10^10
        long long currentMass = mass;
        
        // Sort asteroids to always tackle the smallest possible one first
        sort(asteroids.begin(), asteroids.end());
        
        for (int asteroid : asteroids) {
            if (currentMass >= asteroid) {
                currentMass += asteroid;
            } else {
                // Planet cannot destroy the current asteroid
                return false; 
            }
        }
        
        // All asteroids destroyed successfully
        return true;
    }
};
