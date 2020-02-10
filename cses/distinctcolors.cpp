#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll n;
vector<ll> v, ans, u;

struct Fenwick {
    int n;
    vector<int> t;

    Fenwick (int n = 2e5) : n(n) {
        t.resize(n);
    }
 
    void update (int i, int delta) {
        while (i < n) {
            t[i] += delta;
            i += i&-i;
        }
    }
 
    int query (int i) {
        int r = 0;
        while (i > 0) {
            r += t[i];
            i -= i&-i;
        }
        return r;
    }
};

vector<vector<ll>> adj;
unordered_map<ll, ll> pre;

Fenwick f;

void treeify (int i, int p) {
    int k = u.size();
    u.push_back(v[i]);

    f.update(pre[v[i]] + 1, 1);
    pre[v[i]] = k+1;

    for (auto& j : adj[i]) {
        if (j == p) continue;
        
        treeify(j, i);
    }

    ans[i] = f.query(k+1) - k;
}

int main () {
    cin >> n;

    v.resize(n);
    ans.resize(n);
    adj.resize(n);

    for (auto& x : v) cin >> x;

    for (int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    treeify(0, -1);

    for (auto x : ans) cout << x << " ";
}
