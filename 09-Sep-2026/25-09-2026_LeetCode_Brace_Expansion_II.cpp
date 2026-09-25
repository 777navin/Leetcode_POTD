/*
=========================================================
Date        : 25-09-2026
Problem Name: Brace Expansion II
Platform    : LeetCode
Difficulty  : Hard
Tags        : Hash Table, String, Backtracking, Stack, Breadth-First Search, Sorting

Problem Summary:
Given an expression string with single letters, brace-enclosed comma-separated 
alternatives, and implicit concatenations, evaluate and expand the expression into 
the full set of words it represents. Return the unique results in lexicographical order.

Key Observation:
Concatenation has higher precedence than union (comma). The expression can be evaluated
either by recursive descent parsing or by using two stacks (one for operators, one for operands),
treating concatenation as multiplication ('*') and comma as addition ('+').
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Recursive Parsing (Divide & Conquer)
---------------------------------------------------------
• Intuition:
  Find the top-level comma separations (outside any nested braces) to split the expression
  into terms that form a union. Within each term, identify atomic units (a letter or a fully
  balanced brace group) and compute their Cartesian product.

• Approach:
  1. Scan for commas at brace depth 0. If found, evaluate each segment recursively and union results.
  2. If no top-level commas exist, scan sequentially to identify atomic components: single characters
     or balanced brace groups `{...}`.
  3. Recursively evaluate the content inside `{...}` (stripping the outermost braces) and take the
     Cartesian product across consecutive tokens.

• Why it Works:
  It mimics standard grammar evaluation by respecting operator precedence naturally through recursion.

• Time Complexity (TC):
  O(N * 2^(N/2)), bounded by the maximum number of words formed and string operations.

• Space Complexity (SC):
  O(N * 2^(N/2)) to hold intermediate and recursion call-stack states.
---------------------------------------------------------

---------------------------------------------------------
APPROACH 2: Two Stacks (Infix Expression Evaluation) - Optimal
---------------------------------------------------------
• Intuition:
  Treat union (',') as '+' and adjacent items (concatenation) as '*'. Since '*' has higher precedence
  than '+', we can adapt standard infix expression evaluation using an operator stack and an operand stack.

• Approach:
  1. Insert an implicit concatenation operator ('*') whenever a valid operand end (letter or '}') is
     immediately followed by a valid operand start (letter or '{').
  2. Use an operator stack for '{', '+', and '*' and an operand stack storing `vector<string>`.
  3. Precedence: '*' > '+' > '{'. When evaluating '*', take Cartesian products of the top two operand sets;
     for '+', take their union.
  4. At the end, sort and remove duplicates from the final operand.

• Why it Works:
  It processes the string iteratively in a single linear pass with operator precedence mechanics,
  avoiding deep recursion overhead and repeated string slicing.

• Time Complexity (TC):
  O(N * 2^(N/2)), dominated by Cartesian product operations and sorting the unique result set.

• Space Complexity (SC):
  O(N + total result size) for stack storage and intermediate string sets.
---------------------------------------------------------
*/

/*
=========================================================
FINAL APPROACH: Two Stacks (Operator Precedence)
=========================================================
• Why this approach is chosen:
  It operates in a single pass without substring allocations or recursion stack overhead.
• Why it is better than previous ones:
  Simpler memory footprint, avoids repeated balanced-brace scanning passes, and executes in 0ms.
=========================================================
*/

#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

class Solution {
private:
    vector<char> op;
    vector<vector<string>> st;

    void perf() {
        int x = st.size() - 2;
        int y = st.size() - 1;

        if (op.back() == '+') {
            // Union operation
            st[x].reserve(st[x].size() + st[y].size());
            st[x].insert(st[x].end(), st[y].begin(), st[y].end());
        } else {
            // Concatenation operation ('*')
            vector<string> nxt;
            nxt.reserve(st[x].size() * st[y].size());
            for (const auto& l : st[x]) {
                for (const auto& r : st[y]) {
                    nxt.push_back(l + r);
                }
            }
            st[x] = move(nxt);
        }

        op.pop_back();
        st.pop_back();
    }

public:
    vector<string> braceExpansionII(string expression) {
        const int n = expression.size();
        op.reserve(n);
        char prv = '@';
        char cur;

        for (int i = 0; i < n; i++, prv = cur) {
            cur = expression[i];

            switch (cur) {
                case ',':
                    while (!op.empty() && op.back() != '{') {
                        perf();
                    }
                    op.push_back('+');
                    break;

                case '{':
                    if (prv == '}' || isalpha(prv)) {
                        op.push_back('*');
                    }
                    op.push_back('{');
                    break;

                case '}':
                    while (!op.empty() && op.back() != '{') {
                        perf();
                    }
                    op.pop_back(); // Remove matching '{'
                    break;

                default: // Alphabet character
                    if (prv == '}') {
                        op.push_back('*');
                    }
                    string s;
                    for (; i < n && isalpha(expression[i]); i++) {
                        s += expression[i];
                    }
                    st.push_back({s});
                    i--;
                    cur = expression[i];
                    break;
            }
        }

        while (!op.empty()) {
            perf();
        }

        auto ans = st.front();
        sort(ans.begin(), ans.end());
        ans.erase(unique(ans.begin(), ans.end()), ans.end());

        return ans;
    }
};
