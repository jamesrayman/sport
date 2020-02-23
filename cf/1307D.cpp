#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll n, m, k;
vector<char> red;
vector<vector<ll>> adj;

struct Bag {
    vector<ll> x; // inc
    vector<ll> y; // dec

    void add (ll i, ll j) {
        while (y.size() > 0 && j > y.back()) {            
            y.pop_back();
            x.pop_back();
        }
        x.push_back(i);
        y.push_back(j);

    }
    ll f (ll i, ll j, ll m) {
        return min(i + x[m], j + y[m]);
    }
    ll query (ll i, ll j) {
        if (x.size() == 0) return 0;

        ll lo = 0;
        ll hi = x.size()-1;

        while (lo+6 < hi) {
            ll ma = (2*lo + hi)/3;
            ll mb = (lo + 2*hi)/3;

            if (f(i, j, ma) > f(i, j, mb)) {
                hi = mb;
            }
            else {
                lo = ma;
            }
        }
        ll r = 0;
        for (int m = lo; m <= hi; m++) {
            r = max(r, f(i, j, m));
        }
        return r;
    }
};

vector<ll> bfs (ll i) {
    queue<ll> q;
    q.push(i);
    q.push(0);

    vector<ll> d(n, 1e9);

    while (!q.empty()) {
        i = q.front();
        q.pop();
        ll dist = q.front();
        q.pop();

        if (dist >= d[i]) continue;

        d[i] = dist;

        for (auto& j : adj[i]) {
            q.push(j);
            q.push(dist+1);
        }
    }
    return d;
}

int main () {
    cin >> n >> m >> k;

    red.resize(n, false);
    adj.resize(n);

    while (k-->0) {
        ll a;
        cin >> a;
        a--;

        red[a] = true;
    }

    bool good = false;
    while (m-->0) {
        ll a, b;
        cin >> a >> b;
        a--;
        b--;

        if (red[a] && red[b]) good = true;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<ll> v, u;
    v = bfs(0);
    u = bfs(n-1);

    if (good) {
        cout << v[n-1] << "\n";
    }
    else {
        ll best = 0;
        Bag b;

        vector<pair<ll, ll>> w;
        for (int i = 0; i < n; i++) {
            if (red[i])
                w.push_back({ v[i], u[i] });
        }
        sort(w.begin(), w.end());

        for (auto& p : w) {
            best = max(best, 1+b.query(p.first, p.second));
            b.add(p.second, p.first);
        }
        cout << min(best, v[n-1]) << "\n";
    }
}
