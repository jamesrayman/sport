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
        
        for (auto [j, w] : adj[i]) {
            if (d[i] + w < d[j]) {
                q.erase({ d[j], j });
                d[j] = d[i] + w;
                q.insert({ d[j], j });
            }
        }
    }

    return d;
}

int main () {
    ll n, m;
    vector<vector<pair<ll, ll>>> adj;

    cin >> n >> m;
    adj.resize(n);

    while (m-->0) {
        ll a, b, w;
        cin >> a >> b >> w;
        a--;
        b--;

        adj[a].push_back({ b, w });
    }

    auto d = dijk(adj, 0);

    for (auto x : d) cout << x << " ";

    return 0;
}
