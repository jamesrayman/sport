#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;
using ld = long double;

void initio (string file = "") {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    if (file != "") {
        freopen((file + ".in").c_str(), "r", stdin);
        freopen((file + ".out").c_str(), "w", stdout);
    }
}

struct Fenwick {
    ll n;
    vector<ll> t;

    Fenwick (ll n = 2e5) : n(n) {
        t.resize(n);
    }
 
    void update (ll i, ll delta) {
        while (i < n) {
            t[i] += delta;
            i += i&-i;
        }
    }
 
    ll query (ll i) {
        ll r = 0;
        while (i > 0) {
            r += t[i];
            i -= i&-i;
        }
        return r;
    }
};

ll n;

ll solve (vector<ll> v, vector<ll> u) {
    ll t = 0;
    Fenwick f (n+10);

    vector<ll> w (n);

    for (int i = 0; i < n; i++) {
        w[v[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        u[i] = w[u[i]];
    }

    for (int i = n-1; i > -1; i--) {
        t += f.query(u[i]+3);
        f.update(u[i]+3, 1);
    }

    ll best = t;

    for (int i = 0; i < n; i++) {
        t += n - 2*u[i] - 1;
        best = min(best, t);
    }
    
    return best;
}

int main () {
    initio("mincross");
    
    vector<ll> v, u;

    cin >> n;
    v.resize(n);
    u.resize(n);

    for (auto& x : v) cin >> x, x--;
    for (auto& x : u) cin >> x, x--;

    cout << min(solve(v, u), solve(u, v)) << "\n";

    return 0;
}
