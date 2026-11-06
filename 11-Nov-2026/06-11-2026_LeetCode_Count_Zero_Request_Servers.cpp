/*
=========================================================
Date        : 06-11-2026
Problem Name: Count Zero Request Servers
Platform    : LeetCode
Difficulty  : Medium
Tags        : Sliding Window, Sorting, Hash Map, Offline Queries

Problem Summary:
- Given server request logs and query times.
- For each query q, find servers that received
  zero requests in interval [q - x, q].

Key Observation:
- Process queries offline in sorted order.
- Maintain active servers using a sliding window.
=========================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
Approach 1: Brute Force
=========================================================

• Intuition:
  - Check all logs for every query.

• Approach:
  - Collect servers appearing in [q-x, q].

• Why it Works:
  - Direct implementation of definition.

• TC:
  - O(Q * M)

• SC:
  - O(N)
*/


/*
=========================================================
Approach 2: Offline Queries + Sliding Window
=========================================================

• Intuition:
  - Sorted queries allow reuse of previous work.

• Approach:
  - Sort logs by time.
  - Sort queries while storing original indices.
  - Maintain logs currently inside [q-x, q].
  - Track active servers using frequency map.

• Why it Works:
  - Window always contains exactly valid logs.
  - Active servers = servers with at least one
    request in current interval.

• TC:
  - O((M + Q) log(M + Q))

• SC:
  - O(N)
*/


/*
=========================================================
Final Approach Chosen
=========================================================

• Sliding window processes every log once.
• Much faster than scanning all logs repeatedly.
• Suitable for large constraints.
=========================================================
*/

class Solution {
public:
    vector<int> countServers(int n,
                             vector<vector<int>>& logs,
                             int x,
                             vector<int>& queries) {

        sort(logs.begin(), logs.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[1] < b[1];
             });

        vector<pair<int, int>> sortedQueries;

        for (int i = 0; i < (int)queries.size(); i++) {
            sortedQueries.push_back({queries[i], i});
        }

        sort(sortedQueries.begin(), sortedQueries.end());

        vector<int> answer(queries.size());

        unordered_map<int, int> freq;

        int activeServers = 0;
        int left = 0;
        int right = 0;

        for (auto &[queryTime, originalIndex] : sortedQueries) {

            int windowStart = queryTime - x;

            while (right < (int)logs.size() &&
                   logs[right][1] <= queryTime) {

                int serverId = logs[right][0];

                if (++freq[serverId] == 1)
                    activeServers++;

                right++;
            }

            while (left < right &&
                   logs[left][1] < windowStart) {

                int serverId = logs[left][0];

                if (--freq[serverId] == 0)
                    activeServers--;

                left++;
            }

            answer[originalIndex] = n - activeServers;
        }

        return answer;
    }
};
