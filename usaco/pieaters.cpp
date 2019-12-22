#include <bits/stdc++.h>
using namespace std;

long long n, m;

struct Cow {
    int a, b, w;
};
vector<Cow> v;

unordered_map<long long, unordered_map<long long, long long>> d;
vector<vector<vector<long long>>> w;

long long f (int i, int j) {
    if (i > j) return 0;
    if (d[i].count(j)) return d[i][j];

    long long r = 0;

    for (int k = i; k <= j; k++) {
        r = max(r, w[i][k][j] + f(i, k-1) + f(k+1, j));
        //if (j - i == n-1) cout << k << " " << r << " " << w[i][k][j] << "\n";
    }


    return d[i][j] = r;
}

int main() {
    ifstream input ("pieaters.in");
    ofstream output ("pieaters.out");

    input >> n >> m;

    while (m-->0) {
        int a, b, w;
        input >> w >> a >> b;
        a--;
        b--;

        v.push_back({ a, b, w });
    }

    w.resize(n, vector<vector<long long>>(n, vector<long long>(n, 0)));
    
    for (auto& cow : v) {
        for (int k = cow.a; k <= cow.b; k++) {
            w[cow.a][k][cow.b] = max(w[cow.a][k][cow.b], (long long)cow.w);
        }
    }

    for (int len = 0; len < n; len++) {
        for (int i = 0; i + len < n; i++) {
            int j = i + len;

            for (int k = i; k <= j; k++) {
                if (i < k) w[i][k][j] = max(w[i][k][j], w[i+1][k][j]);
                if (k < j) w[i][k][j] = max(w[i][k][j], w[i][k][j-1]);
            }
        }
    }


    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            f(i, j);
        }
    }

    output << f(0, n-1) << "\n";

    return 0;
}
