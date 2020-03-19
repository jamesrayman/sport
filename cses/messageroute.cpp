#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll n, m;

int main () {
    cin >> n >> m;

    vector<vector<ll>> adj (n);
    vector<ll> p (n, -1);

    while (m-->0) {
        ll a, b;
        cin >> a >> b;
        a--;
        b--;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    queue<ll> q;
    q.push(0);
    q.push(-2);

    while (!q.empty()) {
        ll i = q.front();
        q.pop();
        ll r = q.front();
        q.pop();

        if (p[i] != -1) continue;

        p[i] = r; 

        if (i == n-1) {
            vector<ll> v;

            while (i != -2) {
                v.push_back(i);

                i = p[i];
            }
            reverse(v.begin(), v.end());

            cout << v.size();
            for (auto& x : v) cout << " " << 1+x;

            return 0;
        }
        for (auto& j : adj[i]) {
            q.push(j);
            q.push(i);
        }
    }
    cout << "IMPOSSIBLE";

    return 0;
}