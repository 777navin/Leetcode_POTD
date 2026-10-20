/*
=========================================================
Date        : 20-10-2026
Problem Name: Sum of Sortable Integers
Platform    : LeetCode
Difficulty  : Hard
Tags        : Array, Sorting, Number Theory, String Matching, KMP

Problem Summary:
- Given an array `nums` of size `n`, find the sum of all divisors `k` of `n` such that `nums` can be sorted by partitioning it into blocks of size `k` and cyclically shifting each block.
- The previous brute-force block verification took $O(k^2)$ per block, leading to Time Limit Exceeded (TLE) on large inputs with repetitive elements (e.g., all 1s).

Key Observation:
- Checking if a block `a` is a cyclic shift of the sorted block `b` is equivalent to checking if pattern `b` appears in text `a + a`, which can be efficiently solved in $O(k)$ time using the KMP algorithm with modulo indexing.
=========================================================
*/

/*
APPROACH EXPLANATION:

1. Brute Force Approach (Previous TLE)
   • Intuition: Iterate over divisors, partition into blocks, and test all shift offsets using nested loops.
   • Approach: Check every possible shift offset `pos` from $0$ to $k-1$ for each block of size $k$.
   • Why it Works: Direct simulation of cyclic shift definition, but checking takes $O(k^2)$ per block.
   • Time Complexity (TC): $O(n \cdot \sum k)$, which can reach $O(n^2)$ and cause TLE on large arrays or dense divisor structures.
   • Space Complexity (SC): $O(n)$ for auxiliary arrays.

2. Most Optimal Approach (KMP-based Cyclic Shift Check)
   • Intuition: Reduce the block verification time from $O(k^2)$ to $O(k)$ using string matching (KMP algorithm).
   • Approach: For each block `a` and corresponding sorted block `b`, use KMP with modulo indexing (`a[i % k]`) to check if `b` is a cyclic shift of `a` in $O(k)$ time.
   • Why it Works: KMP precomputes the LPS array in $O(k)$ and performs the search in $O(k)$, eliminating redundant shift checks and avoiding TLE even with identical elements.
   • Time Complexity (TC): $O(d(n) \cdot n)$, where $d(n)$ is the number of divisors of $n$, executing well within time limits.
   • Space Complexity (SC): $O(n)$ to store sorted array and $O(k)$ temporary space for the KMP LPS table.
*/

/*
FINAL APPROACH:
We choose the KMP-based cyclic shift verification because it optimizes the block check from quadratic time $O(k^2)$ to linear time $O(k)$. This brings the total time complexity down to $O(d(n) \cdot n)$, successfully preventing TLE on all edge cases (such as large arrays with identical elements).
*/

#include <vector>
#include <algorithm>

class Solution {
private:
    bool isCyclicShift(const std::vector<int>& a, const std::vector<int>& b) {
        int k = a.size();
        if (k == 0) return true;
        
        // Compute LPS array for pattern b
        std::vector<int> lps(k, 0);
        for (int i = 1, len = 0; i < k; ) {
            if (b[i] == b[len]) {
                lps[i++] = ++len;
            } else if (len) {
                len = lps[len - 1];
            } else {
                lps[i++] = 0;
            }
        }
        
        // Search pattern b in text a + a using modulo indexing
        int i = 0, j = 0;
        while (i < 2 * k) {
            if (a[i % k] == b[j]) {
                i++;
                j++;
                if (j == k) return true;
            } else if (j) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
        return false;
    }

public:
    int sortableIntegers(std::vector<int>& nums) {
        int n = nums.size();

        std::vector<int> sortedNums = nums;
        std::sort(sortedNums.begin(), sortedNums.end());

        std::vector<int> divisors;
        for (int d = 1; d * d <= n; d++) {
            if (n % d == 0) {
                divisors.push_back(d);
                if (d * d != n)
                    divisors.push_back(n / d);
            }
        }

        long long ans = 0;

        for (int k : divisors) {
            bool ok = true;

            for (int start = 0; start < n; start += k) {
                std::vector<int> a(nums.begin() + start, nums.begin() + start + k);
                std::vector<int> b(sortedNums.begin() + start, sortedNums.begin() + start + k);

                if (!isCyclicShift(a, b)) {
                    ok = false;
                    break;
                }
            }

            if (ok) ans += k;
        }

        return (int)ans;
    }
};
