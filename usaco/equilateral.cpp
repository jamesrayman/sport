#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void initio (string file = "") {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    if (file != "") {
        freopen((file + ".in").c_str(), "r", stdin);
        freopen((file + ".out").c_str(), "w", stdout);
    }
}

template<typename T, typename U>
ostream& operator << (ostream& out, pair<T, U> p) {
    return out << "(" << p.first << " " << p.second << ")";
}

template<typename T>
ostream& prints (ostream& out, T v) {
    out << "[";
    for (auto it = v.begin(); it != v.end(); ++it) {
        out << " " << *it;
    }
    out << " ]\n";

    return out;
}
#define PRINTS(C) template<typename T> ostream& operator << (ostream& out, C<T> v) { return prints(out, v); } 
#define PRINTS2(C) template<typename T, typename U> ostream& operator << (ostream& out, C<T, U> v) { return prints(out, v); } 
PRINTS(vector)
PRINTS(list)
PRINTS(deque)
PRINTS(set)
PRINTS(multiset)
PRINTS(unordered_set)
PRINTS(unordered_multiset)
PRINTS2(map)
PRINTS2(multimap)
PRINTS2(unordered_map)
PRINTS2(unordered_multimap)

void println () {
    cerr << "\n";
}
template<typename T, typename... Ts>
void println (T t, Ts... ts) {
    cerr << t << " ";
    println(ts...);
}

ll n, t = 0;
vector<string> v;

void solve () {
    vector<string> u (n);
    
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            u[i] += ".";
        }
        u[i] += v[i];

        for (int j = 0; j < i; j++) {
            u[i] += ".";
        }
    }
    ll m = u.front().size();

    vector<vector<ll>> s (m, vector<ll>(n+1, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            s[j][i+1] = s[j][i] + (u[i][j] == '*');
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (u[i][j] != '*') continue;

            for (int I = i+1; I < n; I++) {
                if (u[I][j] != '*') continue;

                ll x = 2*(I-i);
                if (j - x >= 0) t += s[j-x][min(n, I+x/2+1)] - s[j-x][I];
                if (j + x < m) t += s[j+x][i+1] - s[j+x][max(0LL, i-x/2)];
            }
        }
    }
}

int main () {
    initio("triangles");
    cin >> n;
    v.resize(n);

    for (auto& r : v) cin >> r;

    solve();
    for (auto& r : v) reverse(r.begin(), r.end());
    solve();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ('.' == v[i][j]) continue;
            for (int I = i+2; I < n; I+=2) {
                if ('.' == v[I][j]) continue;
                int sep = (I-i)/2; 

                if (0 <= j - sep) t -= v[i+sep][j-sep] != '.'; 
                if (j + sep < n) t -= v[i+sep][j+sep] != '.'; 
            }
            for (int J = j+2; J < n; J+=2) {
                if ('.' == v[i][J]) continue;
                int sep = (J-j)/2; 

                if (0 <= i - sep) t -= v[i-sep][j+sep] != '.'; 
                if (i + sep < n) t -= v[i+sep][j+sep] != '.'; 
            }
        }
    }

    cout << t << "\n";

    return 0;
}
