#include <bits/stdc++.h>
using namespace std;

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

ll d [51][51][51][51];
ll n;
vector<ll> v;

ll f (ll i, ll j, ll lo, ll hi) {
    if (i > j) return 0;
    if (d[i][j][lo][hi] > 0) return d[i][j][lo][hi]-1;

    ll r = 0;

    r = max(r, f(i+1, j, lo, hi));
    r = max(r, f(i, j-1, lo, hi));
    if (lo <= v[i] && v[i] <= hi) {
        r = max(r, 1+f(i+1, j, v[i], hi));
        r = max(r, 1+f(i+1, j-1, lo, v[i]));
    }
    if (lo <= v[j] && v[j] <= hi) {
        r = max(r, 1+f(i, j-1, lo, v[j]));
        r = max(r, 1+f(i+1, j-1, v[j], hi));
    }

    if (lo <= v[j] && v[j] <= v[i] && v[i] <= hi && i < j) {
        r = max(r, 2+f(i+1, j-1, v[j], v[i]));
    }

    d[i][j][lo][hi] = r+1;
    return r;
}

int main () {
    initio("subrev");

    cin >> n;
    v.resize(n);
    for (auto& x : v) cin >> x;

    cout << f(0, n-1, 0, 50);

    return 0;
}
