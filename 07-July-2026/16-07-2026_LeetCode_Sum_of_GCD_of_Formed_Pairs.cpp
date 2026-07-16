/*
=========================================================
Date        : 16-07-2026
Problem Name: 3867. Sum of GCD of Formed Pairs
Platform    : LeetCode
Difficulty  : Medium
Tags        : Array, Math, Two Pointers, Sorting, Simulation, Number Theory

Problem Summary:
Given an array, create a new array where each element is the GCD of the current element and the maximum element seen so far. Sort this array, pair the smallest and largest unpaired elements iteratively, and return the sum of the GCDs of these pairs (ignoring the middle element if odd).

Key Observation:
Computing the running maximum and sorting takes O(N log N). Pairing smallest and largest optimally utilizes a classic two-pointer technique where the middle element is naturally skipped if the array length is odd.
=========================================================
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH EXPLANATION
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

1. Optimal Simulation & Two Pointers
• Intuition: The constraints (N = 10^5) allow for an O(N log N) approach, which perfectly aligns with directly simulating the problem instructions.
• Approach: First, build the `prefixGcd` array by tracking the running maximum and calculating the GCD. Then, sort the array. Finally, use a two-pointer approach (left at 0, right at n-1) to compute the GCD of pairs and sum them up.
• Why it Works: Sorting fulfills the non-decreasing requirement. The two-pointer (`left < right`) inherently forms the correct pairs and safely ignores any middle element in an odd-length array without extra checks.
• Time Complexity (TC): O(N log N) dominated by the sorting step. The GCD calculations take O(log(min(a,b))) per step.
• Space Complexity (SC): O(N) to store the intermediate `prefixGcd` array.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
FINAL APPROACH
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Why this approach is chosen: It directly and efficiently models the problem constraints.
• Why it is better than the previous ones: This is the optimal and most straightforward way to solve this specific constraint set without overcomplicating the math.
*/

#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    long long gcdSum(vector<int>& nums) {
        int n = nums.size();
        vector<int> prefixGcd(n);
        int mx = 0;
        
        // Construct the prefixGcd array
        for (int i = 0; i < n; i++) {
            mx = max(mx, nums[i]);
            prefixGcd[i] = std::gcd(nums[i], mx);
        }
        
        // Sort the array in non-decreasing order
        sort(prefixGcd.begin(), prefixGcd.end());
        
        long long sum = 0;
        int left = 0, right = n - 1;
        
        // Pair the smallest and largest elements
        while (left < right) {
            sum += std::gcd(prefixGcd[left], prefixGcd[right]);
            left++;
            right--;
        }
        
        return sum;
    }
};
