
/*
=========================================================
Date        : 11-11-2026
Problem Name: 3789. Minimum Cost to Acquire Required Items
Platform    : LeetCode
Difficulty  : Medium
Tags        : Math, Greedy

Problem Summary:
- Three types of items are available.
- Type 1 contributes to requirement 1 only.
- Type 2 contributes to requirement 2 only.
- Type 3 contributes to both requirements.
- Find the minimum cost to satisfy both requirements.

Key Observation:
- Use type 3 items for common requirements when beneficial.
- For remaining requirements, choose the cheaper option
  between individual items and type 3 items.
=========================================================

APPROACH 1: BRUTE FORCE (NOT RECOMMENDED)

- Intuition:
  Try different combinations of all three item types.

- Approach:
  Enumerate possible quantities of each item type and
  calculate the minimum valid total cost.

- Why it Works:
  Every possible valid combination is considered.

- Time Complexity: O(min(need1, need2))
- Space Complexity: O(1)

APPROACH 2: GREEDY (OPTIMAL)

- Intuition:
  First satisfy the common requirement using the cheapest
  option between two individual items and one combined item.

- Approach:
  1. Let common = min(need1, need2).
  2. Buy common items at min(costBoth, cost1 + cost2).
  3. For remaining type 1, choose min(cost1, costBoth).
  4. For remaining type 2, choose min(cost2, costBoth).

- Why it Works:
  After satisfying the common requirement, the remaining
  requirements are independent. Each can be fulfilled
  using its cheapest available item.

- Time Complexity: O(1)
- Space Complexity: O(1)

FINAL APPROACH:
- Greedy is chosen because it directly compares the
  cheapest options for every required contribution.
- It avoids unnecessary enumeration and handles large
  requirements efficiently.
- Use long long to prevent integer overflow.
=========================================================
*/

class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth,
                          int need1, int need2) {

        long long common = min(need1, need2);

        long long totalCost = 0;

        // Satisfy common requirements.
        totalCost += common * min(costBoth, cost1 + cost2);

        // Remaining type 1 requirement.
        long long rem1 = need1 - common;
        totalCost += rem1 * min(cost1, costBoth);

        // Remaining type 2 requirement.
        long long rem2 = need2 - common;
        totalCost += rem2 * min(cost2, costBoth);

        return totalCost;
    }
};
