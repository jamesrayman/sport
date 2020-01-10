#include <bits/stdc++.h>
using namespace std;

struct Node {
    int p = -1;
    int h = -1;
    multiset<int> d { 0, 0 };
    int best = 0;
    vector<int> adj;
};
vector<Node> graph;
vector<int> bfs;

void treeify () {
    queue<int> q;
    q.push(0);
    q.push(-1);
    q.push(0);
    
    int i, p, h;

    while (!q.empty()) {
        i = q.front(); q.pop();
        p = q.front(); q.pop();
        h = q.front(); q.pop();

        graph[i].p = p;
        graph[i].h = h;
        bfs.push_back(i);

        if (p != -1) graph[i].adj.erase(find(graph[i].adj.begin(), graph[i].adj.end(), p));

        for (auto j : graph[i].adj) {
            q.push(j);
            q.push(i);
            q.push(h+1);
        }
    }
    
    reverse(bfs.begin(), bfs.end());
}

void compute (int i) {
    auto& node = graph[i];
    for (auto j : node.adj) {
        node.d.insert(1 + *graph[j].d.rbegin());
        node.best = max(node.best, graph[j].best);
    }
    node.best = max(node.best, *node.d.rbegin() + *++node.d.rbegin());
}

int main () {
    int n;
    cin >> n;

    graph.resize(n);

    for (int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;

        graph[b].adj.push_back(a);
        graph[a].adj.push_back(b);
    }

    treeify();


    for (auto i : bfs) {
        compute(i);
    }

    cout << graph[0].best << "\n";
}