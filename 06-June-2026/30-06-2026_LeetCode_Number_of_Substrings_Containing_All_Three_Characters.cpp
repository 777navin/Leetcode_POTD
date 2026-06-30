/*
=========================================================
Date        : 30-06-2026
Problem Name: Number of Substrings Containing All Three Characters
Platform    : LeetCode
Difficulty  : Medium
Tags        : Hash Table, String, Sliding Window

Problem Summary
Given a string `s` consisting only of characters 'a', 'b', and 'c'. Return the number of substrings containing at least one occurrence of all these characters.

Constraints
- 3 <= s.length <= 5 * 10^4
- s only consists of 'a', 'b', or 'c' characters.

Key Observation
If a substring ending at index `right` and starting at index `left` contains at least one 'a', 'b', and 'c', then any substring starting at an index before `left` and ending at `right` will also be valid. We do not need to count them one by one; we can use math to count them in batches.
=========================================================

=========================================================
APPROACH 1: Brute Force
=========================================================
• Intuition: Generate every possible substring and check if it contains all three characters.
• Idea: Use two nested loops to define the start and end of every substring. 
• Approach: For every starting index `i`, iterate an ending index `j` from `i` to `n-1`. Use an array or hash map to track characters seen in the current substring. Once all 3 are found, increment the count.
• Dry Run: 
  s = "abcabc"
  i = 0 ('a'), j moves to 2 ('c'). Found "abc". Valid.
  j moves to 3 ('a'). "abca". Valid.
  Continues checking all combinations.
• Why it works: It exhaustively searches the entire solution space.
• Time Complexity: O(N^2) where N is the length of the string.
• Space Complexity: O(1) as we only use an array of size 3 for character counts.
• Advantages: Extremely simple to understand and implement.
• Disadvantages: Highly inefficient. Will result in Time Limit Exceeded (TLE) for N = 5 * 10^4.
• When to use: When N <= 1000.
• Why next approach is better: We are repeatedly re-evaluating the same overlapping substrings. A sliding window can avoid this redundant work.

=========================================================
APPROACH 2: Sliding Window
=========================================================
• Intuition: Maintain a dynamic window `[left, right]` that expands until it contains all three characters, then shrinks from the left to find the smallest valid window.
• Idea: Once a valid window `[left, right]` is found, every substring starting at `left` and ending anywhere from `right` to `n-1` is also valid.
• Approach: 
  1. Use two pointers `left` and `right`.
  2. Expand `right` and add characters to a frequency array.
  3. While the window contains at least one 'a', 'b', and 'c':
     - Add `n - right` to the total count (because all substrings extending to the right end are valid).
     - Remove the `left` character from the frequency array and increment `left` to shrink the window.
• Dry Run:
  s = "abcabc", n = 6
  right = 0 to 2: freq becomes {a:1, b:1, c:1}. Valid window!
  Add (6 - 2) = 4 to count.
  Shrink: left=1, freq becomes {a:0, b:1, c:1}. Invalid window. Expand right.
• Why it works: It counts multiple substrings at once by leveraging the fact that extending a valid substring always yields another valid substring.
• Time Complexity: O(N) because each character is processed by `left` and `right` pointers at most twice.
• Space Complexity: O(1) auxiliary space (array of size 3).
• Advantages: Efficient and conceptually standard for substring problems.
• Disadvantages: Slightly more code and requires careful pointer management.
• When to use: General string problems involving substring conditions.
• Why next approach is better: The next approach eliminates the `left` pointer entirely by just tracking the most recent indices of each character, resulting in slightly cleaner and faster code.

=========================================================
APPROACH 3: Most Optimal (Tracking Last Occurrences)
=========================================================
• Intuition: For any ending index `i`, what is the shortest valid substring ending at `i`? It must start at the minimum of the last seen indices of 'a', 'b', and 'c'.
• Idea: Track the most recent index where 'a', 'b', and 'c' were seen.
• Approach: 
  1. Initialize an array `lastSeen` with -1 for all three characters.
  2. Iterate through the string with index `i`.
  3. Update `lastSeen[s[i] - 'a'] = i`.
  4. If all three characters have been seen (none are -1), the number of valid substrings ending at `i` is `1 + min(lastSeen['a'], lastSeen['b'], lastSeen['c'])`. Add this to the total count.
• Dry Run:
  s = "abcabc"
  i = 0 ('a'): lastSeen = {0, -1, -1}. count = 0
  i = 1 ('b'): lastSeen = {0, 1, -1}. count = 0
  i = 2 ('c'): lastSeen = {0, 1, 2}. min is 0. count += (1+0) = 1.
  i = 3 ('a'): lastSeen = {3, 1, 2}. min is 1. count += (1+1) = 3. (Total = 4)
• Why it works: The minimum of the last seen indices represents the tightest left boundary. Any starting point from 0 up to that minimum index combined with the current ending index `i` forms a valid substring.
• Time Complexity: O(N) single pass.
• Space Complexity: O(1) constant space for 3 variables.
• Advantages: Cleanest code, single loop, minimal operations, no nested `while` loops.
• Disadvantages: None.
• When to use: Highly optimized counting logic for restricted character sets.

=========================================================
COMPARISON TABLE
-------------------------------------------------------
Method              Idea                      Time   Space  Difficulty  Recommended
-------------------------------------------------------
Brute Force         Check all combinations    O(N^2) O(1)   Easy        No
Sliding Window      Expand/Shrink Window      O(N)   O(1)   Medium      Yes
Last Occurrences    Track min of last seen    O(N)   O(1)   Medium      Highly
-------------------------------------------------------

=========================================================
FINAL RECOMMENDED APPROACH
=========================================================
The Most Optimal Approach (Tracking Last Occurrences) is the best solution. It requires only a single pass `O(N)` through the string without the inner `while` loop used in traditional sliding windows. It keeps the space complexity strictly to `O(1)` using a size-3 array. It is extremely concise and less prone to off-by-one errors compared to manipulating two separate pointers.
*/

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int numberOfSubstrings(string s) {
        // Array to store the last seen index of 'a', 'b', and 'c'
        int lastSeen[3] = {-1, -1, -1};
        int count = 0;
        
        for (int i = 0; i < s.length(); i++) {
            // Update the last seen index for the current character
            lastSeen[s[i] - 'a'] = i;
            
            // If all three characters have been encountered at least once
            if (lastSeen[0] != -1 && lastSeen[1] != -1 && lastSeen[2] != -1) {
                // The number of valid substrings ending at index i is determined by 
                // the smallest index among the last seen positions of 'a', 'b', and 'c'.
                count += (1 + min({lastSeen[0], lastSeen[1], lastSeen[2]}));
            }
        }
        
        return count;
    }
};
