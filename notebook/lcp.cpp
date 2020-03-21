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

vector<ll> lcp (const string& s, const vector<ll>& p) {
    ll n = s.size(), k = 0;
    vector<ll> rank (n), v (n-1);

    for (int i = 0; i < n; i++) rank[p[i]] = i;

    for (int i = 0; i < n; i++) {
        if (rank[i] + 1 == n) {
            k = 0;
            continue;
        }

        ll j = p[rank[i]+1];
        while (k < n && s[(i+k)%n] == s[(j+k)%n])
            k++;

        v[rank[i]] = k;
        if (k > 0) k--;
    }

    return v;
}
