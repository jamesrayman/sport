#include <bits/stdc++.h>
using namespace std;

using ll = long long;

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