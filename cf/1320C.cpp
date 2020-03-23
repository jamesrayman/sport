#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

template<typename T>
struct SegTree {
    ll n;
    vector<T> t, lazy;
    T noval = -1e15;
    T nolazy = 0;

    T f (T a, T b) {
        return max(a, b);
    }

    T at (ll p, ll lo, ll hi) {
        return t[p] + lazy[p];
    }
    void unlazy (ll p, ll lo, ll hi) {
        lazy[2*p] += lazy[p];
        lazy[2*p+1] += lazy[p];
        lazy[p] = nolazy;

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
        lazy.assign(4*n, nolazy);
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


ll n, m, p;
vector<pll> a, b;
vector<pair<ll, pll>> v;

void filter (vector<pll>& v) {
    vector<pll> u;

    for (auto& x : v) {
        while (!u.empty() && u.back().second >= x.second) u.pop_back();
        u.push_back(x);
    }

    v = u;
}

ll cost (ll x, ll y) {
    auto ita = lower_bound(a.begin(), a.end(), make_pair(x+1, -1LL));
    auto itb = lower_bound(b.begin(), b.end(), make_pair(y+1, -1LL));
    if (ita == a.end() || itb == b.end()) return 1e18;
    return ita->second + itb->second;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m >> p;
    
    a.resize(n);
    b.resize(m);
    v.resize(p);

    for (auto& x : a) cin >> x.first >> x.second;
    for (auto& x : b) cin >> x.first >> x.second;
    for (auto& x : v) cin >> x.first >> x.second.first >> x.second.second;

    auto cmp = [](pll x, pll y) {
        if (x.first == y.first) return x.second > y.second;
        return x.first < y.first;
    };
    sort(a.begin(), a.end(), cmp);
    sort(b.begin(), b.end(), cmp);
    sort(v.begin(), v.end());

    filter(a);
    filter(b);
    n = a.size();
    m = b.size();

    ll i = 0, j = 0;
    SegTree<ll> t;
    t.build(vector<ll>(1e6+10));

    ll best = -cost(-1, -1);
    ll c = a.begin()->second;

    for (i = 0; i < m; i++) {
        t.update(j, b[i].first-1, -b[i].second);
        j = b[i].first;
    }
    t.update(j, t.n-1, -1e15);

    i = j = 0;

    for (ll x = 0; x <= 1e6; x++) {
        while (j < n && a[j].first <= x) {
            j++;
            if (j == n) {
                x = 1e7;
                break;
            }
            c = a[j].second;
        }
        if (x > 1e6) break;

        while (i < p && v[i].first <= x) {
            t.update(v[i].second.first, t.n-1, v[i].second.second);
            i++;
        }
        best = max(best, t.query(0, t.n-1) - c);
    }
    cout << best << "\n";
}