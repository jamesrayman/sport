#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

template<typename T>
struct SegTree {
    ll n;
    vector<T> t;
    T noval = { 1e8, -1 };

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
        if (i > j) return query(j, i);
        return query(1, 0, n-1, i, j);
    }
};

ll n;
vector<vector<ll>> adj;
vector<pll> trav;
vector<ll> pos, par, ans;

void treeify (int i, int p, int h) {
    par[i] = p;

    pll mark = { h, i };
    pos[i] = trav.size();
    trav.push_back(mark);

    for (auto& j : adj[i]) {
        if (j == p) continue;
        treeify(j, i, h+1);
        trav.push_back(mark);
    }
}

void calc (int i) {
    for (auto& j : adj[i]) {
        if (j == par[i]) continue;
        calc(j);
        ans[i] += ans[j];
    }
}

int main () {
    int q;
    cin >> n >> q;

    adj.resize(n);
    ans.resize(n);
    pos.resize(n);
    par.resize(n);

    for (int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    treeify(0, -1, 0);

    SegTree<pll> t;
    t.build(trav);

    while (q-->0) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;

        ans[a]++;
        ans[b]++;
        int lca = t.query(pos[a], pos[b]).second;
        ans[lca]--;
        if (lca != 0) ans[par[lca]]--;
    }
    calc(0);

    for (auto x : ans) cout << x << " ";
}
