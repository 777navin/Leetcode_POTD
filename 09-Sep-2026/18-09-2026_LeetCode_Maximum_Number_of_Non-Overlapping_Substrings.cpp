/*
=========================================================
Date        : 18-09-2026
Problem Name: B. Rain
Platform    : Codeforces
Difficulty  : 2100
Tags        : Sweep-line, Math, Data Structures

Problem Summary:
• There are n rain days, each creating a tent-shaped rainfall accumulation.
• We need to determine if removing exactly one specific day's rain prevents a flood (rainfall > m everywhere).

Key Observation:
• Total rainfall is a piecewise linear function where all slope changes occur at x_i - p_i, x_i, and x_i + p_i.
• We only need to check the points where the slope changes to find maximum violations.
=========================================================
*/

/*
1. Brute Force
• Intuition: For every day, remove its rain and recalculate the total rainfall across all points to check if it exceeds m.
• Approach: Iterate over each day, temporarily zero out its intensity, and build the rainfall array to check the peak.
• Why it Works: Simply simulates the problem statement directly.
• Time Complexity (TC): O(N^2)
• Space Complexity (SC): O(N)

2. Optimized Sweep-line (Most Optimal)
• Intuition: Instead of recalculating, compute the total rainfall function once and find all points where rainfall exceeds m.
• Approach: Use a difference array (map) for slopes to compute the total rain S(x) at all critical points.
• Why it Works: If S(x) > m, day i can only fix it if its contribution at x brings it down below m. This reduces to satisfying two global maximum conditions.
• Time Complexity (TC): O(N log N) for sorting/map insertions.
• Space Complexity (SC): O(N) to store events.
*/

/*
Final Approach: Optimized Sweep-line
• We use the sweep-line technique to compute the prefix sums of slope changes, accurately finding S(x).
• If there are violations (S(x) > m), a day is valid if it mathematically covers the worst-case left and right bounds of the overflow.
*/

#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    long long m;
    cin >> n >> m;

    vector<pair<long long, long long>> rains(n);
    map<long long, long long> delta_slope;

    for (int i = 0; i < n; ++i) {
        long long x, p;
        cin >> x >> p;
        rains[i] = {x, p};
        
        // Slope changes: +1 at start, -2 at peak, +1 at end
        delta_slope[x - p] += 1;
        delta_slope[x] -= 2;
        delta_slope[x + p] += 1;
    }

    long long curr_S = 0;
    long long curr_slope = 0;
    long long prev_x = delta_slope.begin()->first;
    
    long long M1 = -3e18; // To track max(S(x) - x) for bad points
    long long M2 = -3e18; // To track max(S(x) + x) for bad points
    bool has_bad = false;

    // Evaluate total rainfall at all critical points
    for (auto const& [x, ds] : delta_slope) {
        curr_S += curr_slope * (x - prev_x);
        
        if (curr_S > m) {
            has_bad = true;
            M1 = max(M1, curr_S - x);
            M2 = max(M2, curr_S + x);
        }
        
        curr_slope += ds;
        prev_x = x;
    }

    string ans = "";
    for (int i = 0; i < n; ++i) {
        if (!has_bad) {
            ans += "1"; // No floods at all, removing anything is fine
        } else {
            long long x = rains[i].first;
            long long p = rains[i].second;
            
            // Check if removing this rain reduces the peak below m for all bad points
            if (p - x >= M1 - m && p + x >= M2 - m) {
                ans += "1";
            } else {
                ans += "0";
            }
        }
    }
    
    cout << ans << "\n";
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}
