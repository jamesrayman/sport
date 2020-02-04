#include <bits/stdc++.h>
using namespace std;

using ll = long long;
ll n;
vector<ll> pre, in, post;
vector<ll> pos;

void solve (int i, int j, int ini, int inj) {
    if (ini > inj) return;
    post[j] = pre[i];

    if (ini == inj) return;

    int k = pos[pre[i]];
    int lt = k - ini;
    int rt = inj - k;
    
    solve(i+1, j-rt-1, ini, k-1);
    solve(i+lt+1, j-1, k+1, inj);
}

int main () {
    cin >> n;
    pre.resize(n);
    in.resize(n);
    post.resize(n);
    pos.resize(n);

    for (auto& x : pre) {
        cin >> x;
        x--;
    }
    for (auto& x : in) {
        cin >> x;
        x--;
    }

    for (int i = 0; i < n; i++) {
        pos[in[i]] = i;
    }

    solve(0, n-1, 0, n-1);

    for (auto& x : post) cout << 1+x << " ";
}
