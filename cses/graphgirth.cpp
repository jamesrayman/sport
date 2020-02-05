
#include <bits/stdc++.h>
using namespace std;

#define L int
#define v vector<
L n, m, a, b, B = '   ', i, d;
v v L>> A;

L f () {
    v L> e (n, B);
    queue<L> q;

    q.push(a);
    q.push(1);

    while (q.size()) {
        i = q.front();
        q.pop();
        d = q.front();
        q.pop();

        if (d < e[i]) { 
            e[i] = d;
            if (i == b) B = min(B, d);

            for (auto j : A[i])
                q.push(j),
                q.push(d+1);
        }
    }
}
L main () {
    cin >> n >> m;

    for (A.resize(n); m--; A[a].push_back(b))
        cin >> a >> b,
        
        A[--b].push_back(--a),
        f();

    cout << (B > n ? -1 : B);
}

