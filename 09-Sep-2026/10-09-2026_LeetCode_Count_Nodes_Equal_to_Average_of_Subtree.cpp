/*
=========================================================
Date        : 10-09-2026
Problem Name: Count Nodes Equal to Average of Subtree
Platform    : LeetCode
Difficulty  : Medium
Tags        : Tree, Depth-First Search, Binary Tree

Problem Summary:
Given the root of a binary tree, determine how many nodes have a value 
equal to the average of all values in their subtree. The subtree of a node 
includes itself and all descendants, and the average is rounded down 
to the nearest integer.

Key Observation:
A bottom-up post-order traversal allows each node to compute its subtree 
sum and node count in O(1) from its left and right children before checking 
the condition.
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Brute Force (Top-Down DFS)
---------------------------------------------------------
• Intuition:
  - Traverse every node in the tree and, for each node, trigger a separate DFS 
    traversal to compute the subtree sum and count.
• Approach:
  - For every visited node, invoke a helper function that walks its full subtree, 
    computes sum / count, checks equality with node->val, and repeats for child nodes.
• Why it Works:
  - It directly follows the definition by visiting all descendants independently for each node.
• Time Complexity: O(N^2) in the worst case (skewed tree) because every subtree is recomputed.
• Space Complexity: O(N) auxiliary stack space for the recursion.

---------------------------------------------------------
APPROACH 2: Optimal (Bottom-Up Post-Order Traversal)
---------------------------------------------------------
• Intuition:
  - To avoid redundant recomputations, compute subtree information from leaves up to the root.
• Approach:
  - Use a recursive post-order DFS that returns a pair {subtree_sum, subtree_node_count}.
  - Combine results from left and right children:
      current_sum = left.sum + right.sum + root->val
      current_count = left.count + right.count + 1
  - Check if root->val == current_sum / current_count, increment answer if true, and pass up the pair.
• Why it Works:
  - Post-order guarantees child subtrees are completely resolved before the parent processes them, 
    visiting every node exactly once.
• Time Complexity: O(N) as each tree node is visited once.
• Space Complexity: O(H) where H is the height of the tree (O(N) worst-case, O(log N) balanced).
---------------------------------------------------------
*/

/*
=========================================================
FINAL APPROACH CHOICE:
Bottom-up post-order traversal is chosen because it avoids the 
quadratic O(N^2) overhead of recalculating subtree sums repeatedly. 
It processes the entire tree in a single linear O(N) pass with 
optimal O(H) call stack memory.
=========================================================
*/

#include <utility>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

class Solution {
private:
    int matchingNodesCount = 0;

    // Returns {subtree_sum, subtree_node_count}
    std::pair<int, int> postOrder(TreeNode* node) {
        if (!node) {
            return {0, 0};
        }

        auto [leftSum, leftCount] = postOrder(node->left);
        auto [rightSum, rightCount] = postOrder(node->right);

        int currentSum = leftSum + rightSum + node->val;
        int currentCount = leftCount + rightCount + 1;

        if (node->val == (currentSum / currentCount)) {
            matchingNodesCount++;
        }

        return {currentSum, currentCount};
    }

public:
    int averageOfSubtree(TreeNode* root) {
        matchingNodesCount = 0;
        postOrder(root);
        return matchingNodesCount;
    }
};
