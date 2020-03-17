#include <bits/stdc++.h>
using namespace std;

using ll = long long;

vector<ll> v;
ll n, m;

ll f () {
    ll best = 0;

    vector<pair<ll, ll>> d;
    d.push_back({ 0, -1 });

    for (int i = 0; i <= n; i++) {
        ll a = 0;
        if (i < n) a = v[i];

        while (d.back().first > a) {
            ll b = d.back().first;
            d.pop_back();

            best = max(best, b * (i - d.back().second - 1));
        }
        d.push_back({ a, i });
    }
    return best;
}

int main () {
    cin >> m >> n;

    v.resize(n);
    ll best = 0;

    while (m-->0) {
        string s;
        cin >> s;

        for (int i = 0; i < n; i++) {
            if (s[i] == '*') v[i] = 0;
            else v[i]++;
        }
        
        best = max(best, f());
    }
    cout << best;

    return 0;
}