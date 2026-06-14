// 14-06-2026_Codeforces_The_Way_to_Home.cpp

/*
Date: 14-06-2026
Problem Name: The Way to Home
Platform: Codeforces
Difficulty: 800 (Estimated)
Tags: Greedy, Implementation

Problem Summary:
A frog is at point 1 on an axis and needs to reach point n. The frog can jump 
at most 'd' units to the right. The frog can only land on points that have 
a lily flower (represented by '1' in the input string). Determine the 
minimum number of jumps to reach point n, or -1 if impossible.

Methods to Solve:
1. Greedy Approach (Optimal)

For Method 1 (Greedy):
- Intuition: To minimize the total jumps, at any point 'curr', we should 
  jump to the farthest possible lily flower within the range [curr+1, curr+d].
- Approach: Start from position 0 (representing point 1). While the current 
  position is less than n-1, look for the farthest '1' within the next 'd' 
  indices. If no such '1' exists, the target is unreachable. Otherwise, 
  jump to that farthest index and increment the jump counter.
- Dry Run: n=8, d=4, s="10010101"
  - Start at index 0. Farthest '1' within 1-4 is index 3 (value '1'). Count=1.
  - From index 3, farthest '1' within 4-7 is index 7 (value '1'). Count=2.
  - Reached 7 (which is n-1). Total jumps = 2.
- Time Complexity: O(n)
- Space Complexity: O(1)
- Why better: It makes the locally optimal choice at each step to ensure the 
  global minimum.
- When to use: When we need to reach a target with limited step sizes and 
  specific allowed positions.

Comparison Table:
Method | TC   | SC   | Best Use Case
Greedy | O(n) | O(1) | Finding min jumps with constraints

Final Recommended Solution: Greedy
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

/**
 * Solves the "The Way to Home" problem using a greedy approach.
 * @param n Total points
 * @param d Maximum jump distance
 * @param s String representing lily positions
 * @return Minimum jumps or -1 if unreachable
 */
int solve() {
    int n, d;
    if (!(cin >> n >> d)) return -1;
    string s;
    cin >> s;

    int jumps = 0;
    int curr = 0; // Frog starts at point 1 (index 0)

    while (curr < n - 1) {
        int next_pos = -1;
        // Look for the farthest lily within range d
        for (int i = min(n - 1, curr + d); i > curr; --i) {
            if (s[i] == '1') {
                next_pos = i;
                break;
            }
        }

        // If no lily found in reach, it's impossible
        if (next_pos == -1) {
            return -1;
        }

        curr = next_pos;
        jumps++;
    }

    return jumps;
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << solve() << endl;

    return 0;
}
