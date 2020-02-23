#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main () {
    string t;
    cin >> t;

    ll j = -1;
    vector<ll> b (t.size()+1);
    b[0] = -1;

    for (ll i = 0; i < t.size(); i++) {
        while (j > -1 && t[i] != t[j]) j = b[j];
        j++;
        b[i+1] = j;
    }
    
}