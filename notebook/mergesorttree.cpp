#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template<typename T>
struct MergeSortTree {
    ll n;
    vector<vector<T>> t;

    void combine (ll p) {
        t[p].resize(t[2*p].size() + t[2*p+1].size());
        merge(t[2*p].begin(), t[2*p].end(), t[2*p+1].begin(), t[2*p+1].end(), t[p].begin());
    }

    void build (const vector<T>& v, ll p, ll lo, ll hi) {
        if (lo == hi) {
            t[p].push_back(v[lo]);
            return;
        }
        
        ll mid = (lo + hi)/2;
        build(v, 2*p, lo, mid);
        build(v, 2*p+1, mid+1, hi);

        combine(p);
    }
    void build (const vector<T>& v) {
        n = v.size();

        t.assign(4*n, vector<T>());
        build(v, 1, 0, n-1);
    }

    ll query (ll p, ll lo, ll hi, ll i, ll j, const T& x) {
        if (hi < i || j < lo) return 0;
        if (i <= lo && hi <= j) {
            return lower_bound(t[p].begin(), t[p].end(), x) - t[p].begin();
        }

        ll mid = (lo + hi)/2;
        return query(2*p, lo, mid, i, j, x) +
               query(2*p+1, mid+1, hi, i, j, x);
    }
    ll query (ll i, ll j, const T& x) {
        return query(1, 0, n-1, i, j, x);
    }
};
