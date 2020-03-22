#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll n, m;
vector<pair<ll, pair<ll, ll>>> e;
vector<vector<ll>> f;
vector<ll> v;

int main () {
    cin >> n >> m;
    v.resize(n, -1e17);

    f.resize(n);

    for (int i = 0; i < m; i++) {
        ll a, b, w;
        cin >> a >> b >> w;
        a--;
        b--;

        e.push_back({ w, { a, b } });
        f[b].push_back(a);
    }

    queue<ll> q;
    q.push(n-1);

    while (!q.empty()) {
        ll i = q.front();
        q.pop();

        if (v[i] != -1e17) continue;
        v[i] = -1e16;

        for (auto j : f[i]) {
            q.push(j);
        }
    }

    bool good = false;

    v[0] = 0;

    for (int i = 0; i < 2*n; i++) {
        good = false;

        for (auto p : e) {
            if (v[p.second.first] == -1e16) continue;
            if (v[p.second.second] == -1e17) continue;
            if (v[p.second.second] < v[p.second.first] + p.first) {
                v[p.second.second] = v[p.second.first] + p.first;
                good = true;
            }
        }
        if (!good) break;
    }
    
    if (good) cout << -1;
    else cout << v.back();

    return 0;
}