#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

using ll = int;
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

ll n;

struct Fenwick {
    tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> t;

    void update (ll i, ll x) {
        t.insert(i);
    }

    ll query (ll i) {
        return t.order_of_key(i);
    }
};

struct FENWICK {
    vector<Fenwick> t;

    void update (ll i, ll x, ll y) {
        while (i < t.size()) {
            t[i].update(x, y); 
            i += i&-i;
        }
    }

    ll query (ll i, ll j) {
        ll r = 0;
        while (i > 0) {
            r += t[i].query(j);
            i -= i&-i;
        }
        return r;
    }
};
vector<ll> v;
FENWICK f;

vector<vector<ll>> adj;
vector<ll> ans;

ll pos = 0;
ll go (ll i) {
    ll k = pos;
    f.update(pos+1, v[i]+1, 1);
    pos++;
    ll sts = 1;

    for (auto j : adj[i]) {
        sts += go(j);
    }

    ans[i] = sts - 1 - (f.query(pos + 1, v[i]+1) - f.query(k+1, v[i]+1));
    return sts;
}

int main () {
    initio("promote");

    cin >> n;
    f.t.resize(n+10);
    v.resize(n);
    adj.resize(n);
    ans.resize(n);

    vector<pair<ll, ll>> u;
    for (auto& x : v) {
        cin >> x;
        u.push_back({ x, u.size() });
    }
    sort(u.begin(), u.end());

    for (int i = 0; i < n; i++) {
        v[u[i].second] = i;
    }

    for (int i = 1; i < n; i++) {
        ll a;
        cin >> a;
        a--;

        adj[a].push_back(i);
    }
    go(0);

    for (auto& x : ans) cout << x << "\n";

    return 0;
}
