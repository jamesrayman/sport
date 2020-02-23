#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void sos (vector<ll>& v, ll k) {
    for (ll i = 0; i < k; i++) {
        for (ll mask = 0; mask < (1 << k); mask++) {
            if (mask & (1 << i)) {
                v[mask] += v[mask - (1 << i)];
            }
        }
    }
}
