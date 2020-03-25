#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll n, m;
vector<vector<ll>> adj;
vector<ll> nx, d;

ll f (ll i) {
    if (d[i] > 0) return d[i];
    if (i == n-1) return 0;

    ll r = -1e9;
    for (auto& j : adj[i]) {
        ll t = r;
        r = max(r, 1 + f(j));
        if (t != r) nx[i] = j;
    }

    return d[i] = r;
}

int main () {
    cin >> n >> m;
    adj.resize(n);
    d.resize(n);
    nx.resize(n);

    while (m-->0) {
        ll a, b;
        cin >> a >> b;
        a--;
        b--;

        adj[a].push_back(b);
    }

    vector<ll> v;
    if (f(0) < 0) {
        cout << "IMPOSSIBLE";
        return 0;
    }
    ll i = 0;
    v.push_back(0);

    while (i != n-1) {
        i = nx[i];
        v.push_back(i);
    }

    cout << v.size();

    for (auto x : v) cout << " " << x+1;
    
    
     
    return 0;
}
