/*
=========================================================
Date        : 12-07-2026
Problem Name: Rank Transform of an Array
Platform    : LeetCode
Difficulty  : Easy
Tags        : Array, Hash Table, Sorting

Problem Summary:
Given an array of integers, replace each element with its corresponding rank. 
The rank represents how large the element is, starting from 1 for the smallest element. 
Identical elements must share the exact same rank, and ranks must be consecutive integers.

Key Observation:
Sorting a copy of the unique elements allows us to assign ranks sequentially. 
Mapping each unique value to its rank enables efficient updates to the original array.
=========================================================
*/

#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

/*
=========================================================
APPROACH 1: Sorting and Hash Map (Optimized)
=========================================================
• Intuition:
  To find the rank of each element, we need to know its order relative to the other unique elements. 
  Sorting helps arrange elements from smallest to largest, which directly maps to ranks 1, 2, 3, etc.

• Approach:
  1. Create a duplicate copy of the original array.
  2. Sort the copy in ascending order.
  3. Traverse the sorted array and assign ranks sequentially using an unordered map, ensuring duplicate values share the same rank.
  4. Iterate through the original array and replace each element with its mapped rank from the hash table.

• Why it Works:
  Sorting establishes the relative order of elements, and the hash map prevents duplicate values from advancing the rank counter unnecessarily. 
  Re-indexing from the hash map ensures the final output maintains the original array order.

• Time Complexity (TC):
  $O(N \log N)$ where $N$ is the number of elements in the array due to the sorting operation. Map insertions and lookups take $O(N)$ on average.

• Space Complexity (SC):
  $O(N)$ to store the copy of the array and the rank map mapping unique elements to their integers.
*/

/*
=========================================================
FINAL APPROACH CHOICE
=========================================================
• The Sorting + Hash Map approach is chosen because it directly satisfies all ranking rules optimally.
• It naturally handles duplicates by only incrementing the rank counter when encountering a new unique element.
• With a constraint of up to $10^5$ elements, the $O(N \log N)$ sorting time is highly efficient and comfortably fits within standard execution time limits.
*/

class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        // Handle empty array boundary condition
        if (arr.empty()) return {};

        // Step 1: Clone the original array to preserve original order
        vector<int> sortedArr = arr;

        // Step 2: Sort the cloned array
        sort(sortedArr.begin(), sortedArr.end());

        // Step 3: Map each unique element to its respective rank
        unordered_map<int, int> rankMap;
        int rank = 1;
        
        for (int num : sortedArr) {
            // If the element is not already ranked, assign the current rank and increment
            if (rankMap.find(num) == rankMap.end()) {
                rankMap[num] = rank;
                rank++;
            }
        }

        // Step 4: Transform the original array using the map
        for (int i = 0; i < arr.size(); i++) {
            arr[i] = rankMap[arr[i]];
        }

        return arr;
    }
};
