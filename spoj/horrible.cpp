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

    T at (int p, int lo, int hi) {
        return t[p] + (hi - lo + 1) * lazy[p];
    }
    void unlazy (int p, int lo, int hi) {
        lazy[2*p] += lazy[p];
        lazy[2*p+1] += lazy[p];
        lazy[p] = 0;

        combine(p, lo, hi);
    }

    void combine (int p, int lo, int hi) {
        int mid = (lo + hi)/2;
        t[p] = f(at(2*p, lo, mid), at(2*p+1, mid+1, hi));
    }

    void build (vector<T>& v, int p, int lo, int hi) {
        if (lo == hi) {
            t[p] = v[lo];
            return;
        }
        
        int mid = (lo + hi)/2;
        build(v, 2*p, lo, mid);
        build(v, 2*p+1, mid+1, hi);

        combine(p, lo, hi);
    }
    void build (vector<T>& v) {
        n = v.size();

        t.assign(4*n, noval);
        lazy.assign(4*n, noval);
        build(v, 1, 0, n-1);
    }

    T query (int p, int lo, int hi, int i, int j) {
        if (hi < i || j < lo) return noval;
        if (i <= lo && hi <= j) return at(p, lo, hi);

        unlazy(p, lo, hi);

        int mid = (lo + hi)/2;
        return f(query(2*p, lo, mid, i, j),
                 query(2*p+1, mid+1, hi, i, j));
    }
    T query (int i, int j) {
        return query(1, 0, n-1, i, j);
    }

    void update (int p, int lo, int hi, int i, int j, T x) {
        if (hi < i || j < lo) return;
        if (i <= lo && hi <= j) {
            lazy[p] += x;
            return;
        }

        unlazy(p, lo, hi);

        int mid = (lo + hi)/2;
        update(2*p, lo, mid, i, j, x);
        update(2*p+1, mid+1, hi, i, j, x);
        combine(p, lo, hi);
    }

    void update (int i, int j, T x) {
        update(1, 0, n-1, i, j, x);
    }
};

ll n;
vector<ll> v;
SegTree<ll> t;

int main () {
    ll times;

    cin >> times;
    while (times-->0) {
        ll q;
        cin >> n >> q;
        v.assign(n, 0);

        t.build(v);

        while (q-->0) {
            ll c, i, j, x;
            cin >> c >> i >> j;
            i--;
            j--;

            if (c) {
                cout << t.query(i, j) << "\n";
            }
            else {
                cin >> x;
                t.update(i, j, x);
            }
        }
    }
}