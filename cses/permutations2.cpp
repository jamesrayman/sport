#include <bits/stdc++.h>
using namespace std;

using ll = long long;
ll mod = 1e9+7;

vector<ll> f { 1, 1 };
ll n;

ll nCr (ll n, ll r) {
    static unordered_map<ll, unordered_map<ll, ll>> d;

    if (r == 0) return 1;
    if (r < 0) return 0;
    if (2*r > n) return nCr(n, n-r);
    if (d[n].count(r)) return d[n][r];

    return d[n][r] = (nCr(n-1, r) + nCr(n-1, r-1)) % mod;
}

ll modPow (ll b, ll e) {
    ll r = 1;

    while (e) {
        if (e%2) r = r*b % mod;
        b = b*b % mod;

        e /= 2;
    }
    return r;
}

int main () {
    cin >> n;

    while (f.size() <= n)
        f.push_back(f.size() * f.back() % mod);
    
    ll t = f[n];

    ll dir = -1;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            ll delta = nCr(i-1, j-1) * nCr(n-i, j) % mod * modPow(2, j) % mod * f[n-i] % mod;
            t += dir * delta + 2*mod;
            t %= mod;
        }
        dir *= -1;
    }

    cout << t;
}
