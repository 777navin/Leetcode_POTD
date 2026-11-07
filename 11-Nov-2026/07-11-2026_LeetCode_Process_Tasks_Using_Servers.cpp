/*
=========================================================
Date        : 07-11-2026
Problem Name: Process Tasks Using Servers
Platform    : LeetCode
Difficulty  : Medium
Tags        : Heap, Priority Queue, Simulation, Greedy

Problem Summary:
- Each task arrives at second i.
- Assign tasks to free servers with minimum weight.
- If weights are equal, choose smaller index.
- If all servers are busy, wait for the earliest available server.

Key Observation:
- We must efficiently track both free and busy servers.
- Two min-heaps allow optimal server selection and release.
=========================================================
*/

class Solution {
public:

    /*
    =========================================================
    Approach 1: Brute Force Simulation

    • Intuition:
      - For every task, check all servers manually.

    • Approach:
      - Track availability time of each server.
      - Scan all servers whenever a task arrives.

    • Why it Works:
      - Directly simulates the given process.

    • TC:
      - O(m * n)

    • SC:
      - O(n)
    =========================================================
    */

    /*
    =========================================================
    Approach 2: Two Min-Heaps (Optimized)

    • Intuition:
      - Always need:
        1) Best available server.
        2) Earliest server becoming free.

    • Approach:
      - Free Heap:
          (weight, index)
      - Busy Heap:
          (finishTime, weight, index)
      - Release servers whose work is completed.
      - Assign task to best available server.
      - If none available, jump to earliest finish time.

    • Why it Works:
      - Heaps maintain required priorities efficiently.
      - Simulation exactly follows problem rules.

    • TC:
      - O((n + m) log n)

    • SC:
      - O(n)
    =========================================================
    */

    /*
    =========================================================
    Final Approach Chosen

    - Two priority queues provide the optimal simulation.
    - Free servers are selected by (weight, index).
    - Busy servers are released by earliest finish time.
    - Much faster than repeatedly scanning all servers.
    =========================================================
    */

    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {

        using ll = long long;

        // Available servers:
        // {weight, index}
        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > freeServers;

        // Busy servers:
        // {finishTime, weight, index}
        priority_queue<
            tuple<ll, int, int>,
            vector<tuple<ll, int, int>>,
            greater<tuple<ll, int, int>>
        > busyServers;

        int n = servers.size();
        int m = tasks.size();

        for (int i = 0; i < n; i++) {
            freeServers.push({servers[i], i});
        }

        vector<int> ans(m);

        ll currentTime = 0;

        for (int taskIndex = 0; taskIndex < m; taskIndex++) {

            currentTime = max(currentTime, (ll)taskIndex);

            // Release all completed servers.
            while (!busyServers.empty() &&
                   get<0>(busyServers.top()) <= currentTime) {

                auto [finishTime, weight, serverIndex] =
                    busyServers.top();

                busyServers.pop();

                freeServers.push({weight, serverIndex});
            }

            // If no server is free, jump to earliest finish time.
            if (freeServers.empty()) {

                currentTime = get<0>(busyServers.top());

                while (!busyServers.empty() &&
                       get<0>(busyServers.top()) <= currentTime) {

                    auto [finishTime, weight, serverIndex] =
                        busyServers.top();

                    busyServers.pop();

                    freeServers.push({weight, serverIndex});
                }
            }

            auto [weight, serverIndex] = freeServers.top();
            freeServers.pop();

            ans[taskIndex] = serverIndex;

            busyServers.push({
                currentTime + tasks[taskIndex],
                weight,
                serverIndex
            });
        }

        return ans;
    }
};
