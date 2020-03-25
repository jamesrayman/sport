#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

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
using OrderTree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct Fenwick {
    ll n;
    vector<OrderTree<int>> t;

    Fenwick (ll n = 2e5) : n(n) {
        t.resize(n);
    }
 
    void update (ll i, ll delta) {
        while (i < n) {
            t[i].insert(delta);
            i += i&-i;
        }
    }
 
    ll query (ll i, ll x, ll y) {
        ll r = 0;
        while (i > 0) {
            auto& uu = t[i];
            r += uu.order_of_key(x);
            r += uu.size() - uu.order_of_key(y);
            i -= i&-i;
        }
        return r;
    }
};

ll n, k;
vector<ll> v, u, w;

ll t = 0;

void solve () {
    Fenwick f (n+1);

    for (int i = n-1; i > -1; i--) {
        t += f.query(u[i]+1, w[i] - k, w[i] + k + 1);
        f.update(u[i]+1, w[i]);
    }
}

int main () {
    initio("friendcross");

    cin >> n >> k;
    v.resize(n);
    u.resize(n);
    w.resize(n);

    for (int i = 0; i < n; i++) {
        ll a;
        cin >> a;
        a--;

        v[a] = i;
    }
    for (int i = 0; i < n; i++) {
        ll a;
        cin >> a;
        a--;

        u[i] = v[a];
        w[i] = a;
    }

    solve();

    cout << t << "\n";

    return 0;
}
