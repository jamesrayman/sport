#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

ll n, m;
vector<vector<pll>> adj;

int main () {
    cin >> n >> m;
    adj.resize(2*n);

    adj[n-1].push_back({ 2*n-1, 0 });
    while (m-->0) {
        ll a, b, w;
        cin >> a >> b >> w;
        a--;
        b--;

        adj[a].push_back({ b, w });
        adj[a+n].push_back({ b+n, w });
        adj[a].push_back({ b+n, w/2 });
    }

    set<pll> q;
    vector<ll> d (adj.size(), 1e18);

    q.insert({ 0, 0 });
    d[0] = 0;

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

    cout << d.back();

    return 0;
}
