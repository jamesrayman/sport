#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    vector<pair<int, int>> t;
    int n;

    void build (vector<pair<int, int>>& v) {
        n = v.size();
        t.resize(2*n, { 1<<27, -1 });

        for (int i = 0; i < n; i++)
            t[n+i] = v[i];

        for (int i = n-1; i > 0; i--)
            t[i] = min(t[2*i], t[2*i+1]);
    }
    pair<int, int> query(int i, int j) {
        if (i > j) swap(i, j);
        j++;

        pair<int, int> res = { 1<<27, -1 };
        for (i += n, j += n; i < j; i /= 2, j /= 2) {
            if (i % 2) res = min(res, t[i++]);
            if (j % 2) res = min(res, t[--j]);
        }
        return res;
    }
};
int n;

struct Node {
    int id, p = -1, h = -1, x = 0;
    vector<int> adj;
};
vector<Node> tree;
vector<pair<int, int>> v;
vector<int> pos;

void treeify (int i, int p, int h) {
    auto& node = tree[i];
    node.p = p;
    node.h = h;

    pos[i] = v.size();
    v.push_back({ h, i });

    for (auto& next : node.adj) {
        if (next != p) {
            treeify(next, i, h+1);
            v.push_back({ h, i });
        }
    }
}
int r = 0;

void calc (int i) {
    for (auto& next : tree[i].adj) {
        if (next != tree[i].p) {
            calc(next);
            tree[i].x += tree[next].x;
        }
    }
    r = max(r, tree[i].x);
}

int main () {
    ifstream input ("maxflow.in");
    ofstream output ("maxflow.out");

    int k;
    input >> n >> k;

    tree.resize(n);
    pos.resize(n);

    for (int i = 0; i < n; i++) {
        tree[i].id = i;
    }

    for (int i = 0; i < n-1; i++) {
        int a, b;
        input >> a >> b;
        a--;
        b--;

        tree[a].adj.push_back(b);
        tree[b].adj.push_back(a);
    }

    treeify(0, -1, 0);
    
    SegTree t;
    t.build(v);

    while (k-->0) {
        int a, b;
        input >> a >> b;
        a--;
        b--;

        tree[a].x++;
        tree[b].x++;

        int lca = t.query(pos[a], pos[b]).second;
        tree[lca].x--;
        if (tree[lca].p != -1) tree[tree[lca].p].x--;
    }

    calc(0);

    output << r << "\n";
}
