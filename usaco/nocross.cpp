#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;
using ld = long double;

void initio (string file = "") {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    if (file != "") {
        freopen((file + ".in").c_str(), "r", stdin);
        freopen((file + ".out").c_str(), "w", stdout);
    }
}

template<typename T, typename U>
ostream& operator << (ostream& out, const pair<T, U>& p) {
    return out << "(" << p.first << " " << p.second << ")";
}

template<typename T>
ostream& prints (ostream& out, const T& v) {
    out << "[";
    for (auto it = v.begin(); it != v.end(); ++it) {
        out << " " << *it;
    }
    out << " ]\n";

    return out;
}
#define PRINTS(C) template<typename T> ostream& operator << (ostream& out, const C<T>& v) { return prints(out, v); } 
#define PRINTS2(C) template<typename T, typename U> ostream& operator << (ostream& out, const C<T, U>& v) { return prints(out, v); } 
PRINTS(vector)
PRINTS(list)
PRINTS(deque)
PRINTS(set)
PRINTS(multiset)
PRINTS(unordered_set)
PRINTS(unordered_multiset)
PRINTS2(map)
PRINTS2(multimap)
PRINTS2(unordered_map)
PRINTS2(unordered_multimap)

void println () {
    cerr << "\n";
}
template<typename T, typename... Ts>
void println (const T& t, Ts... ts) {
    cerr << t << " ";
    println(ts...);
}

template<typename T>
struct SegTree {
    ll n;
    vector<T> t;
    T noval = 0;

    T f (T a, T b) {
        return max(a, b);
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

    T query (ll p, ll lo, ll hi, ll i, ll j) {
        if (hi < i || j < lo) return noval;
        if (i <= lo && hi <= j) return t[p];

        ll mid = (lo + hi)/2;
        return f(query(2*p, lo, mid, i, j),
                 query(2*p+1, mid+1, hi, i, j));
    }
    T query (ll i, ll j) {
        if (j < i) return 0;
        return query(1, 0, n-1, i, j);
    }

    void update (ll p, ll lo, ll hi, ll i, T x) {
        if (hi < i || i < lo) return;
        if (lo == hi) {
            t[p] = max(t[p], x);
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

ll n;
vector<ll> v, inv, u, inu;
SegTree<ll> t;


int main () {
    initio("nocross");

    cin >> n;
    
    v.resize(n);
    inv.resize(n);
    u.resize(n);
    inu.resize(n);

    for (int i = 0; i < n; i++) {
        cin >> v[i];
        v[i]--;

        inv[v[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        cin >> u[i];
        u[i]--;

        inu[u[i]] = i;
    }
    t.build(vector<ll>(n, 0));

    for (int i = 0; i < n; i++) {
        ll x = u[i];
        vector<ll> js;

        for (ll y = max(0LL, x-4); y <= min(n-1, x+4); y++) {
            js.push_back(inv[y]);
        }
        sort(js.rbegin(), js.rend());

        for (auto j : js) {
            ll r = 1 + t.query(0, j-1);
            t.update(j, r); 
        }
    }

    cout << t.query(0, n-1) << "\n";

    return 0;
}
