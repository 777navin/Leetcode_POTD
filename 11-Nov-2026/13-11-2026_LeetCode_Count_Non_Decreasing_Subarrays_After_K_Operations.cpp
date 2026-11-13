/*
=========================================================
Date        : 13-11-2026
Problem Name: Count Non-Decreasing Subarrays After K Operations
Platform    : LeetCode
Difficulty  : Hard
Tags        : Array, Stack, Sliding Window, Monotonic Queue, Monotonic Stack

Problem Summary:
Given an array nums of n integers and an integer k, return the number of 
subarrays that can be made non-decreasing after performing at most k 
increments across elements in the subarray. Each subarray is evaluated independently.

Key Observation:
Processing the sliding window from right to left using a monotonic decreasing 
deque of indices allows us to compute the operational cost in O(1) amortized 
time when extending the left boundary or shrinking the right boundary.
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Brute Force (Check all subarrays)
---------------------------------------------------------
• Intuition:
  Iterate through all possible subarrays nums[i...j], simulate making each 
  subarray non-decreasing greedily, and check if total operations <= k.

• Approach:
  For each pair (i, j) with 0 <= i <= j < n, compute the minimum operations 
  required to make nums[i...j] non-decreasing. If ops <= k, increment count.

• Why it Works:
  Exhaustively checks every single subarray option.

• Time Complexity (TC): O(n^3) or O(n^2).
• Space Complexity (SC): O(1).
---------------------------------------------------------
*/

/*
---------------------------------------------------------
APPROACH 2: Sliding Window + Monotonic Deque (Optimal)
---------------------------------------------------------
• Intuition:
  If a subarray nums[l...r] can be made non-decreasing within k operations, 
  all smaller sub-intervals within it also satisfy the condition. 
  By iterating the left pointer i backwards and maintaining a monotonic 
  decreasing queue of indices, we can dynamically track operations.

• Approach:
  - Maintain a deque storing indices of elements in non-increasing order.
  - Iterate `i` backwards from n-1 down to 0, updating `cost` when `nums[i]` is greater 
    than previous elements in the deque.
  - If `cost` exceeds `k`, shrink the window from the right (`j`) and adjust the `cost`.
  - Add the valid window length (`j - i + 1`) to the answer at each step.

• Why it Works:
  The monotonic deque ensures each element is pushed and popped at most once, 
  yielding linear amortized time complexity and avoiding redundant sub-interval checks.

• Time Complexity (TC): O(n) amortized.
• Space Complexity (SC): O(n) for the deque.
---------------------------------------------------------
*/

/*
---------------------------------------------------------
FINAL APPROACH
---------------------------------------------------------
• Why this approach is chosen:
  The right-to-left sliding window with a monotonic deque achieves O(n) linear time 
  complexity, easily handling constraints up to n = 10^5 and avoiding Time Limit Exceeded (TLE).
• Why it is better than previous ones:
  It eliminates redundant recalculations of subarray operations by leveraging 
  monotonicity and sliding window invariants in O(n) instead of O(n^2) or O(n^3).
*/

#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        long long ans = 0;
        long long cost = 0;
        
        // Store indices of `nums` with `nums[i]` in non-increasing order.
        deque<int> dq;
        
        for (int i = nums.size() - 1, j = nums.size() - 1; i >= 0; --i) {
            const int num = nums[i];
            
            // Maintain monotonic decreasing order in the deque
            while (!dq.empty() && nums[dq.back()] < num) {
                const int l = dq.back();
                dq.pop_back();
                const int r = dq.empty() ? j + 1 : dq.back();
                
                // Adjust `nums[l]` to `num` and add operational cost
                cost += static_cast<long long>(r - l) * (num - nums[l]);
            }
            
            dq.push_back(i);
            
            // Shrink the window from the right if cost exceeds k
            while (cost > k) {
                cost -= nums[dq.front()] - nums[j];
                if (dq.front() == j) {
                    dq.pop_front();
                }
                --j;
            }
            
            // All subarrays starting at i and ending from i to j are valid
            ans += (j - i + 1);
        }
        
        return ans;
    }
};
