/*
=========================================================
Date        : 12-10-2026
Problem Name: Apply Operations on Array to Maximize Sum of Squares
Platform    : LeetCode
Difficulty  : Hard
Tags        : Array, Greedy, Bit Manipulation

Problem Summary:
- Given an array of integers and an integer k, you can perform bitwise AND and OR operations simultaneously on any two elements.
- The total sum of set bits across all elements remains invariant under these operations.
- Choose $k$ elements from the final array to maximize the sum of their squares modulo $10^9 + 7$.

Key Observation:
- Bitwise operations between two numbers transfer individual set bits without changing the total count of set bits in each column.
- To maximize the sum of squares, we should greedily pack as many set bits as possible into the top $k$ chosen numbers because squaring heavily favors larger numbers.
=========================================================
*/

/*
=========================================================
APPROACH EXPLANATION
=========================================================

1. Greedy Bit Counting
   • Intuition: The bitwise operation preserves the column sum of each bit position across the entire array.
   • Approach: Count how many numbers have the $i$-th bit set for every bit position from 0 to 31.
   • Why it Works: Since larger numbers contribute exponentially more to the sum of squares due to squaring, we should concentrate the available set bits into $k$ distinct numbers.
   • Time Complexity (TC): O(N * 32)
   • Space Complexity (SC): O(32)

2. Reconstruction and Summation
   • Intuition: Distribute the collected counts of set bits to form $k$ maximally large numbers.
   • Approach: For each of the $k$ slots, construct a number by setting its $j$-th bit if at least one bit remains in the $j$-th position bucket.
   • Why it Works: Greedily building the top $k$ numbers from the most significant bit downward yields the globally optimal maximum sum of squares.
   • Time Complexity (TC): O(K * 32)
   • Space Complexity (SC): O(1)

=========================================================
FINAL APPROACH
=========================================================
- We use a greedy bit-frequency counting approach combined with bit reconstruction.
- It is optimal because concentrating set bits into fewer numbers yields a strictly greater sum of squares than spreading them out, adhering to the mathematical property of convex functions like squaring.
=========================================================
*/

#include <vector>

class Solution {
public:
    int maxSum(std::vector<int>& nums, int k) {
        // Step 1: Count frequency of each bit position being set across all numbers
        std::vector<int> bit_counts(32, 0);
        for (int num : nums) {
            for (int i = 0; i < 32; ++i) {
                if ((num >> i) & 1) {
                    bit_counts[i]++;
                }
            }
        }

        long long total_sum = 0;
        long long mod = 1e9 + 7;

        // Step 2: Greedily construct the top k numbers
        for (int step = 0; step < k; ++step) {
            long long current_num = 0;
            for (int i = 0; i < 32; ++i) {
                if (bit_counts[i] > 0) {
                    current_num |= (1LL << i);
                    bit_counts[i]--;
                }
            }
            total_sum = (total_sum + (current_num * current_num) % mod) % mod;
        }

        return total_sum;
    }
};
