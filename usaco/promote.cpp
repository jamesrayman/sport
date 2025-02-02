#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void initio (string file = "") {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    if (file != "") {
        freopen((file + ".in").c_str(), "r", stdin);
        freopen((file + ".out").c_str(), "w", stdout);
    }
}

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

ll n;
vector<ll> v, u;
vector<vector<ll>> adj;
vector<pair<ll, ll>> r;
MergeSortTree<ll> t;

void go (ll i) {
    u.push_back(-v[i]);
    r[i].first = u.size();

    for (auto j : adj[i]) {
        go(j);
    } 

    r[i].second = u.size()-1;
}

int main () {
    initio("promote");
    cin >> n;

    v.resize(n);
    r.resize(n);
    adj.resize(n);
    for (auto& x : v) cin >> x;

    for (int i = 1; i < n; i++) {
        ll a;
        cin >> a;
        a--;

        adj[a].push_back(i);
    }

    go(0);
    t.build(u);

    for (int i = 0; i < n; i++) {
        cout << t.query(r[i].first, r[i].second, -v[i]) << "\n";
    }
    return 0;
}