#include <bits/stdc++.h>
using namespace std;

using ll = long long;

vector<ll> Z (const string& s) {
    ll n = s.size(), lo = 0, hi = 0;
    vector<ll> z (n);

    for (ll i = 1; i < n; i++) {
        if (i <= hi)
            z[i] = min(hi - i + 1, z[i - lo]);
        
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            z[i]++;

        if (i + z[i] - 1 > hi) {
            lo = i;
            hi = i + z[i] - 1;
        }
    }

    return z;
}
