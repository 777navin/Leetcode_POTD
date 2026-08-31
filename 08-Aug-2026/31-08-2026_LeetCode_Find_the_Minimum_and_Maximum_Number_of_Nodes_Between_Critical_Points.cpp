/*
=========================================================
Date        : 31-08-2026
Problem Name: Find the Minimum and Maximum Number of Nodes Between Critical Points
Platform    : LeetCode
Difficulty  : Medium
Tags        : Linked List, Two Pointers

Problem Summary:
Identify all critical points (local maxima or minima) in a given singly linked list.
Calculate and return the minimum and maximum distance between any two distinct critical points.
Return [-1, -1] if there are fewer than two critical points.

Key Observation:
- Maximum distance is always between the first and the last critical point.
- Minimum distance is always between two adjacent critical points.
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Vector / Array Storage (Brute / Better)
---------------------------------------------------------
• Intuition:
  Traverse the linked list, check each node with its neighbors, and store the 1-based indices of all critical points into a dynamic array.

• Approach:
  1. Iterate with three pointers: prev, curr, and curr->next.
  2. If curr is strictly greater or strictly smaller than both neighbors, push index to array.
  3. If array size < 2, return [-1, -1].
  4. Max distance = array.back() - array.front().
  5. Min distance = minimum difference between consecutive elements in the array.

• Why it Works:
  Linear traversal preserves sorted index order, making consecutive differences easy to compute.

• TC: O(N) — Single pass to find points and another pass over critical indices.
• SC: O(N) — Extra space used to store critical point indices.
---------------------------------------------------------

---------------------------------------------------------
APPROACH 2: Single-Pass In-Place Tracking (Most Optimal)
---------------------------------------------------------
• Intuition:
  We only need the first critical point, the most recent critical point, and the running minimum distance between consecutive critical points. Storing all indices is redundant.

• Approach:
  1. Maintain variables: `firstIndex`, `prevIndex`, `minIndex`, and `minDist`.
  2. Traverse with `prev`, `curr`, and `curr->next` tracking 1-based index `i`.
  3. When a critical point is found:
     - If `firstIndex == -1`, set `firstIndex = i`.
     - Else, update `minDist = min(minDist, i - prevIndex)`.
     - Update `prevIndex = i`.
  4. If fewer than 2 critical points were found, return [-1, -1].
  5. Otherwise, return [minDist, prevIndex - firstIndex].

• Why it Works:
  Adjacent critical points yield the minimum distance, while the first and last yield the maximum distance. Keeping only boundary and adjacent states maintains full correctness.

• TC: O(N) — One single pass through the linked list.
• SC: O(1) — Constant extra space used for tracking variables.
---------------------------------------------------------
*/

/*
=========================================================
FINAL APPROACH: Single-Pass In-Place Tracking
=========================================================
• Eliminates the auxiliary array completely, achieving O(1) auxiliary space complexity.
• Solves the problem in a single pass of the linked list without extra allocations.
• Optimal in both time O(N) and space O(1).
*/

#include <vector>
#include <algorithm>
#include <climits>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution {
public:
    std::vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        // Base edge case: need at least 3 nodes to have any critical point
        if (!head || !head->next || !head->next->next) {
            return {-1, -1};
        }

        int firstIndex = -1;
        int prevIndex = -1;
        int minDist = INT_MAX;

        ListNode* prev = head;
        ListNode* curr = head->next;
        int currentIndex = 2; // 1-based index for `curr`

        while (curr->next != nullptr) {
            ListNode* nextNode = curr->next;

            // Check if current node is local maxima or minima
            bool isLocalMaxima = (curr->val > prev->val) && (curr->val > nextNode->val);
            bool isLocalMinima = (curr->val < prev->val) && (curr->val < nextNode->val);

            if (isLocalMaxima || isLocalMinima) {
                if (firstIndex == -1) {
                    firstIndex = currentIndex;
                } else {
                    minDist = std::min(minDist, currentIndex - prevIndex);
                }
                prevIndex = currentIndex;
            }

            prev = curr;
            curr = nextNode;
            currentIndex++;
        }

        // If fewer than two critical points exist
        if (firstIndex == -1 || prevIndex == firstIndex) {
            return {-1, -1};
        }

        int maxDist = prevIndex - firstIndex;
        return {minDist, maxDist};
    }
};
