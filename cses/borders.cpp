#include <bits/stdc++.h>
using namespace std;

using ll = long long;

vector<ll> prefix (const string& s) {
    ll j = -1;
    vector<ll> p (s.size()+1);
    p[0] = -1;

    for (ll i = 0; i < s.size(); i++) {
        while (j > -1 && s[i] != s[j]) j = p[j];
        j++;
        p[i+1] = j;
    }

    return p;
}

int main () {
    string t;
    cin >> t;

    auto p = prefix(t);

    ll j = p.back();
    set<ll> v;

    while (j > 0) {
        v.insert(j);
        j = p[j];
    }
    for (auto x : v) cout << x << " ";
}