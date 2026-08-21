/*
=========================================================
Date        : 21-08-2026
Problem Name: 3116. Kth Smallest Amount With Single Denomination Combination
Platform    : LeetCode
Difficulty  : Hard
Tags        : Array, Math, Binary Search, Bit Manipulation, Combinatorics, Number Theory

Problem Summary:
Given an array `coins` and an integer `k`, find the k-th smallest amount that 
can be generated using multiples of single denominations from the array. 
Different coin denominations cannot be combined together.

Key Observation:
The count of achievable values $\le x$ increases monotonically with $x$. 
We can binary search the answer $x$ and use the Principle of Inclusion-Exclusion (PIE) 
over coin subsets to count multiples $\le x$.
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Priority Queue / Min-Heap (Brute Force)
---------------------------------------------------------
• Intuition:
  Generate amounts sequentially using a min-heap, popping the minimum and pushing its next multiple.
• Approach:
  Maintain a min-heap of current multiples, pop $k$ times while skipping duplicates to find the k-th value.
• Why it Works:
  Always processes values in increasing numerical order.
• Time Complexity (TC):
  O(k * log(N)) — TLE because $k \le 2 \times 10^9$.
• Space Complexity (SC):
  O(N) for heap storage.

---------------------------------------------------------
APPROACH 2: Binary Search + Principle of Inclusion-Exclusion (PIE) (Optimal)
---------------------------------------------------------
• Intuition:
  Binary search on the target value $x \in [1, \min(coins) \times k]$. Count how many numbers $\le x$ are divisible by at least one coin.
• Approach:
  1. Filter out redundant coins (any coin divisible by a smaller coin).
  2. For a mid value $x$, iterate over all non-empty subsets of size $m \le 15$.
  3. Compute $\text{LCM}$ of the subset. Add $\lfloor x / \text{LCM} \rfloor$ if subset size is odd, subtract if even.
  4. Binary search for the smallest $x$ where count $\ge k$.
• Why it Works:
  Monotonicity of count function guarantees binary search correctness; PIE precisely handles overlapping multiples without duplicate counting.
• Time Complexity (TC):
  O(2^M \cdot \log(\min(coins) \cdot k)), where $M \le 15$ is the number of reduced coins.
• Space Complexity (SC):
  O(M) auxiliary space for filtered coins and subset generation.
*/

/*
---------------------------------------------------------
FINAL APPROACH: Binary Search + Inclusion-Exclusion Principle
---------------------------------------------------------
• Efficiently handles constraints where $k \le 2 \times 10^9$ via logarithmic search.
• Drastically reduces the subset state space by pruning redundant multiples before evaluating bitmasks.
*/

#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
private:
    long long gcd(long long a, long long b) {
        while (b) {
            a %= b;
            swap(a, b);
        }
        return a;
    }

    long long lcm(long long a, long long b) {
        if (a == 0 || b == 0) return 0;
        return (a / gcd(a, b)) * b;
    }

    long long countMultiples(long long mid, const vector<int>& coins) {
        int n = coins.size();
        long long count = 0;
        int totalSubsets = 1 << n;

        for (int mask = 1; mask < totalSubsets; ++mask) {
            long long currentLcm = 1;
            int bits = 0;
            bool overflow = false;

            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) {
                    bits++;
                    currentLcm = lcm(currentLcm, coins[i]);
                    if (currentLcm > mid) {
                        overflow = true;
                        break;
                    }
                }
            }

            if (!overflow) {
                if (bits % 2 == 1) {
                    count += (mid / currentLcm);
                } else {
                    count -= (mid / currentLcm);
                }
            }
        }
        return count;
    }

public:
    long long findKthSmallest(vector<int>& coins, int k) {
        sort(coins.begin(), coins.end());
        vector<int> filteredCoins;

        // Prune redundant denominations
        for (int coin : coins) {
            bool redundant = false;
            for (int existing : filteredCoins) {
                if (coin % existing == 0) {
                    redundant = true;
                    break;
                }
            }
            if (!redundant) {
                filteredCoins.push_back(coin);
            }
        }

        long long low = 1;
        long long high = 1LL * filteredCoins[0] * k;
        long long ans = high;

        while (low <= high) {
            long long mid = low + (high - low) / 2;
            if (countMultiples(mid, filteredCoins) >= k) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        return ans;
    }
};
