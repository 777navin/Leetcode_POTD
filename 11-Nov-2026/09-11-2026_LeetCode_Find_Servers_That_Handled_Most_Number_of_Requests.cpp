/*
=========================================================
Date        : 09-11-2026
Problem Name: Find Servers That Handled Most Number of Requests
Platform    : LeetCode
Difficulty  : Hard
Tags        : Heap, Ordered Set, Simulation, Greedy

Problem Summary:
- There are k servers and incoming requests.
- Each request should be assigned based on the given circular rule.
- Busy servers cannot take another request.
- Return all servers that handled the maximum number of requests.

Key Observation:
- We need to quickly find the next available server.
- Use an ordered set for free servers and a min-heap for busy servers.
=========================================================
*/

/*
---------------------------------------------------------
Approach 1: Brute Force
---------------------------------------------------------
Intuition:
- For every request, check servers one by one.

Approach:
- Start from (i % k) and search circularly.
- Assign the first available server.

Why it Works:
- Direct simulation of the problem statement.

TC:
- O(n * k)

SC:
- O(k)

Not feasible for k,n up to 1e5.
*/

/*
---------------------------------------------------------
Approach 2: Optimized using Ordered Set + Min Heap
---------------------------------------------------------
Intuition:
- Need fast server release and fast next-server lookup.

Approach:
- Min Heap stores:
      {finishTime, serverId}
- Ordered Set stores currently available servers.
- Before processing a request:
      release all completed servers.
- Use lower_bound(i % k) to find the preferred server.
- If none exists, wrap to the first available server.

Why it Works:
- Ordered set efficiently finds the next valid server.
- Heap efficiently tracks when servers become free.

TC:
- O(n log k)

SC:
- O(k)

Feasible for constraints up to 1e5.
*/

/*
---------------------------------------------------------
Final Approach Chosen
---------------------------------------------------------
- Ordered Set + Min Heap gives efficient assignment.
- Server release operations are handled lazily.
- Circular server search is supported via lower_bound.
- Achieves O(n log k), which easily fits constraints.
---------------------------------------------------------
*/

class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {

        set<int> availableServers;

        for (int server = 0; server < k; server++) {
            availableServers.insert(server);
        }

        priority_queue<
            pair<long long, int>,
            vector<pair<long long, int>>,
            greater<pair<long long, int>>
        > busyServers;

        vector<int> handledCount(k, 0);

        int n = arrival.size();

        for (int request = 0; request < n; request++) {

            long long currentTime = arrival[request];

            while (!busyServers.empty() &&
                   busyServers.top().first <= currentTime) {

                availableServers.insert(busyServers.top().second);
                busyServers.pop();
            }

            if (availableServers.empty()) {
                continue;
            }

            int preferredServer = request % k;

            auto it = availableServers.lower_bound(preferredServer);

            if (it == availableServers.end()) {
                it = availableServers.begin();
            }

            int assignedServer = *it;

            availableServers.erase(it);

            handledCount[assignedServer]++;

            busyServers.push({
                currentTime + load[request],
                assignedServer
            });
        }

        int maxHandled = *max_element(
            handledCount.begin(),
            handledCount.end()
        );

        vector<int> answer;

        for (int server = 0; server < k; server++) {
            if (handledCount[server] == maxHandled) {
                answer.push_back(server);
            }
        }

        return answer;
    }
};
