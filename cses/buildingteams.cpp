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

    for (int x = 0; x < n; x++) {
        if (p[x] == -1) {
            queue<ll> q;
            q.push(x);
            q.push(0);

            while (!q.empty()) {
                ll i = q.front();
                q.pop();
                ll r = q.front();
                q.pop();

                if (p[i] == !r) {
                    cout << "IMPOSSIBLE";
                    return 0;
                }
                if (p[i] != -1) continue;

                p[i] = r; 

                for (auto& j : adj[i]) {
                    q.push(j);
                    q.push(!r);
                }
            }
        }
    }
    for (auto& x : p) cout << x+1 << " ";

    return 0;
}