/*
Date: 14-06-2026
Problem Name: Maximum Twin Sum of a Linked List
Platform: LeetCode
Difficulty: Medium
Tags: Linked List, Two Pointers, Stack

Problem Summary:
In a linked list of size n (where n is even), the twin of the i-th node (0-indexed) 
is the (n-1-i)-th node. The twin sum is the sum of a node and its twin. 
Find the maximum twin sum of the linked list.

Methods to Solve:
1. Brute Force (Using Extra Space/Stack):
   - Intuition: Store all node values in a vector or stack, then calculate sum of pairs from both ends.
   - Approach: Traverse list, push values into vector. Use two pointers to calculate sums.
   - Time Complexity: O(n)
   - Space Complexity: O(n)

2. Optimal Approach (Reversing Second Half):
   - Intuition: Reverse the second half of the linked list to align the twin nodes.
   - Approach:
     a) Use slow and fast pointers to find the middle of the list.
     b) Reverse the second half of the list starting from the middle.
     c) Use two pointers (one at head, one at middle) to calculate twin sums.
   - Time Complexity: O(n)
   - Space Complexity: O(1)

Comparison Table:
Method | TC | SC | Best Use Case
-------|----|----|--------------
Vector/Stack | O(n) | O(n) | Simple implementation
Two Pointers | O(n) | O(1) | Optimal memory usage (Recommended)

Final Recommended Solution: Two Pointers with Half-List Reversal
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 * int val;
 * ListNode *next;
 * ListNode() : val(0), next(nullptr) {}
 * ListNode(int x) : val(x), next(nullptr) {}
 * ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

#include <algorithm>
#include <vector>

class Solution {
public:
    int pairSum(ListNode* head) {
        // 1. Find the middle of the linked list using slow and fast pointers
        ListNode* slow = head;
        ListNode* fast = head;
        
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        // 2. Reverse the second half of the list
        ListNode* prev = nullptr;
        ListNode* curr = slow;
        while (curr != nullptr) {
            ListNode* nextNode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextNode;
        }
        
        // 3. Calculate twin sums and find the maximum
        int maxTwinSum = 0;
        ListNode* firstHalf = head;
        ListNode* secondHalf = prev; // Start of reversed second half
        
        while (secondHalf != nullptr) {
            maxTwinSum = std::max(maxTwinSum, firstHalf->val + secondHalf->val);
            firstHalf = firstHalf->next;
            secondHalf = secondHalf->next;
        }
        
        return maxTwinSum;
    }
};
