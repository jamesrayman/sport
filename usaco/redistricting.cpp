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
    T noval = 2e9;

    T f (T a, T b) {
        return min(a, b);
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
    void build (ll n, T val = T()) {
        build (vector<T>(n, val));
    }

    T query (ll p, ll lo, ll hi, ll i, ll j) {
        if (hi < i || j < lo) return noval;
        if (i <= lo && hi <= j) return t[p];

        ll mid = (lo + hi)/2;
        return f(query(2*p, lo, mid, i, j),
                 query(2*p+1, mid+1, hi, i, j));
    }
    T query (ll i, ll j) {
        if (i > j) return noval;
        return query(1, 0, n-1, i, j);
    }

    void update (ll p, ll lo, ll hi, ll i, T x) {
        if (hi < i || i < lo) return;
        if (lo == hi) {
            t[p] = x;
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

ll n, k, m;
vector<ll> v { 0 };

int main () {
    initio("redistricting");

    string s;
    cin >> n >> k >> s;

    for (auto c : s) {
        v.push_back(v.back() - 1 + 2*(c == 'H'));
    }
    ll toadd = -*min_element(v.begin(), v.end());
    for (auto& x : v) x += toadd;
    m = 1+*max_element(v.begin(), v.end());

    SegTree<ll> t;
    t.build(m, 2e9); // v value -> cost

    vector<ll> d (n+1);
    vector<set<pll>> st (m, { { 2e9, -1 } }); // v value -> cost (d value), i value

    st[v[0]].insert({ 0, 0 });
    d[0] = 0;
    t.update(v[0], 0);

    for (int i = 1; i < n+1; i++) {
        d[i] = min(1 + t.query(v[i], m-1), t.query(0, v[i]-1));

        st[v[i]].insert({ d[i], i });
        t.update(v[i], st[v[i]].begin()->first);

        if (i - k >= 0) {
            st[v[i-k]].erase({ d[i-k], i-k });
            t.update(v[i-k], st[v[i-k]].begin()->first);
        }
    }

    cout << d[n] << "\n";

    return 0;
}
