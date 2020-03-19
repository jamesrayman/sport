#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main () {
    ll n, m, q;
    cin >> n >> m >> q;

    vector<vector<ll>> dist (n, vector<ll>(n, 1e12));
    for (int i = 0; i < n; i++) dist[i][i] = 0;

    while (m-->0) {
        ll a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;

        dist[a][b] = dist[b][a] = min(dist[a][b], c);
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dist[i][j] = min(dist[i][k] + dist[k][j], dist[i][j]);
            }
        }
    }

    while (q-->0) {
        ll a, b;
        cin >> a >> b;
        a--;
        b--;

        cout << (dist[a][b] == 1e12 ? -1 : dist[a][b]) << " ";
    }

    return 0;
}
