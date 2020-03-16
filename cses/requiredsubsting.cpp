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

ll mod = 1e9 + 7;
ll n, m;
string s;
vector<ll> v;

ll transition (ll i, char c) {
    while (i > -1 && c != s[i]) i = v[i];
    i++;

    return i;
}

vector<vector<ll>> mat;

vector<vector<ll>> operator* (const vector<vector<ll>>& a, const vector<vector<ll>>& b) {
    vector<vector<ll>> res (a.size(), vector<ll>(a.size()));

    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a.size(); j++) {
            for (int k = 0; k < a.size(); k++) {
                res[i][j] += a[i][k] * b[k][j];
                res[i][j] %= mod;
            }
        }
    }
    return res;
}
vector<vector<ll>> modpow (ll e) {
    vector<vector<ll>> res (mat.size(), vector<ll>(mat.size()));

    for (int i = 0; i < res.size(); i++) res[i][i] = 1;

    while (e>0) {
        if (e % 2) res = res * mat;
        mat = mat * mat;
        e /= 2;
    }

    return res;
}

int main () {
    cin >> n >> s;
    m = s.size();

    v = prefix(s);
    
    mat.resize(m+1, vector<ll>(m+1));

    for (int i = 0; i < m; i++) {
        for (char c = 'A'; c <= 'Z'; c++) {
            mat[i][transition(i, c)]++;
        }
    }
    mat[m][m] = 26;
    
    mat = modpow(n);
    
    cout << mat[0][m];

    return 0;
}