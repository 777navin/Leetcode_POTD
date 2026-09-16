/*
=========================================================
Date        : 16-09-2026
Problem Name: 1621. Number of Sets of K Non-Overlapping Line Segments
Platform: LeetCode
Difficulty: Medium
Tags: Math, Dynamic Programming, Combinatorics

Problem Summary:
Given n points on a 1-D plane, find the number of ways to draw exactly k non-overlapping line segments. 
The line segments are allowed to share endpoints, and the result must be modulo 10^9 + 7.

Key Observation:
Allowing adjacent segments to share endpoints is mathematically equivalent to picking 2k endpoints from n + k - 1 distinct points.
=========================================================
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH EXPLANATION
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

1. Dynamic Programming (Memoization)
• Intuition: At each point, we decide to either start a new segment, extend an ongoing one, or skip the point entirely.
• Approach: Use a 3D DP state: dp(i, k, isStarted) and recursively explore state transitions.
• Why it Works: It strictly follows the rules of forming segments, ensuring we cover exactly k segments over n points.
• Time Complexity (TC): O(N * K) - We compute each of the N * K * 2 states exactly once.
• Space Complexity (SC): O(N * K) - For storing the 3D memoization table.

2. Combinatorics (Math)
• Intuition: If segments couldn't share endpoints, we would just pick 2k distinct points from n points.
• Approach: To account for the possibility of up to k-1 shared endpoints, we add k-1 virtual points, making it a problem of choosing 2k from n + k - 1.
• Why it Works: Choosing 2k distinct points from n + k - 1 creates a perfect mapping (bijection) to our original overlapping segment constraints.
• Time Complexity (TC): O(K) - For calculating the combinations formula (nCr) using modular inverse.
• Space Complexity (SC): O(1) - Only a few integer variables are used.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
FINAL APPROACH
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
The Combinatorics (Math) approach is chosen for the final implementation.
It is vastly superior because it reduces time complexity from O(N*K) to O(K) and space complexity from O(N*K) to O(1), entirely avoiding DP overhead.
*/

class Solution {
private:
    const int MOD = 1e9 + 7;

    // Helper function to calculate (base^exp) % MOD
    long long power(long long base, long long exp) {
        long long res = 1;
        base %= MOD;
        while (exp > 0) {
            if (exp % 2 == 1) res = (res * base) % MOD;
            base = (base * base) % MOD;
            exp /= 2;
        }
        return res;
    }

    // Helper function to find modular inverse
    long long modInverse(long long n) {
        return power(n, MOD - 2);
    }

    // Function to calculate nCr % MOD
    long long nCr(int n, int r) {
        if (r < 0 || r > n) return 0;
        long long num = 1, den = 1;
        for (int i = 0; i < r; i++) {
            num = (num * (n - i)) % MOD;
            den = (den * (i + 1)) % MOD;
        }
        return (num * modInverse(den)) % MOD;
    }

public:
    int numberOfSets(int n, int k) {
        // We want to choose 2k points from (n + k - 1) points
        return nCr(n + k - 1, 2 * k);
    }
};
