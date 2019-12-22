#include <bits/stdc++.h>
using namespace std;

long long n, t, x, y, i, mod = 1e9+7, d = 5e8+4;
 
int main () {
    cin >> n;
 
    for (i = 1; n/i > n/(i+1); i++) {
        x = n/i;
        y = n/(i+1)+1;
 
        t += (x-y+1) % mod * ((x*(n/x) + y*(n/y)) % mod) % mod * d % mod;
        t %= mod;
    }
 
    for (i = 1; i < y; i++) {
        t += i*(n/i);
        t %= mod;
    }
 
    cout << t;
}