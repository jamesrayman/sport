#include <bits/stdc++.h>
using namespace std;

using ll = long long;

vector<ll> manacher (const string& s) {
    string t = "#";

    for (auto c : s) {
        t += c;
        t += "#";
    }
    ll n = t.size();
    vector<ll> v (t.size());

    ll hi = -1, c = 0, r;
 
    for (int i = 0; i < n; i++) {
        if (i <= hi) {
            r = min(v[2*c-i], hi-i);
        } else {
            r = 0;
        }
 
        while (i+r < n && i-r >= 0 && t[i-r] == t[i+r]) {
            r++;
        }
        v[i] = r;
 
        if (i + r - 1 > hi) {
            c = i;
            hi = i + r - 1;
        }
    }
    return v;
}

int main() {
    string s;
    cin >> s;
 
    auto v = manacher(s);
 
    ll r = -1, lo, hi;

    for (int i = 0; i < v.size(); i++) {
        if (v[i] > r) {
            r = v[i];
            lo = i - r;
            hi = i + r;
        }
    }

    for (int i = lo+1; i < hi; i++) {
        if (i % 2 != 0) cout << s[i/2];
    }
    cout << "\n";
}