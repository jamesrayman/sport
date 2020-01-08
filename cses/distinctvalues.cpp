#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n = 2e5+10;
    vector<int> t = vector<int>(n);

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

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;
    vector<int> v (n);
    vector<pair<pair<int, int>, int>> u (q);

    for (auto& x : v) cin >> x;

    int j = 0;
    for (auto& p : u) {
        cin >> p.first.second >> p.first.first;
        p.first.first--;
        p.first.second--;
        p.second = j++;
    }

    sort(u.begin(), u.end());
    vector<int> ans (q);
    map<int, int> prev;

    Fenwick f;
    j = 0;

    for (int i = 0; i < n; i++) {
        f.update(prev[v[i]]+1, 1);

        prev[v[i]] = i+1;

        while (j < u.size() && u[j].first.first <= i) {
            ans[u[j].second] = f.query(u[j].first.second+1) - u[j].first.second;

            j++;
        } 
    }

    for (auto& x : ans) {
        cout << x << "\n";
    }
}