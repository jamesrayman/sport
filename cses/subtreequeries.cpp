#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll n;
vector<ll> v;

struct SegTree {
    vector<ll> t;

    void build (int p, int lo, int hi) {
        if (lo == hi) {
            t[p] = v[lo];
            return;
        }

        int mid = (lo + hi)/2;
        build(2*p, lo, mid);
        build(2*p+1, mid+1, hi);
        t[p] = t[2*p] + t[2*p+1];
    }
    void build () {
        t.resize(4*n);
        build(1, 0, n-1);
    }
    ll query (int i, int j) {
        return query(1, 0, n-1, i, j);
    }
    ll query (int p, int lo, int hi, int i, int j) {
        if (lo > j || hi < i) return 0;
        if (i <= lo && hi <= j) return t[p];

        int mid = (lo + hi)/2;
        return query(2*p, lo, mid, i, j) + query(2*p+1, mid+1, hi, i, j);
    }
    void update (int i, int x) {
        update(1, 0, n-1, i, x);
    }
    void update (int p, int lo, int hi, int i, int x) {
        if (lo > i || hi < i) return;
        if (i == lo && i == hi) {
            t[p] = x;
            return;
        }
        int mid = (lo + hi)/2;
        update(2*p, lo, mid, i, x);
        update(2*p+1, mid+1, hi, i, x);
        t[p] = t[2*p] + t[2*p+1];
    }
};

vector<vector<ll>> adj;
vector<ll> b, e, u;

void treeify (int i, int p) {
    b[i] = v.size();
    v.push_back(u[i]);

    for (auto& j : adj[i]) {
        if (j == p) continue;
        treeify(j, i);
    }

    e[i] = v.size()-1;
}

int main () {
    int q;
    cin >> n >> q;

    adj.resize(n);
    u.resize(n);
    b.resize(n);
    e.resize(n);
    for (auto& x : u) cin >> x;

    for (int i = 0; i < n-1; i++) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;

        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    treeify(0, -1);

    SegTree t;
    t.build();

    while (q-->0) {
        int c, x, y;
        cin >> c >> x;
        x--;

        if (c == 2) {
            cout << t.query(b[x], e[x]) << " ";
        }
        else {
            cin >> y;
            t.update(b[x], y);
        }
    }
}
