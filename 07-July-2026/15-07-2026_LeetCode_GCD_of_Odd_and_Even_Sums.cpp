/*
=========================================================
Date        : 15-07-2026
Problem Name: 3658. GCD of Odd and Even Sums
Platform    : LeetCode
Difficulty  : Easy
Tags        : Math, Number Theory

Problem Summary:
Given an integer n, compute the GCD of the sum of the 
smallest n positive odd numbers and the sum of the 
smallest n positive even numbers.

Key Observation:
The sum of the first n odd numbers is n^2, and the sum 
of the first n even numbers is n * (n + 1). Their GCD 
mathematically reduces to just n.
=========================================================
*/

/*
=========================================================
APPROACH 1: Brute Force Simulation
=========================================================
- Intuition  : We can directly simulate the problem by generating the sums.
- Approach   : Loop from 1 to n to accumulate the odd and even sums, then use a standard GCD function.
- Why it Works: It strictly follows the problem statement's definitions.
- Time Complexity (TC): O(n) to compute the sums, plus O(log(min(sumOdd, sumEven))) for the GCD.
- Space Complexity (SC): O(1) as we only use a few variables for tracking sums.

=========================================================
APPROACH 2: Most Optimal (Mathematical Deduction)
=========================================================
- Intuition  : We can use arithmetic progression sum formulas to avoid looping.
- Approach   : 
  * sumOdd = n * n
  * sumEven = n * (n + 1)
  * GCD(sumOdd, sumEven) = GCD(n * n, n * (n + 1))
- Why it Works: Factoring out 'n' gives us n * GCD(n, n + 1). Since any two consecutive integers (n and n+1) are strictly coprime, their GCD is 1. Thus, the answer is always simply n.
- Time Complexity (TC): O(1) constant time, no loops or external function calls required.
- Space Complexity (SC): O(1) constant space, no extra memory used.

=========================================================
FINAL APPROACH CHOSEN
=========================================================
We choose Approach 2 (Mathematical Deduction). 
It evaluates in O(1) time and avoids all loop iterations, 
as well as potential integer overflow issues that could 
arise from calculating large sums manually. 
=========================================================
*/

class Solution {
public:
    int gcdOfOddEvenSums(int n) {
        // The mathematical GCD of n^2 and n(n+1) is simply n.
        return n;
    }
};
