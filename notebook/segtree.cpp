#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template<typename T>
struct SegTree {
    ll n;
    vector<T> t;
    T noval = 2e9;

    T f (T a, T b) {
        return min(a, b);
    }

    void combine (ll p) {
        t[p] = f(t[2*p], t[2*p+1]);
    }

    void build (const vector<T>& v, ll p, ll lo, ll hi) {
        if (lo == hi) {
            t[p] = v[lo];
            return;
        }
        
        ll mid = (lo + hi)/2;
        build(v, 2*p, lo, mid);
        build(v, 2*p+1, mid+1, hi);

        combine(p);
    }
    void build (const vector<T>& v) {
        n = v.size();

        t.assign(4*n, noval);
        build(v, 1, 0, n-1);
    }
    void build (ll n, T val = T()) {
        build (vector<T>(n, val));
    }

    T query (ll p, ll lo, ll hi, ll i, ll j) {
        if (hi < i || j < lo) return noval;
        if (i <= lo && hi <= j) return t[p];

        ll mid = (lo + hi)/2;
        return f(query(2*p, lo, mid, i, j),
                 query(2*p+1, mid+1, hi, i, j));
    }
    T query (ll i, ll j) {
        return query(1, 0, n-1, i, j);
    }

    void update (ll p, ll lo, ll hi, ll i, T x) {
        if (hi < i || i < lo) return;
        if (lo == hi) {
            t[p] = x;
            return;
        }

        ll mid = (lo + hi)/2;
        update(2*p, lo, mid, i, x);
        update(2*p+1, mid+1, hi, i, x);
        combine(p);
    }

    void update (ll i, T x) {
        update(1, 0, n-1, i, x);
    }
};