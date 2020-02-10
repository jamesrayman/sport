#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct SegTree {
    ll n;
    vector<T> t;
    T noval = 1e8;

    T f (T a, T b) {
        return min(a, b);
    }

    void combine (int p) {
        t[p] = f(t[2*p], t[2*p+1]);
    }

    void build (vector<T>& v, int p, int lo, int hi) {
        if (lo == hi) {
            t[p] = v[lo];
            return;
        }
        
        int mid = (lo + hi)/2;
        build(v, 2*p, lo, mid);
        build(v, 2*p+1, mid+1, hi);

        combine(p);
    }
    void build (vector<T>& v) {
        n = v.size();

        t.resize(4*n);
        build(v, 1, 0, n-1);
    }

    T query (int p, int lo, int hi, int i, int j) {
        if (hi < i || j < lo) return noval;
        if (i <= lo && hi <= j) return t[p];

        int mid = (lo + hi)/2;
        return f(query(2*p, lo, mid, i, j),
                 query(2*p+1, mid+1, hi, i, j));
    }
    T query (int i, int j) {
        return query(1, 0, n-1, i, j);
    }
};