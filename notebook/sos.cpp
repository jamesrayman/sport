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
