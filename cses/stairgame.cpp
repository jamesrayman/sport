#include <bits/stdc++.h>
using namespace std;

int main () {
    long long t, n, a;
    cin >> t;

    while (t-->0) {
        cin >> n;
        vector<long long> v (n);
        a = 0;

        for (int i = 0; i < n; i++) {
            cin >> v[i];
            if (i % 2 == 1) a ^= v[i];
        }

        if (a != 0) {
            cout << "first\n";
        }
        else {
            cout << "second\n";
        }
    }
}