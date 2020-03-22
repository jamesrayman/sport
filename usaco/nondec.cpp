#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll mod = 1e9+7;
const ll N = 5e4+1, K = 20;
using Matrix = ll [K][K];

void initio (string file = "") {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    if (file != "") {
        freopen((file + ".in").c_str(), "r", stdin);
        freopen((file + ".out").c_str(), "w", stdout);
    }
}

void mul (Matrix res, Matrix lhs, Matrix rhs) {
    for (int i = 0; i < K; i++) {
        for (int j = i; j < K; j++) {
            for (int k = i; k <= j; k++) {
                res[i][j] += lhs[i][k] * rhs[k][j];
                res[i][j] %= mod;
            }
            res[i][j] += lhs[i][j] + rhs[i][j];
            res[i][j] %= mod;
        }
    }
}

void singleton (int x, Matrix res) {
    for (int i = x; i < K; i++) {
        res[x][i] = 1;
    }
    for (int i = 0; i < K; i++) {
        res[i][i]++;
    }
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < K; j++) {
            cerr << res[i][j] << " ";
        }
        cerr << "\n";
    }
    cerr << "\n";
}

Matrix v [N];

struct Fenwick {
    int n, k;

    Fenwick (int n, int k) {
        this->n = n;
        this->k = k;
    }

    void update (int i, Matrix m) {
        while (i < N) {
            Matrix r = {}; 

            mul(r, v[i], m);

            for (int a = 0; a < K; a++) {
                for (int b = i; b < K; b++) {
                    v[i][a][b] = r[a][b];
                }
            }
            i += i&-i;
        }
    }

    void query (int i, Matrix res) {
        while (i > 0) {
            Matrix r = {};

            mul(r, res, v[i]);

            for (int a = 0; a < K; a++) {
                for (int b = i; b < K; b++) {
                    res[a][b] = r[a][b];
                }
            }
            i -= i&-i;
        }
    }
};

int main() {
    initio("nondec");
    ll n, k, q;

    cin >> n >> k;

    vector<vector<pair<ll, ll>>> qs (n);
    vector<int> v (n);

    for (auto& x : v) cin >> x;

    cin >> q;
    vector<ll> ans (q);

    Fenwick f (n+10, k);

    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;

        qs[b-1].push_back({ a-1, i });
    }

    for (int i = 0; i < n; i++) {
        Matrix sn = {};

        singleton(v[i]-1, sn);
        f.update(n-i, sn);

        for (auto& p : qs[i]) {
            Matrix res = {};

            f.query(n-p.first, res);
            ll s = 1;

            for (int j = 0; j < k; j++) {
                s += res[j][k-1];
            }

            ans[p.second] = s % mod;
        }
    }

    for (auto& x : ans)
        cout << x << "\n";

    return 0;
}

