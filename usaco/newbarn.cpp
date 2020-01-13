#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

struct Tree {
    int n = 0;

    vector<ll> p;
    vector<vector<pll>> adj;
    vector<ll> prev;
    vector<ll> sts;

    void init () {
        p.resize(n, -1);
        adj.resize(n);
        prev.resize(n, -1);
        sts.resize(n, -1);
    }

    void calcSts (int i) {
        sts[i] = 1;

        for (auto& e : adj[i]) {
            calcSts(e.first);
            sts[i] += sts[e.first];
        }
    }

    void centroid (int i, int pr) {
        prev[i] = pr;


    }
};

int main () {
    ifstream input ("newbarn.in");
    ofstream output ("newbarn.out");
    
    int q;
    input >> q;

    vector<pll> qs (q);

    Tree t;

    for (auto& x : qs) {
        char c;
        input >> c >> x.second;
        x.second--;
        if (c == 'B') {
            t.n++;
            x.first = 1;
        }
    }

    t.init();

    int i = 0;
    for (auto x : qs) {
        if (x.first == 1) {
            if (i != 0) {
                t.p[i] = x.second;
                t.adj[x.second].push_back({ i, -1e9 });
            }
            i++;
        }
    }

    t.calcSts(i);
    t.centroid(0, -1);
}