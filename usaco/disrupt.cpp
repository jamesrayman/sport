#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void initio (string file = "") {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    if (file != "") {
        freopen((file + ".in").c_str(), "r", stdin);
        freopen((file + ".out").c_str(), "w", stdout);
    }
}

ll n, m;
vector<vector<pair<ll, ll>>> adj;
vector<ll> ans;
vector<set<pair<ll, ll>>> s;

void pour (set<pair<ll, ll>>& x, set<pair<ll, ll>>& y) { // pour x to y
    if (x.size() > y.size()) swap(x, y);

    for (auto& p : x) {
        if (y.count(p)) {
            y.erase(p);
        }
        else {
            y.insert(p);
        }
    }
}

ll go (ll i, ll p) {
    for (auto& edge : adj[i]) {
        if (edge.first == p) continue;

        ans[edge.second] = go(edge.first, i);

        pour(s[edge.first], s[i]);
    }

    if (s[i].empty()) return -1;
    return s[i].begin()->first;
}

int main () {
    initio("disrupt");

    cin >> n >> m;
    ans.resize(n-1);
    adj.resize(n);
    s.resize(n);

    for (int i = 0; i < n-1; i++) {
        ll a, b;
        cin >> a >> b;
        a--;
        b--;

        adj[a].push_back({ b, i });
        adj[b].push_back({ a, i });
    }

    while (m-->0) {
        ll a, b, w;
        cin >> a >> b >> w;
        a--;
        b--;

        s[a].insert({ w, m });
        s[b].insert({ w, m });
    }

    go(0, -1);

    for (auto x : ans) cout << x << "\n";
}
