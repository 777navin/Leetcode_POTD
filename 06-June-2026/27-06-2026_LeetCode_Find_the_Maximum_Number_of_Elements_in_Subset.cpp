/*
Date: 27-06-2026
Problem Name: Find the Maximum Number of Elements in Subset
Platform: LeetCode
Difficulty: Medium
Tags: Array, Hash Table, Enumeration

Problem Summary:
Given an array of positive integers, select a subset that can be rearranged into a pattern 
[x, x^2, x^4, ..., x^(k/2), x^k, x^(k/2), ..., x^4, x^2, x].
Here, k must be a non-negative power of 2. We need to find the maximum number of elements 
in such a subset.

Methods to Solve:
1. Hash Map Chain Simulation (Optimal)

For EACH method include:

- Intuition:
  Every valid sequence starts with some base 'x'. Since it forms a mountain of squares 
  (x, x^2, x^4...), we can count frequencies of all numbers. For any starting 'x > 1', 
  we iteratively check if we have at least 2 copies of 'x' to form the "sides" of the 
  mountain, moving up to 'x^2', then 'x^4', until we can only place 1 copy (the peak) 
  or we run out of numbers. '1' is handled separately since 1^2 = 1.

- Approach:
  1. Store frequencies in an unordered_map<long long, int> to handle large squares safely.
  2. Handle '1's separately: we can use all available '1's if odd, or count - 1 if even.
  3. For other numbers, simulate the sequence: while freq[curr] >= 2, add 2 to length 
     and square curr.
  4. If we stop because freq[curr] == 1, add 1 (it is exactly the peak).
  5. If we stop because freq[curr] == 0, it means the PREVIOUS element in the chain 
     must act as the peak instead of a side pair. We adjust by subtracting 1 from the length.

- Dry Run (small example):
  nums = [14, 14, 196, 196, 38416, 38416]
  freq = {14:2, 196:2, 38416:2}
  Start curr = 14. freq[14]=2 -> len=2, curr=196.
  freq[196]=2 -> len=4, curr=38416.
  freq[38416]=2 -> len=6, curr=1475789056.
  freq[1475789056]=0 -> Loop stops. len = 6 - 1 = 5.

- Time Complexity: O(N) average case. Each number is part of an extremely short chain 
  (at most 5 elements, since numbers square rapidly).
- Space Complexity: O(N) to store frequencies in the hash map.
- Why better than previous method: Bypasses the early break bug by naturally simulating 
  long long squares, guaranteeing peaks are correctly identified.
- When to use: Whenever solving array chain/sequence problems dependent on frequency counts.

Comparison Table:
Method | TC | SC | Best Use Case
Hash Map Simulation | O(N) | O(N) | Optimal for array frequency and chain tracking

Final Recommended Solution: Hash Map Chain Simulation
*/

#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maximumLength(vector<int>& nums) {
        unordered_map<long long, int> freq;
        for (int x : nums) {
            freq[x]++;
        }

        int ans = 1;

        // Case 1: Handle '1's
        if (freq.count(1)) {
            int count1 = freq[1];
            if (count1 % 2 == 0) {
                count1--;
            }
            ans = max(ans, count1);
        }

        // Case 2: Handle chains starting from x > 1
        for (auto const& [key, count] : freq) {
            if (key == 1) continue;

            long long curr = key;
            int len = 0;

            // Follow the chain of squares
            while (freq.count(curr)) {
                if (freq[curr] >= 2) {
                    len += 2;
                    curr = curr * curr;
                } else { 
                    // freq[curr] == 1, this is a perfect peak
                    len += 1;
                    break;
                }
            }
            
            // If the loop exited because the square does not exist (freq[curr] == 0),
            // the previous element we processed must be the peak instead of a pair.
            if (!freq.count(curr)) {
                len -= 1;
            }

            ans = max(ans, len);
        }

        return ans;
    }
};
