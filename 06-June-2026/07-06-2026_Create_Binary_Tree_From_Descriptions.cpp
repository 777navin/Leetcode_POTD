/*
Date: 07-06-2026
Problem Name: Create Binary Tree From Descriptions
Platform: LeetCode
Difficulty: Medium
Tags: Array, Hash Table, Tree, Binary Tree

Problem Summary:
Construct a binary tree from a 2D array of descriptions where each description
is [parent, child, isLeft]. isLeft=1 indicates the child is the left child, 
and isLeft=0 indicates it is the right child. Return the root of the tree.

Methods to Solve:
1. Hash Map + Set Approach (Optimal)

For the Optimal Approach:
- Intuition: Use a hash map to store node values and their corresponding TreeNode pointers. 
  Use a hash set to keep track of all children nodes. The root will be the only node
  that appears as a parent but never as a child.
- Approach: 
  1. Map all values to TreeNode pointers.
  2. Use a set to mark all nodes that are children.
  3. Iterate through descriptions:
     a. Create parent and child nodes if they don't exist.
     b. Link parent to child based on isLeft.
     c. Add child to the child set.
  4. Find the root by iterating through the map and picking the node not in the child set.
- Dry Run: 
  Input: [[20,15,1],[20,17,0],[50,20,1]]
  - Map: {20: Node(20), 15: Node(15), 17: Node(17), 50: Node(50)}
  - Children Set: {15, 17, 20}
  - Root: 50 (exists in map, not in set)
- Time Complexity: O(N) where N is the number of descriptions.
- Space Complexity: O(N) to store the map and set.
- Why better: Single pass construction and efficient lookup.
- When to use: When tree construction is based on parent-child relations.

Comparison Table:
Method | TC | SC | Best Use Case
Hash Map | O(N) | O(N) | General tree construction

Final Recommended Solution: Hash Map + Set Approach
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 * int val;
 * TreeNode *left;
 * TreeNode *right;
 * TreeNode() : val(0), left(nullptr), right(nullptr) {}
 * TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 * TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
public:
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
        unordered_map<int, TreeNode*> nodes;
        unordered_set<int> children;
        
        // Build the tree nodes and establish parent-child relationships
        for (const auto& desc : descriptions) {
            int pVal = desc[0];
            int cVal = desc[1];
            int isLeft = desc[2];
            
            if (nodes.find(pVal) == nodes.end()) nodes[pVal] = new TreeNode(pVal);
            if (nodes.find(cVal) == nodes.end()) nodes[cVal] = new TreeNode(cVal);
            
            if (isLeft) {
                nodes[pVal]->left = nodes[cVal];
            } else {
                nodes[pVal]->right = nodes[cVal];
            }
            
            children.insert(cVal);
        }
        
        // The root is the node that is never a child
        for (const auto& desc : descriptions) {
            if (children.find(desc[0]) == children.end()) {
                return nodes[desc[0]];
            }
        }
        
        return nullptr;
    }
};
