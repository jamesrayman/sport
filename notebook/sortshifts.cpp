#include <bits/stdc++.h>
using namespace std;

using ll = long long;

vector<ll> shifts (const string& s) {
    ll n = s.size();
    vector<ll> p (n), c (n);

    iota(p.begin(), p.end(), 0);
    sort(p.begin(), p.end(), [&](ll i, ll j) { return s[i] < s[j]; });


    ll ci = 0;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i-1]])
            ci++;
        c[p[i]] = ci; 
    }

    for (ll k = 1; k < n; k *= 2) {
        vector<ll> nc (n);

        auto cmp = [&](ll i, ll j) {
            if (c[i] != c[j]) return c[i] < c[j];
            return c[(i+k)%n] < c[(j+k)%n];
        };

        sort(p.begin(), p.end(), cmp);

        ci = 0; 
        for (int i = 1; i < n; i++) {
            if (cmp(p[i], p[i-1]) || cmp(p[i-1], p[i]))
                ci++;
            nc[p[i]] = ci; 
        }

        c = nc;
    } 
    return p;
}
