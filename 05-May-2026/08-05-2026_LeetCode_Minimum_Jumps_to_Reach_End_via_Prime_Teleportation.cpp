// File: 08-05-2026_LeetCode_Minimum_Jumps_to_Reach_End_via_Prime_Teleportation.cpp

/*
Date: 08-05-2026
Problem Name: Minimum Jumps to Reach End via Prime Teleportation
Platform: LeetCode
Difficulty: Medium
Tags: Array, Hash Table, Math, Breadth-First Search, Number Theory

Problem Summary:
You are given an integer array `nums` of length `n`. Starting at index 0, you want to reach index `n - 1`.
From index `i`, you can:
1. Move to `i + 1` or `i - 1` (adjacent steps).
2. If `nums[i]` is a prime number `p`, instantly jump to any index `j != i` where `nums[j] % p == 0`.
Return the minimum number of jumps required to reach the last index.

Methods to Solve:
1. Brute Force (Standard BFS without Prime Precomputation)
2. Optimal Approach (BFS with Prime Sieve and Factorization Buckets)

For EACH method include:

---
### 1. Brute Force 
- Intuition: At every step, we check all possible adjacent moves and, if the current element is prime, we iterate through the entire array to find all multiples of this prime.
- Approach: Use a standard Breadth-First Search (BFS) queue. For the current index `u`, push `u - 1` and `u + 1`. If `nums[u]` is prime, loop `j` from 0 to `n-1` and push `j` if `nums[j] % nums[u] == 0`.
- Dry Run (small example): nums = [2, 3, 4, 7, 9]
  - Start at 0 (value 2). Prime! Check all elements % 2 == 0. Found index 2 (value 4). Add indices 1 and 2 to Queue.
  - Next in queue: 1 (value 3). Prime! Check all elements % 3 == 0. Found index 4 (value 9). Add index 4 to Queue.
  - Next reach 4, which is the end. Distance = 2.
- Time Complexity: O(N^2) in the worst case (e.g., repeatedly looping over the array to find multiples).
- Space Complexity: O(N) for the BFS queue and visited array.
- Why better than previous method: N/A (Baseline).
- When to use: Only when N is very small (N <= 1000).

---
### 2. Optimal Approach
- Intuition: Finding multiples on the fly is too slow. Instead, we can precompute the prime factors of every number in the array. We can map each prime factor to the list of indices where it appears using buckets. When teleporting via a prime `p`, we just fetch all indices from its bucket directly.
- Approach:
  1. Use Sieve of Eratosthenes to precompute primes and the Smallest Prime Factor (SPF) for fast factorization up to the max value (10^6).
  2. Iterate through `nums` and factorize each number. If prime factor `p` divides `nums[i]`, add index `i` to `bucket[p]`.
  3. Initialize a BFS with a `dist` array set to -1. Start at index 0.
  4. Dequeue `u`. Check adjacent indices `u - 1` and `u + 1`.
  5. If `nums[u]` is prime and hasn't been used for teleportation yet, iterate through all indices `v` in `bucket[nums[u]]`. Push unvisited indices to the queue.
  6. Mark the prime `nums[u]` as used so we never process its bucket again, preventing redundant work.
- Dry Run (small example): nums = [2, 3, 4, 7, 9]
  - Sieve identifies primes. 
  - Buckets: `bucket[2] = {0, 2}`, `bucket[3] = {1, 4}`, `bucket[7] = {3}`.
  - BFS Q=[0], dist[0]=0.
  - Pop 0. `nums[0]=2` (Prime). Add adj `1`. Teleport via `bucket[2]` -> index `2`. Q=[1, 2]. Mark prime 2 used.
  - Pop 1. `nums[1]=3` (Prime). Add adj `0` (visited), `2` (visited). Teleport via `bucket[3]` -> index `4`. Q=[2, 4]. Mark prime 3 used.
  - Pop 2. `nums[2]=4` (Not Prime). Adj: `1` (visited), `3`. Q=[4, 3].
  - Pop 4. Target reached! Return `dist[4]` which is 2.
- Time Complexity: O(N log(log(MAX_VAL)) + N) -> Roughly O(N). Sieve takes O(MAX_VAL log(log(MAX_VAL))), factorizing takes O(log(MAX_VAL)) per element. The BFS processes each index and each prime bucket at most once.
- Space Complexity: O(MAX_VAL + N). Sieve and SPF arrays take O(MAX_VAL). The buckets and queue take O(N) space.
- Why better than previous method: Avoids the O(N^2) inner loop during BFS by precomputing and amortizing the cost via smart bucket retrieval.
- When to use: Always, especially suitable for competitive programming constraints (N = 10^5).

---
Comparison Table:
Method       | TC          | SC             | Best Use Case
-------------------------------------------------------------------------
Brute Force  | O(N^2)      | O(N)           | Small arrays (N < 10^3)
Optimal      | O(N)        | O(MAX_VAL + N) | Strict constraints (N = 10^5)

Final Recommended Solution: Optimal Approach
*/

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Fast I/O for Competitive Programming
auto init = []() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 'c';
}();

class Solution {
private:
    static const int MAX_VAL = 1000005;
    static bool sieve_computed;
    static int spf[MAX_VAL];
    static bool is_prime[MAX_VAL];

    static void compute_sieve() {
        if (sieve_computed) return;
        
        fill(is_prime, is_prime + MAX_VAL, true);
        is_prime[0] = is_prime[1] = false;
        
        for (int i = 2; i < MAX_VAL; i++) {
            spf[i] = i;
        }

        for (int i = 2; i * i < MAX_VAL; i++) {
            if (is_prime[i]) {
                for (int j = i * i; j < MAX_VAL; j += i) {
                    is_prime[j] = false;
                    if (spf[j] == j) {
                        spf[j] = i;
                    }
                }
            }
        }
        sieve_computed = true;
    }

public:
    Solution() {
        compute_sieve();
    }

    int minJumps(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return 0;

        // bucket[p] stores all indices j where nums[j] is a multiple of prime p
        unordered_map<int, vector<int>> bucket;
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            while (x > 1) {
                int p = spf[x];
                bucket[p].push_back(i);
                // Remove all factors of prime p
                while (x % p == 0) {
                    x /= p;
                }
            }
        }

        vector<int> dist(n, -1);
        vector<bool> prime_used(MAX_VAL, false);
        queue<int> q;

        q.push(0);
        dist[0] = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            if (u == n - 1) {
                return dist[u];
            }

            // 1. Adjacent Steps
            if (u + 1 < n && dist[u + 1] == -1) {
                dist[u + 1] = dist[u] + 1;
                q.push(u + 1);
            }
            if (u - 1 >= 0 && dist[u - 1] == -1) {
                dist[u - 1] = dist[u] + 1;
                q.push(u - 1);
            }

            // 2. Prime Teleportation
            if (is_prime[nums[u]]) {
                int p = nums[u];
                if (!prime_used[p]) {
                    prime_used[p] = true; // Mark as used to prevent TLE
                    for (int v : bucket[p]) {
                        if (dist[v] == -1) {
                            dist[v] = dist[u] + 1;
                            q.push(v);
                        }
                    }
                }
            }
        }
        
        return -1; 
    }
};

// Initialize static members
bool Solution::sieve_computed = false;
int Solution::spf[1000005];
bool Solution::is_prime[1000005];


// ==========================================
// FULL DRIVER CODE FOR LOCAL RUNNABILITY
// ==========================================
int main() {
    Solution sol;
    
    // Test Case 1
    vector<int> nums1 = {1, 2, 4, 6};
    cout << "Test Case 1: " << sol.minJumps(nums1) << " (Expected: 2)\n";

    // Test Case 2
    vector<int> nums2 = {2, 3, 4, 7, 9};
    cout << "Test Case 2: " << sol.minJumps(nums2) << " (Expected: 2)\n";

    // Test Case 3
    vector<int> nums3 = {4, 6, 5, 8};
    cout << "Test Case 3: " << sol.minJumps(nums3) << " (Expected: 3)\n";

    return 0;
}
