#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Trie {
    vector<Trie> t;
    vector<ll> z = vector<ll>(2);

    void add (ll x, ll k) {
        if (k < 0) return;
        if (t.empty()) t.resize(2);

        z[x >> k & 1]++;
        t[x >> k & 1].add(x, k-1);
    }
    
    ll solve (ll x, ll k) {
        if (k < 0) return 0;
        if (z[!(x >> k & 1)]) {
            return (1 << k) + t[!(x >> k & 1)].solve(x, k-1);
        }
        else {  
            return t[x >> k & 1].solve(x, k-1);
        }
    }
};

int main () {
    ll n, b = 0, a = 0;
    cin >> n;

    Trie t;
    t.add(0, 31);

    while (n-->0) {
        ll x;
        cin >> x;
        a ^= x;

        b = max(b, t.solve(a, 31));
        t.add(a, 31);
    }

    cout << b;
}