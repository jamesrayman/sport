#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

vector<ll> dijk (const vector<vector<pll>>& adj, ll source) {
    set<pll> q;
    vector<ll> d (adj.size(), 1e18);

    q.insert({ 0, source });
    d[source] = 0;

    while (!q.empty()) {
        ll i = q.begin()->second;
        q.erase(q.begin());
        
        for (auto& p : adj[i]) {
            auto j = p.first, w = p.second;

            if (d[i] + w < d[j]) {
                q.erase({ d[j], j });
                d[j] = d[i] + w;
                q.insert({ d[j], j });
            }
        }
    }

    return d;
}
