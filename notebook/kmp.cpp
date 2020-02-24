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

vector<ll> kmp (const string& s, const string& t) {
    vector<ll> v, p = prefix(t);

    ll j = 0;
    for (ll i = 0; i < s.size(); i++) {
        while (j > -1 && s[i] != t[j]) j = p[j];
        j++;
        if (j == t.size()) {
            v.push_back(i - j);
            j = p[j];
        }
    }
    return v;
}
