/*
Date: 24-06-2026
Problem Name: Number of ZigZag Arrays II
Platform: LeetCode
Difficulty: Hard
Tags: Math, Dynamic Programming, Matrix Exponentiation

Problem Summary:
Given n, l, and r, find the number of "ZigZag" arrays of length n where each 
element is in range [l, r], no two adjacent elements are equal, and no three 
consecutive elements form a strictly increasing or strictly decreasing sequence.
Result should be modulo 10^9 + 7.

Methods to Solve:
1. Matrix Exponentiation (Optimal)
   - Intuition: Since n can be up to 10^9, a linear DP is impossible. The state 
     transitions are consistent, making matrix exponentiation ideal.
   - Approach: 
     - Let m = r - l + 1. 
     - A state can be defined by (last_value, direction).
     - Direction 0: Previous move was "down" (arr[i-2] > arr[i-1]), so we must "up" (arr[i] > arr[i-1]).
     - Direction 1: Previous move was "up" (arr[i-2] < arr[i-1]), so we must "down" (arr[i] < arr[i-1]).
     - Transitions:
       - If current state is (val, UP), next state must be (next_val, DOWN) where next_val < val.
       - If current state is (val, DOWN), next state must be (next_val, UP) where next_val > val.
     - Construct a 2m x 2m transition matrix and compute T^(n-1).

Comparison Table:
Method             | TC            | SC      | Best Use Case
-------------------|---------------|---------|--------------
Matrix Exponentiation| O(m^3 log n)  | O(m^2)  | Large n, small range [l, r]

*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
    long long MOD = 1e9 + 7;

    typedef vector<vector<long long>> matrix;

    matrix multiply(const matrix& A, const matrix& B) {
        int sz = A.size();
        matrix C(sz, vector<long long>(sz, 0));
        for (int i = 0; i < sz; i++)
            for (int k = 0; k < sz; k++)
                for (int j = 0; j < sz; j++)
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
        return C;
    }

    matrix power(matrix A, long long p) {
        int sz = A.size();
        matrix res(sz, vector<long long>(sz, 0));
        for (int i = 0; i < sz; i++) res[i][i] = 1;
        while (p > 0) {
            if (p & 1) res = multiply(res, A);
            A = multiply(A, A);
            p >>= 1;
        }
        return res;
    }

public:
    int zigZagArrays(int n, int l, int r) {
        if (n == 1) return (r - l + 1);
        
        int m = r - l + 1;
        // States 0 to m-1: (val, UP), m to 2m-1: (val, DOWN)
        matrix T(2 * m, vector<long long>(2 * m, 0));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                // From (l+i, UP) -> (l+j, DOWN) : need l+j < l+i => j < i
                if (j < i) T[i][m + j] = 1;
                // From (l+i, DOWN) -> (l+j, UP) : need l+j > l+i => j > i
                if (j > i) T[m + i][j] = 1;
            }
        }

        matrix Tn = power(T, n - 1);

        long long ans = 0;
        // Initial state: any starting value is both a potential start of UP or DOWN sequence
        for (int i = 0; i < 2 * m; i++) {
            for (int j = 0; j < 2 * m; j++) {
                ans = (ans + Tn[i][j]) % MOD;
            }
        }

        return (int)ans;
    }
};
