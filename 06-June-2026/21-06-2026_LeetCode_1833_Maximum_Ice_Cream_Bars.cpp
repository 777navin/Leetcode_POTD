/*
Date: 22-06-2026
Problem Name: 1833. Maximum Ice Cream Bars
Platform: LeetCode
Difficulty: Medium
Tags: Array, Greedy, Sorting, Counting Sort

Problem Summary:
Given an array `costs` where `costs[i]` is the price of the i-th ice cream bar and an integer `coins` 
representing the total coins available, find the maximum number of ice cream bars that can be purchased.

Methods to Solve:
1. Sorting (Greedy)
2. Counting Sort (Optimal - Required)

For Counting Sort:
- Intuition: Since the constraints on `costs[i]` are relatively small ($1 \le costs[i] \le 10^5$), 
  we can count the frequency of each price and iterate from the cheapest to the most expensive.
- Approach: Create a frequency array (or hash map). Iterate through the frequency array, 
  subtracting prices from `coins` until we cannot afford the next bar.
- Dry Run: costs = [1,3,2,4,1], coins = 7
  Freq: {1: 2, 2: 1, 3: 1, 4: 1}
  - Price 1: buy 2 bars (cost 2, coins left 5)
  - Price 2: buy 1 bar (cost 2, coins left 3)
  - Price 3: buy 1 bar (cost 3, coins left 0)
  Total: 4 bars.
- Time Complexity: O(n + m), where n is the number of elements and m is the max cost.
- Space Complexity: O(m) to store frequencies.
- Why better: Avoids O(n log n) sorting time, faster for bounded ranges.
- When to use: When the range of values is constrained and manageable.

Comparison Table:
Method         | TC       | SC     | Best Use Case
---------------|----------|--------|--------------
Sorting        | O(N log N)| O(1)   | General purpose
Counting Sort  | O(N + M) | O(M)   | Bounded range of values

Final Recommended Solution: Counting Sort (as requested)
*/

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    /**
     * @brief Calculates maximum ice cream bars using Counting Sort approach.
     * * @param costs Vector of ice cream prices.
     * @param coins Total coins available.
     * @return int Maximum bars possible.
     */
    int maxIceCream(vector<int>& costs, int coins) {
        // Find the maximum price to determine the size of the frequency array
        int maxCost = 0;
        for (int cost : costs) {
            maxCost = max(maxCost, cost);
        }

        // Frequency array to count occurrences of each price
        vector<int> freq(maxCost + 1, 0);
        for (int cost : costs) {
            freq[cost]++;
        }

        int count = 0;
        // Iterate through prices starting from 1
        for (int price = 1; price <= maxCost; ++price) {
            if (freq[price] == 0) continue;

            // Check how many of this price we can afford
            if (coins >= (long long)price * freq[price]) {
                count += freq[price];
                coins -= (price * freq[price]);
            } else {
                // Buy as many as possible with remaining coins
                count += coins / price;
                break;
            }
        }

        return count;
    }
};
