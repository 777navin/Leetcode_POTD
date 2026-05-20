// 20-05-2026_LeetCode_Find_the_Prefix_Common_Array_of_Two_Arrays.cpp

/*
Date: 20-05-2026
Problem Name: Find the Prefix Common Array of Two Arrays
Platform: LeetCode
Difficulty: Medium
Tags: Array, Hash Table, Bit Manipulation

Problem Summary:
You are given two 0-indexed integer permutations A and B of length n. A prefix common array of A and B is an array C such that C[i] is equal to the count of numbers that are present at or before the index i in both A and B. Return the prefix common array C.

Methods to Solve:
1. Brute Force
2. Better Approach (Hash Set)
3. Optimal Approach (Frequency Array)
4. Extra Approach (Bit Manipulation)

For EACH method include:

--- Method 1: Brute Force ---
- Intuition: For each index i, we can iterate from 0 to i in both arrays and manually count the common elements by comparing every possible pair.
- Approach: Use nested loops. For every element in A[0..i], iterate through B[0..i] to check if it exists.
- Dry Run: A=[1,3], B=[3,1]. i=0: A={1}, B={3}, common=0. i=1: A={1,3}, B={3,1}, common=2.
- Time Complexity: O(N^3) (or O(N^2) if optimized slightly)
- Space Complexity: O(1) auxiliary space.
- Why better than previous method: N/A (Baseline).
- When to use: Never recommended unless N is extremely small.

--- Method 2: Better Approach (Hash Set) ---
- Intuition: Maintain sets for elements seen so far in A and B to quickly find intersections.
- Approach: At each index i, insert A[i] into setA and B[i] into setB. Iterate through setA and count how many elements also exist in setB.
- Dry Run: i=1: setA={1,3}, setB={3,1}. Intersection count yields 2.
- Time Complexity: O(N^2)
- Space Complexity: O(N)
- Why better than previous method: Reduces time complexity by utilizing O(1) hash map lookups.
- When to use: When elements are not contiguous or when ranges are unbounded.

--- Method 3: Optimal Approach (Frequency Array) ---
- Intuition: Since the arrays are permutations of 1 to N, an element can appear at most twice overall. We can track frequencies in a single array.
- Approach: Use a frequency array of size N+1. For each index, increment the frequency of A[i] and B[i]. If any element's frequency hits 2, increment the common counter.
- Dry Run: A=[1,3,2,4], B=[3,1,2,4].
  i=0: freq[1]++, freq[3]++. Both frequencies are 1. count=0.
  i=1: freq[3]++ (now 2) -> count=1. freq[1]++ (now 2) -> count=2.
- Time Complexity: O(N)
- Space Complexity: O(N)
- Why better than previous method: Single pass with O(1) check per element.
- When to use: The standard optimal approach for permutation or bounded-range frequency problems.

--- Method 4: Extra Approach (Bit Manipulation) ---
- Intuition: Since N <= 50, we can use a 64-bit integer (`unsigned long long`) to represent the presence of elements as set bits.
- Approach: Maintain two bitmasks. For each A[i] and B[i], set the corresponding bit. The common elements are represented by `maskA & maskB`. The count is simply the number of set bits (popcount).
- Dry Run: A[0]=1, B[0]=3. maskA = ...00010, maskB = ...01000. AND = 0.
- Time Complexity: O(N)
- Space Complexity: O(1) auxiliary space.
- Why better than previous method: Constant space overhead. Extremely fast due to hardware-level bit counting.
- When to use: When N <= 64 and maximum performance/minimal memory is required.

Comparison Table:
Method           | TC     | SC   | Best Use Case
---------------- | ------ | ---- | ---------------------------
Brute Force      | O(N^3) | O(1) | Never
Hash Set         | O(N^2) | O(N) | Unbounded elements
Frequency Array  | O(N)   | O(N) | General optimal solution
Bit Manipulation | O(N)   | O(1) | When N <= 64 (Best here)

Final Recommended Solution: 
Bit Manipulation (Method 4) due to LeetCode constraints (N <= 50), with Frequency Array (Method 3) as the standard algorithmic alternative.
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // Method 4: Bit Manipulation (Highly Optimized for N <= 50)
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
        int n = A.size();
        vector<int> ans(n);
        
        unsigned long long maskA = 0;
        unsigned long long maskB = 0;
        
        for (int i = 0; i < n; ++i) {
            maskA |= (1ULL << A[i]);
            maskB |= (1ULL << B[i]);
            
            // __builtin_popcountll counts the number of set bits (1s) in a 64-bit integer
            ans[i] = __builtin_popcountll(maskA & maskB);
        }
        
        return ans;
    }

    // Method 3: Frequency Array Approach (Standard Optimal)
    vector<int> findThePrefixCommonArray_Freq(vector<int>& A, vector<int>& B) {
        int n = A.size();
        vector<int> ans(n);
        vector<int> freq(n + 1, 0);
        int common = 0;
        
        for (int i = 0; i < n; ++i) {
            if (++freq[A[i]] == 2) common++;
            if (++freq[B[i]] == 2) common++;
            ans[i] = common;
        }
        
        return ans;
    }
};

// Driver code for standalone execution and testing
int main() {
    Solution sol;
    
    // Example 1
    vector<int> A = {1, 3, 2, 4};
    vector<int> B = {3, 1, 2, 4};
    
    vector<int> result = sol.findThePrefixCommonArray(A, B);
    
    cout << "Prefix Common Array: ";
    for (int val : result) {
        cout << val << " ";
    }
    cout << "\n";
    
    return 0;
}
