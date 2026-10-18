/*
=========================================================
Date        : 18-10-2026
Problem Name: Number of Ways to Reorder Array to Get Same BST
Platform    : LeetCode (1569)
Difficulty  : Hard
Tags        : BST, Divide & Conquer, Combinatorics, DP, Math

Problem Summary:
- Given a permutation nums, build a BST by inserting elements
  in order.
- Count the number of different reorderings that generate the
  exact same BST.
- Return the answer modulo 1e9+7.
- Exclude the original ordering from the final answer.

Key Observation:
- Root must remain the same.
- Left and right subtree elements can be interleaved while
  preserving their relative internal order.
=========================================================
*/

class Solution {
    /*
    =========================================================
    APPROACH 1: Generate All Permutations (Brute Force)
    =========================================================
    Intuition:
    - Try every permutation and build the BST.

    Approach:
    - Generate all possible reorderings.
    - Compare resulting BST with original BST.

    Why it Works:
    - Directly checks every candidate ordering.

    TC:
    - O(n! * n)

    SC:
    - O(n!)
    */

    /*
    =========================================================
    APPROACH 2: Recursive Counting + Combinations
    =========================================================
    Intuition:
    - First element is always the root.
    - Elements smaller than root go left.
    - Elements greater than root go right.

    Approach:
    - Recursively count ways for left subtree.
    - Recursively count ways for right subtree.
    - Merge left and right sequences using combinations.

    Why it Works:
    - Relative ordering inside each subtree must remain valid.
    - Only interleaving positions can vary.

    TC:
    - O(n^2)

    SC:
    - O(n^2)
    */

    /*
    =========================================================
    FINAL APPROACH
    =========================================================
    We use recursive divide-and-conquer with combinatorics.
    For each node, count ways for left and right subtrees,
    then choose positions for left subtree elements among all
    remaining positions using nCr. This efficiently counts
    all valid interleavings that preserve the same BST.
    =========================================================
    */

    static constexpr long long MOD = 1000000007LL;
    vector<vector<long long>> nCr;

    long long countWays(vector<int>& nums) {
        int n = nums.size();

        if (n <= 2)
            return 1;

        vector<int> leftSubtree;
        vector<int> rightSubtree;

        int root = nums[0];

        for (int i = 1; i < n; i++) {
            if (nums[i] < root)
                leftSubtree.push_back(nums[i]);
            else
                rightSubtree.push_back(nums[i]);
        }

        long long leftWays = countWays(leftSubtree);
        long long rightWays = countWays(rightSubtree);

        long long waysToMerge =
            nCr[n - 1][leftSubtree.size()];

        return (((waysToMerge * leftWays) % MOD) *
                rightWays) % MOD;
    }

public:
    int numOfWays(vector<int>& nums) {
        int n = nums.size();

        nCr.assign(n + 1, vector<long long>(n + 1, 0));

        for (int i = 0; i <= n; i++) {
            nCr[i][0] = 1;
            nCr[i][i] = 1;

            for (int j = 1; j < i; j++) {
                nCr[i][j] =
                    (nCr[i - 1][j - 1] +
                     nCr[i - 1][j]) % MOD;
            }
        }

        long long result = countWays(nums);

        // Exclude original ordering.
        return (result - 1 + MOD) % MOD;
    }
};
