#include <bits/stdc++.h>
using namespace std;

struct UnionFind {
    struct Element {
        int id;
        int p;
        int rank;

        Element (int i) {
            id = p = i;
        }
    };
    vector<Element> v;

    // make x the parent of y
    void combine (Element& x, Element& y) {
        y.p = x.id;
    }

    void makeSets (int n) {
        for (int i = 0; i < n; i++)
            v.push_back(Element(i));
    }
    int find (int x) {
        if (v[x].p != x) {
            v[x].p = find(v[x].p);
        }
        return v[x].p;
    }
    Element& at (int x) {
        return v[find(x)];
    }
    void join (int x, int y) {
        x = find(x);
        y = find(y);
 
        if (x == y)
            return;
 
        if (v[x].rank < v[y].rank)
            swap(x, y);
        if (v[x].rank == v[y].rank)
            v[x].rank++;
        
        combine(v[x], v[y]);
    }
    bool joined (int x, int y) {
        return find(x) == find(y);
    }
};
