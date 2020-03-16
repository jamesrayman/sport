#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll mod = 1e9+7;

string s;
ll n;
vector<ll> v;

struct Trie {
    vector<Trie> next;
    ll x = 0;

    void add (const string& k, ll i) {
        if (i == k.size()) {
            x++;
            return;
        }
        if (next.empty()) next.resize(26);

        next[k[i]-'a'].add(k, i+1);
    }

    void calc (ll i, ll j) {
        v[i] += x * v[j];
        v[i] %= mod;

        if (!next.empty() && j < n) {
            next[s[j]-'a'].calc(i, j+1);
        }
    }
};

int main () {
    ll k;
    cin >> s >> k;
    n = s.size();

    Trie t;
    while (k-->0) {
        string ss;
        cin >> ss;

        t.add(ss, 0);
    }

    v.resize(n+1);
    v[n] = 1;

    for (int i = n-1; i > -1; i--) {
        t.calc(i, i);
    }

    cout << v.front();
}