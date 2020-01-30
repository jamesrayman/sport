#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

ll n;
vector<set<ll>> adj, adk;
vector<ll> v;

void bfs (int i, int p, int h) {
    v[i] = h;
    for (auto j : adk[i]) {
        if (j == p) continue;
        bfs(j, i, h+1);
    }
}

int main () {
    cin >> n;

    adj.resize(n);
    v.resize(n);
    
    for (int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;

        adj[a].insert(b);
        adj[b].insert(a);
    }

    adk = adj;
    queue<ll> q;

    for (int i = 0; i < n; i++) {
        if (adj[i].size() == 1) {
            q.push(i);
            q.push(0);
        }
    }

    int d = -1;
    vector<ll> centers;
    unordered_set<ll> visited;

    while (q.size() > 0) {
        int i = q.front();
        q.pop();
        int h = q.front();
        q.pop();
        if (h > d) {
            centers.clear();
            d = h;
        }
        if (d == h) {
            centers.push_back(i);
        }

        int j = *adj[i].begin();
        adj[j].erase(i);

        if (adj[j].size() <= 1 && !visited.count(j)) {
            visited.insert(j);
            q.push(j);
            q.push(h+1);
        } 
    }
    if (centers.size() == 1) {
        bfs(centers[0], -1, d);
    }
    else {
        bfs(centers[0], centers[1], d+1);
        bfs(centers[1], centers[0], d+1);
        cout << d << "\n";
    }
    for (auto& x : v) cout << x << " ";
}
