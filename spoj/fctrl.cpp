#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main () {
    ll t, n;
    cin >> t;

    while (t-->0) {
        cin >> n;
        ll r = 0, x = 5;

        while (x <= n) {
            r += n / x;
            x *= 5;
        }

        cout << r << "\n";
    }
}