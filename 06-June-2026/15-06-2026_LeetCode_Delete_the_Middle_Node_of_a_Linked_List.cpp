/*
Date: 15-06-2026
Problem Name: Delete the Middle Node of a Linked List
Platform: LeetCode
Difficulty: Medium
Tags: Linked List, Two Pointers

Problem Summary:
Given the head of a linked list, delete the middle node and return the head of the modified linked list.
The middle node is defined as the ⌊n / 2⌋-th node using 0-based indexing.

Methods to Solve:
1. Two-Pass Approach (Find Size)
2. Optimal Approach (Slow and Fast Pointers)

For EACH method include:

- Method 1: Two-Pass Approach
  - Intuition: Calculate the total length of the list, then traverse again to reach the node just before the middle.
  - Approach: 
    1. Count nodes to find n.
    2. Calculate mid = n / 2.
    3. Iterate to (mid - 1) node.
    4. Update next pointer to skip the middle node.
  - Time Complexity: O(n)
  - Space Complexity: O(1)
  - Why better: Simple to understand, but requires two passes over the list.

- Method 2: Optimal Approach (Slow and Fast Pointers)
  - Intuition: Use a "slow" pointer moving 1 step and a "fast" pointer moving 2 steps. When the fast pointer reaches the end, the slow pointer will be at the node before the middle.
  - Approach: 
    1. Handle edge case (n=1).
    2. Initialize slow = head, fast = head (or move fast 2 steps ahead to track the predecessor).
    3. Move fast at 2x speed and slow at 1x speed.
    4. Remove the node after slow.
  - Time Complexity: O(n)
  - Space Complexity: O(1)
  - Why better: Single pass traversal.

Comparison Table:
Method | TC | SC | Best Use Case
Two-Pass | O(n) | O(1) | When clarity is prioritized
Fast/Slow | O(n) | O(1) | Optimal performance, production code

Final Recommended Solution: Method 2 (Two Pointers)
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

class Solution {
public:
    // Method 1: Two-Pass Approach
    ListNode* deleteMiddleTwoPass(ListNode* head) {
        if (!head || !head->next) return nullptr;
        
        int n = 0;
        ListNode* curr = head;
        while (curr) {
            n++;
            curr = curr->next;
        }
        
        int mid = n / 2;
        curr = head;
        for (int i = 0; i < mid - 1; ++i) {
            curr = curr->next;
        }
        
        curr->next = curr->next->next;
        return head;
    }

    // Method 2: Optimal Two-Pointers Approach
    ListNode* deleteMiddle(ListNode* head) {
        if (!head || !head->next) return nullptr;
        
        // Use a dummy or offset logic to stop at the node before the middle
        ListNode* slow = head;
        ListNode* fast = head->next->next;
        
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        // slow is now at the node before the middle
        slow->next = slow->next->next;
        
        return head;
    }
};
