#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template<typename T>
struct SegTree {
    ll n;
    vector<T> t, lazy;
    T noval = 1e14;

    T f (T a, T b) {
        return min(a, b);
    }

    T at (int p, int lo, int hi) {
        return t[p] + lazy[p];
    }
    void unlazy (int p, int lo, int hi) {
        lazy[2*p] += lazy[p];
        lazy[2*p+1] += lazy[p];
        lazy[p] = 0;

        combine(p, lo, hi);
    }

    void combine (int p, int lo, int hi) {
        t[p] = f(at(2*p, lo, hi), at(2*p+1, lo, hi));
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
        lazy.assign(4*n, 0);
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

ll n, q;
vector<ll> v;
SegTree<ll> t;

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    v.resize(n);

    for (auto& x : v) cin >> x;

    t.build(v);
    cin >> q;

    string s;
    getline(cin, s);
    while (q-->0) {
        getline(cin, s);
        ll a, b, c;
        stringstream ss (s);
        ss >> a >> b;

        if (ss >> c) {
            if (a <= b) {
                t.update(a, b, c);
            }
            else {
                t.update(0, b, c);
                t.update(a, n-1, c);
            }
        }
        else {
            if (a <= b) {
                cout << t.query(a, b) << "\n";
            }
            else {
                cout << min(t.query(0, b), t.query(a, n-1)) << "\n";
            }
        }
    } 
}

