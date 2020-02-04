#include <bits/stdc++.h>
using namespace std;

using ll = long long;
string s;
ll n;

struct SegTree {
    vector<ll> hi, lo;
    vector<ll> openl, openr, openlr, closed;

    void build () {
        hi.resize(4*n);
        lo.resize(4*n);
        openl.resize(4*n);
        openr.resize(4*n);
        openlr.resize(4*n);
        closed.resize(4*n);
        build(1, 0, n-1);
    }

    void build (int p, int i, int j) {
        lo[p] = i;
        hi[p] = j;

        if (i == j) {
            return;
        }
        int mid = (i+j)/2;

        build(2*p, i, mid);
        build(2*p+1, mid+1, j);
    }
    void update (int p, int i, int x) {
        if (lo[p] == i && hi[p] == i) {
            openl[p] = openr[p] = openlr[p] = closed[p] = x;
            return;
        }
        if (lo[p] > i || hi[p] < i) {
            return;
        }

        update(2*p, i, x);
        update(2*p+1, i, x);

        openl[p] = openl[2*p];
        openr[p] = openr[2*p+1];
        openlr[p] = 0;
        closed[p] = max(openr[2*p] + openl[2*p+1], max(closed[2*p], closed[2*p+1]));

        if (openlr[2*p] > 0) {
            if (openlr[2*p+1] > 0) {
                openlr[p] = openlr[2*p] + openlr[2*p+1];
            }
            openl[p] = openlr[2*p] + openl[2*p+1];
        }
        if (openlr[2*p+1] > 0) {
            openr[p] = openr[2*p] + openlr[2*p+1]; 
        }
    }
};

int main () {
    ll q;
    cin >> s >> q;

    n = s.size();

    SegTree zeros, ones;

    zeros.build();
    ones.build();

    for (int i = 0; i < n; i++) {
        zeros.update(1, i, s[i] == '0');
        ones.update(1, i, s[i] == '1');
    }
    while (q-->0) {
        int a;
        cin >> a;
        a--;

        s[a]--;
        if (s[a] < '0') s[a] += 2;

        zeros.update(1, a, s[a] == '0');
        ones.update(1, a, s[a] == '1');

        cout << max(ones.closed[1], zeros.closed[1]) << " ";
    }
}
