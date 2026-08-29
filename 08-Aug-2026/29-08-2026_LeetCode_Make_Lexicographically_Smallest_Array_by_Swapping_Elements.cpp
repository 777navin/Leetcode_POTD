/*
=========================================================
Date        : 29-08-2026
Problem Name: Make Lexicographically Smallest Array by Swapping Elements
Platform    : LeetCode
Difficulty  : Medium
Tags        : Array, Union-Find, Sorting

Problem Summary:
- Given an array of integers and an integer limit, we can swap any two elements if their absolute difference is <= limit.
- We want to find the lexicographically smallest array achievable by performing this operation any number of times.

Key Observation:
- Elements that are transitively connected by differences <= limit form components where all elements can be rearranged amongst their original positions.
- Sorting elements along with their original indices allows us to identify these components efficiently and place the smallest available values into the smallest available indices.
=========================================================
*/

/*
=========================================================
APPROACH 1: Sorting + Connected Components

• Intuition:
  - By pairing each element with its index and sorting by value, elements within the same swappable group appear as contiguous blocks where adjacent elements differ by <= limit.
  - Sorting the original indices of each group allows us to place the smallest sorted values into the smallest sorted positions.

• Approach:
  - Store pairs of {nums[i], i} and sort them in ascending order.
  - Traverse the sorted pairs to find contiguous groups where the difference between adjacent elements is <= limit.
  - For each group, collect their original indices, sort the indices, and map the sorted values back to these sorted indices.

• Why it Works:
  - Sorting groups connected components in O(N log N) time without needing an explicit DSU.
  - Greedily placing the smallest values in the smallest indices within each valid component ensures the lexicographically smallest arrangement.

• Time Complexity (TC): O(N log N) due to sorting.
• Space Complexity (SC): O(N) for storing pairs, groups, and result arrays.
=========================================================
*/

/*
=========================================================
FINAL APPROACH SELECTION:
- The Sorting + Connected Components approach is chosen because it efficiently handles transitive swaps in O(N log N) time and fixes the out-of-bounds/logic bugs present in the previous iteration.
=========================================================
*/

#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<int> lexicographicallySmallestArray(std::vector<int>& nums, int limit) {
        int n = nums.size();
        std::vector<std::pair<int, int>> arr(n);
        for (int i = 0; i < n; ++i) {
            arr[i] = {nums[i], i};
        }

        // Sort based on element values
        std::sort(arr.begin(), arr.end());

        std::vector<int> res(n);
        int i = 0;
        while (i < n) {
            int j = i;
            while (j + 1 < n && arr[j + 1].first - arr[j].first <= limit) {
                j++;
            }

            // Collect indices for the current group
            std::vector<int> indices;
            for (int k = i; k <= j; ++k) {
                indices.push_back(arr[k].second);
            }

            // Sort indices so we can assign values in increasing order of index
            std::sort(indices.begin(), indices.end());

            // Assign sorted values to sorted indices
            for (int k = 0; k < indices.size(); ++k) {
                res[indices[k]] = arr[i + k].first;
            }

            i = j + 1;
        }

        return res;
    }
};
