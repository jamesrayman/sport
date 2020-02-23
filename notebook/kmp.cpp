#include <bits/stdc++.h>
using namespace std;

using ll = long long;

vector<ll> kmp (const string& s, const string& t) {
    ll j = -1;
    vector<ll> b (t.size()+1);
    b[0] = -1;

    for (ll i = 0; i < t.size(); i++) {
        while (j > -1 && t[i] != t[j]) j = b[j];
        j++;
        b[i+1] = j;
    }

    j = 0;
    vector<ll> v;
    for (ll i = 0; i < s.size(); i++) {
        while (j > -1 && s[i] != t[j]) j = b[j];
        j++;
        if (j == t.size()) {
            v.push_back(i - j);
            j = b[j];
        }
    }
    return v;
}
