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

int main () {
    initio("");

    return 0;
}