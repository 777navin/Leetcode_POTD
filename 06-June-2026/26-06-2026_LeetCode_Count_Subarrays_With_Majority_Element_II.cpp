/*
Date: 26-06-2026
Problem Name: Count Subarrays With Majority Element II
Platform: LeetCode
Difficulty: Hard
Tags: Array, Hash Table, Prefix Sum, Fenwick Tree

Problem Summary:
Given an array nums and an integer target, return the number of subarrays where 
target appears strictly more than half of the time (majority element).

Methods to Solve:
1. Brute Force: Iterate over all possible subarrays, count occurrences of target, check condition.
2. Optimal Approach (Prefix Sum + Fenwick Tree/Frequency Map):
   - Transform the array: if nums[i] == target, value = 1; else value = -1.
   - The condition "majority element" implies (count of target) > (count of others).
   - If sum of subarray is > 0, target is the majority element.
   - Using Prefix Sums: Let P[i] be the prefix sum at index i.
   - We need P[j] - P[i-1] > 0 => P[j] > P[i-1] for subarrays [i, j].
   - Use a Fenwick Tree (or Order Statistic Tree) to count pairs (i < j) such that P[j] > P[i].

Comparison Table:
Method         | TC      | SC      | Best Use Case
---------------|---------|---------|----------------
Brute Force    | O(N^2)  | O(1)    | Small constraints
Optimal        | O(N log N)| O(N)    | N up to 10^5

Final Recommended Solution:
The Optimal Approach using prefix sums and a Fenwick Tree for inversion counting.
*/

#include <vector>
#include <algorithm>
#include <map>

using namespace std;

class Solution {
    // Fenwick Tree for prefix sum frequency counting
    struct FenwickTree {
        int size;
        vector<int> tree;
        FenwickTree(int n) : size(n), tree(n + 1, 0) {}
        
        void update(int i, int val) {
            for (; i <= size; i += i & -i) tree[i] += val;
        }
        
        int query(int i) {
            int sum = 0;
            for (; i > 0; i -= i & -i) sum += tree[i];
            return sum;
        }
    };

public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();
        vector<int> pref(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            pref[i + 1] = pref[i] + (nums[i] == target ? 1 : -1);
        }

        // Coordinate compression for prefix sums to use in Fenwick Tree
        vector<int> sorted_pref = pref;
        sort(sorted_pref.begin(), sorted_pref.end());
        sorted_pref.erase(unique(sorted_pref.begin(), sorted_pref.end()), sorted_pref.end());

        auto get_rank = [&](int val) {
            return lower_bound(sorted_pref.begin(), sorted_pref.end(), val) - sorted_pref.begin() + 1;
        };

        FenwickTree ft(sorted_pref.size());
        long long count = 0;

        // Count pairs (i, j) where i < j and pref[j] > pref[i]
        for (int val : pref) {
            int rank = get_rank(val);
            count += ft.query(rank - 1);
            ft.update(rank, 1);
        }

        return count;
    }
};
