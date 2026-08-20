/*
=========================================================
Date        : 20-08-2026
Problem Name: Distribute Elements Into Two Arrays I
Platform    : LeetCode
Difficulty  : Easy
Tags        : Array, Simulation

Problem Summary:
Distribute elements of a given array into two separate arrays, arr1 and arr2.
Initially, place nums[0] into arr1 and nums[1] into arr2.
For each subsequent element, append it to arr1 if arr1's last element is greater than arr2's last element; otherwise, append to arr2.
Return the concatenation of arr1 and arr2.

Key Observation:
Direct simulation is optimal since we only need to inspect the back element of each array at each step and append accordingly.
=========================================================
*/

#include <vector>

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 1: Direct Simulation
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  - Simulate the exact process by maintaining two dynamic arrays and comparing their last inserted values.

• Approach:
  - Initialize `arr1` with `nums[0]` and `arr2` with `nums[1]`.
  - Iterate from index 2 to n - 1:
    - If `arr1.back() > arr2.back()`, push `nums[i]` to `arr1`.
    - Else, push `nums[i]` to `arr2`.
  - Concatenate `arr2` into `arr1` and return `arr1`.

• Why it Works:
  - Follows the operational rules deterministically with $O(1)$ access to the last elements.

• Time Complexity (TC):
  - $O(N)$ where $N$ is the length of `nums`.

• Space Complexity (SC):
  - $O(N)$ to store elements across the two arrays.
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
FINAL APPROACH: Simulation
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Chosen because the problem strictly dictates a sequential simulation process.
• Runs in linear time $O(N)$ and minimal auxiliary space $O(N)$, which is optimal.
*/

class Solution {
public:
    std::vector<int> resultArray(std::vector<int>& nums) {
        std::vector<int> arr1;
        std::vector<int> arr2;

        arr1.push_back(nums[0]);
        arr2.push_back(nums[1]);

        for (int i = 2; i < static_cast<int>(nums.size()); ++i) {
            if (arr1.back() > arr2.back()) {
                arr1.push_back(nums[i]);
            } else {
                arr2.push_back(nums[i]);
            }
        }

        arr1.insert(arr1.end(), arr2.begin(), arr2.end());
        return arr1;
    }
};
