#include <bits/stdc++.h>
using namespace std;

void sos (vector<int>& v, int k) {
    for (int i = 0; i < k; i++) {
        for (int mask = 0; mask < (1 << k); mask++) {
            if (mask & (1 << i)) {
                v[mask] += v[mask - (1 << i)];
            }
        }
    }
}

int k = 20, n = 1 << k, t;
vector<int> v (n), u (n), a;
 
int inv (int x) {
    return ~x & (n-1);
}

int main () {
    cin >> t;
    vector<int> a(t);

    for (auto& x : a) {
        cin >> x;
        v[x]++;
        u[inv(x)]++;
    }

    sos(v, k);
    sos(u, k);

    for (auto& x : a) {
        cout << v[x] << " " << u[inv(x)] << " " << t-v[inv(x)] << "\n";
    }
}
