#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main () {
    ll n, best = 0;
    cin >> n;

    vector<pair<ll, ll>> d;
    d.push_back({ 0, -1 });

    for (int i = 0; i <= n; i++) {
        ll a = 0;
        if (i < n) cin >> a;

        while (d.back().first > a) {
            ll b = d.back().first;
            d.pop_back();

            best = max(best, b * (i - d.back().second - 1));
        }
        d.push_back({ a, i });
    }

    cout << best;    
}
