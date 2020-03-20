#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll n, m;
vector<vector<ll>> adj;
vector<ll> v, s, visited;

bool solve (ll i, ll p) {
    if (s[i]) {
        v.push_back(i);
        return true;
    }

    if (visited[i]) return false;
    visited[i] = true;

    s[i] = true;
    v.push_back(i);
    
    for (auto& j : adj[i]) {
        if (j == p) continue;
        
        if (solve(j, i)) {
            return true;
        }
    }

    s[i] = false;
    v.pop_back();
    return false;
}

int main () {
    cin >> n >> m;
    adj.resize(n);
    s.resize(n);
    visited.resize(n);

    while (m-->0) {
        ll a, b;
        cin >> a >> b;
        a--;
        b--;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (solve(i, -1)) {
                reverse(v.begin(), v.end());
                while (v.back() != v.front()) v.pop_back();

                cout << v.size();
                for (auto x : v) cout << " " << x+1;
                return 0;
            }
        }
    }
    cout << "IMPOSSIBLE";

    return 0;
}
