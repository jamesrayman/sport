#include <bits/stdc++.h>
using namespace std;

int inf = 1e9+9;

struct Tree {
    int n;
    vector<int> parent;
    vector<int> a, vi, ui;
    vector<vector<int>> adj;
    vector<char> blocked;
    vector<int> sts;
    vector<vector<int>> v, u; // v is asc, u is desc

    int best = 0;

    Tree (int n) {
        this->n = n;
        parent.resize(n);
        adj.resize(n);
        a.resize(n);
        sts.resize(n);
        vi.resize(n);
        ui.resize(n);
        v.resize(n);
        u.resize(n);
        blocked.resize(n, false);
    }

    void join (int i, int j) { // merge j into i
        if (v[vi[i]].size() > v[vi[j]].size()) {
            for (int k = 0; k < v[vi[j]].size(); k++) {
                v[vi[i]][k] = min(v[vi[i]][k], v[vi[j]][k]);
            }
        }
        else {
            for (int k = 0; k < v[vi[i]].size(); k++) {
                v[vi[j]][k] = min(v[vi[i]][k], v[vi[j]][k]);
            }
            vi[i] = vi[j];
        }

        if (u[ui[i]].size() > u[ui[j]].size()) {
            for (int k = 0; k < u[ui[j]].size(); k++) {
                u[ui[i]][k] = max(u[ui[i]][k], u[ui[j]][k]);
            }
        }
        else {
            for (int k = 0; k < u[ui[i]].size(); k++) {
                u[ui[j]][k] = max(u[ui[i]][k], u[ui[j]][k]);
            }
            ui[i] = ui[j];
        }
    }

    void down (int i, int p) {
        vi[i] = ui[i] = i;
        v[i] = { 0 };
        u[i] = { inf };

        for (auto& next : adj[i]) {
            if (next == p || blocked[next]) continue;

            down(next, i);
            join(i, next);
        }

        auto it = lower_bound(v[vi[i]].begin(), v[vi[i]].end(), a[i]);
        if (it == v[vi[i]].end()) v[vi[i]].push_back(a[i]);
        else *it = a[i];

        it = lower_bound(u[ui[i]].begin(), u[ui[i]].end(), a[i], greater<int>());
        if (it == u[ui[i]].end()) u[ui[i]].push_back(a[i]);
        else *it = a[i];
    }

    void solve (int root) {
        vi[root] = ui[root] = root;
        v[root] = { 0 };
        u[root] = { inf };

        for (auto& next : adj[root]) {
            if (blocked[next]) continue;

            down(next, root);

            auto it = lower_bound(v[vi[root]].begin(), v[vi[root]].end(), a[root]);
            if (it == v[vi[root]].end()) v[vi[root]].push_back(a[root]);
            else *it = a[root];

            it = lower_bound(u[ui[root]].begin(), u[ui[root]].end(), a[root], greater<int>());
            if (it == u[ui[root]].end()) u[ui[root]].push_back(a[root]);
            else *it = a[root];

            for (int k = 0; k < v[vi[next]].size(); k++) {
                best = max(best, k + max(0, -1 + (int)distance(u[ui[root]].begin(), lower_bound(u[ui[root]].begin(), u[ui[root]].end(), v[vi[next]][k], greater<int>()) )));
            }

            for (int k = 0; k < u[ui[next]].size(); k++) {
                best = max(best, k + max(0, -1 + (int)distance(v[vi[root]].begin(), lower_bound(v[vi[root]].begin(), v[vi[root]].end(), u[ui[next]][k]) )));
            }

            join(root, next);
        }


    }

    void calcSts (int i, int p) {
        parent[i] = p;

        sts[i] = 1;

        for (auto& next : adj[i]) {
            if (next == p || blocked[next]) continue;
            calcSts(next, i);
            sts[i] += sts[next];
        }
    }

    void solveAll (int i) {
        calcSts(i, -1);

        int centroid = i, bestSize = n;

        queue<int> q;
        q.push(i);

        while (!q.empty()) {
            int cur = q.front();
            q.pop();

            int size = sts[i] - sts[cur];

            for (auto& next : adj[cur]) {
                if (next == parent[cur] || blocked[next]) continue;
                size = max(size, sts[next]);
                q.push(next);
            }

            if (bestSize > size) {
                centroid = cur;
                bestSize = size;
            }
        }

        solve(centroid);
        blocked[centroid] = true;

        for (auto& next : adj[centroid]) {
            if (blocked[next]) continue;

            solveAll(next);
        }
    }
};


int main () {
    int times;
    cin >> times;

    while (times-->0) {
        int n;
        cin >> n;

        Tree tree (n);

        for (int i = 0; i < n; i++) {
            tree.a[i] = i+1;
        }

        for (int i = 0; i < n-1; i++) {
            int a, b;
            cin >> a >> b;
            a--;
            b--;

            tree.adj[a].push_back(b);
            tree.adj[b].push_back(a);
        }

        tree.solveAll(0);

        if (n == 1) cout << 1 << "\n";
        else cout << tree.best << "\n";
    }
}
