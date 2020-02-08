#include <bits/stdc++.h>
using namespace std;

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