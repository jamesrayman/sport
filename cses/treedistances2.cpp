#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

ll n;
vector<vector<ll>> adj;
vector<ll> p, h, sts, d;

void treeify (int i, int par) {
    p[i] = par;
    if (par != -1) {
        h[i] = 1 + h[par];
        d[0] += h[i];
    }
    for (auto j : adj[i]) {
        if (j == par) continue;

        treeify(j, i);
        sts[i] += sts[j];
    }
}

void treeify2 (int i) {
    if (i != 0) {
        d[i] = d[p[i]] - 2*sts[i] + n;
    }

    for (auto j : adj[i]) {
        if (j == p[i]) continue;

        treeify2(j);
    }
}
int main () {
    cin >> n;

    adj.resize(n);
    p.resize(n, -1);
    h.resize(n, 0);
    d.resize(n, 0);
    sts.resize(n, 1);

    for (int i = 0; i < n-1; i++) {
        ll a, b;
        cin >> a >> b;
        a--;
        b--;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    treeify(0, -1);
    treeify2(0);
    for (auto x : d) cout << x << " ";
}
