#include <bits/stdc++.h>
using namespace std;

using ll = long long;

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

ll n;
vector<pair<ll, ll>> v;

int main () {
    cin >> n;

    v.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i].first;
        v[i].second = i+1;
    }
    Fenwick f (n+1);
    for (int i = 0; i < n; i++) {
        f.update(i+1, 1);
    }
    sort(v.begin(), v.end());

    ll t = 0;

    for (auto& x : v) {
        f.update(x.second, -1);

        ll a = f.query(x.second);
        n--;
        t += min(a, n-a);
    }

    cout << t;
}
