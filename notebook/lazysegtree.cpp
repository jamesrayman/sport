#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template<typename T>
struct SegTree {
    ll n;
    vector<T> t, lazy;
    T noval = 0;

    T f (T a, T b) {
        return a + b;
    }

    T at (ll p, ll lo, ll hi) {
        return t[p] + (hi - lo + 1) * lazy[p];
    }
    void unlazy (ll p, ll lo, ll hi) {
        lazy[2*p] += lazy[p];
        lazy[2*p+1] += lazy[p];
        lazy[p] = 0;

        combine(p, lo, hi);
    }

    void combine (ll p, ll lo, ll hi) {
        ll mid = (lo + hi)/2;
        t[p] = f(at(2*p, lo, mid), at(2*p+1, mid+1, hi));
    }

    void build (const vector<T>& v, ll p, ll lo, ll hi) {
        if (lo == hi) {
            t[p] = v[lo];
            return;
        }
        
        ll mid = (lo + hi)/2;
        build(v, 2*p, lo, mid);
        build(v, 2*p+1, mid+1, hi);

        combine(p, lo, hi);
    }
    void build (const vector<T>& v) {
        n = v.size();

        t.assign(4*n, noval);
        lazy.assign(4*n, noval);
        build(v, 1, 0, n-1);
    }

    T query (ll p, ll lo, ll hi, ll i, ll j) {
        if (hi < i || j < lo) return noval;
        if (i <= lo && hi <= j) return at(p, lo, hi);

        unlazy(p, lo, hi);

        ll mid = (lo + hi)/2;
        return f(query(2*p, lo, mid, i, j),
                 query(2*p+1, mid+1, hi, i, j));
    }
    T query (ll i, ll j) {
        return query(1, 0, n-1, i, j);
    }

    void update (ll p, ll lo, ll hi, ll i, ll j, T x) {
        if (hi < i || j < lo) return;
        if (i <= lo && hi <= j) {
            lazy[p] += x;
            return;
        }

        unlazy(p, lo, hi);

        ll mid = (lo + hi)/2;
        update(2*p, lo, mid, i, j, x);
        update(2*p+1, mid+1, hi, i, j, x);
        combine(p, lo, hi);
    }

    void update (ll i, ll j, T x) {
        update(1, 0, n-1, i, j, x);
    }
};
