#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct UnionFind {
    struct Element {
        ll id;
        ll p;
        ll rank;

        Element (ll i) {
            id = p = i;
        }
    };
    vector<Element> v;

    // make x the parent of y
    void combine (Element& x, Element& y) {
        y.p = x.id;
    }

    void makeSets (ll n) {
        for (ll i = 0; i < n; i++)
            v.push_back(Element(i));
    }
    ll find (ll x) {
        if (v[x].p != x) {
            v[x].p = find(v[x].p);
        }
        return v[x].p;
    }
    Element& at (ll x) {
        return v[find(x)];
    }
    void join (ll x, ll y) {
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
    bool joined (ll x, ll y) {
        return find(x) == find(y);
    }
};
