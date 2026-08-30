/*
=========================================================
Date        : 30-08-2026
Problem Name: Removing Minimum and Maximum From Array
Platform    : LeetCode
Difficulty  : Medium
Tags        : Array, Greedy, Math

Problem Summary:
- Given a 0-indexed array of distinct integers, find the minimum and maximum elements.
- Deletions are allowed only from either the front or the back of the array.
- Determine the minimum total deletions required to remove both extremes.

Key Observation:
- There are only three possible deletion strategies: delete both from the front, delete both from the back, or delete one from the front and one from the back.
=========================================================
*/

/*
=========================================================
APPROACH 1: Compare Three Deletion Scenarios (Optimal)
=========================================================
• Intuition:
  - Let the indices of the minimum and maximum elements be `min_idx` and `max_idx`.
  - Let `left = min(min_idx, max_idx)` and `right = max(min_idx, max_idx)`.
  - We can cover both targets in three ways:
    1. Both from front: deletes elements up to index `right` -> `right + 1` operations.
    2. Both from back: deletes elements from index `left` to the end -> `n - left` operations.
    3. Both sides: delete `left` from front and `right` from back -> `(left + 1) + (n - right)` operations.

• Approach:
  - Iterate through the array once to locate the indices of the minimum and maximum elements.
  - Compute `left = min(min_idx, max_idx)` and `right = max(min_idx, max_idx)`.
  - Calculate deletions for all 3 scenarios and return the minimum.

• Why it Works:
  - Because deletions are constrained to array endpoints, any valid removal sequence that clears both indices will match one of the three traversal paths without unnecessary redundant steps.

• Time Complexity (TC): O(N) — single pass to find indices and O(1) math computations.
• Space Complexity (SC): O(1) — constant extra space used.
*/

/*
=========================================================
FINAL APPROACH
=========================================================
• Single-pass index discovery followed by constant-time evaluation of the three deletion scenarios.
• Achieves optimal O(N) time and O(1) auxiliary space without modifying the array.
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();
        if (n <= 2) {
            return n;
        }

        int min_idx = 0;
        int max_idx = 0;

        for (int i = 1; i < n; ++i) {
            if (nums[i] < nums[min_idx]) {
                min_idx = i;
            }
            if (nums[i] > nums[max_idx]) {
                max_idx = i;
            }
        }

        int left = min(min_idx, max_idx);
        int right = max(min_idx, max_idx);

        // Scenario 1: Remove both from front
        int deletions_front = right + 1;

        // Scenario 2: Remove both from back
        int deletions_back = n - left;

        // Scenario 3: Remove one from front and one from back
        int deletions_both_sides = (left + 1) + (n - right);

        return min({deletions_front, deletions_back, deletions_both_sides});
    }
};
