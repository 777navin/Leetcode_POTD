/*
=========================================================
Date        : 18-07-2026
Problem Name: Find Greatest Common Divisor of Array
Platform    : LeetCode
Difficulty  : Easy
Tags        : Array, Math, Number Theory

Problem Summary:
Given an integer array nums, find the minimum and maximum 
elements present in the array. Return the greatest common 
divisor (GCD) of these two numbers.

Key Observation:
Instead of sorting the entire array, we can find the minimum 
and maximum elements in a single linear scan or using efficient 
STL algorithms, and then compute their GCD using std::gcd.
=========================================================
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
3. APPROACH EXPLANATION
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

• Approach 1: Sorting
    - Intuition: Sorting the array brings the smallest element to the front and the largest element to the end.
    - Approach: Sort the array using std::sort, pick nums[0] as minimum and nums[n-1] as maximum, then find their GCD.
    - Why it Works: Sorting inherently places the absolute minimum and maximum at the boundaries of the array.
    - TC: O(N log N) where N is the length of the array due to sorting.
    - SC: O(1) or O(log N) depending on the internal sort implementation.

• Approach 2: Linear Scan (Optimized)
    - Intuition: We only need the global minimum and global maximum; tracking them directly avoids the sorting overhead.
    - Approach: Use std::min_element and std::max_element (or a single pass loop) to locate the boundary values, then pass them to std::gcd.
    - Why it Works: Elements are checked sequentially to find bounds without changing their order, matching the theoretical lower bound for finding extremes.
    - TC: O(N) since we visit the array elements a constant number of times.
    - SC: O(1) as no auxiliary space is required.
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
4. FINAL APPROACH
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Why this approach is chosen: Approach 2 is selected because it runs in linear time, significantly outperforming the sorting method for larger arrays.
• Why it is better than the previous ones: It avoids the O(N log N) sorting bottleneck, processing the constraints efficiently while using standard library utilities for clean and optimal execution.
*/

class Solution {
public:
    int findGCD(vector<int>& nums) {
        // Fast I/O optimization within LeetCode
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        
        // Find the minimum and maximum elements in the array
        int mini = *min_element(nums.begin(), nums.end());
        int maxi = *max_element(nums.begin(), nums.end());
        
        // Return the greatest common divisor using standard library utility
        return std::gcd(mini, maxi);
    }
};
