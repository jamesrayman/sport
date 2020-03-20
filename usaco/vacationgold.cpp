#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;
using ld = long double;

void initio (string file = "") {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    if (file != "") {
        freopen((file + ".in").c_str(), "r", stdin);
        freopen((file + ".out").c_str(), "w", stdout);
    }
}

template<typename T, typename U>
ostream& operator << (ostream& out, const pair<T, U>& p) {
    return out << "(" << p.first << " " << p.second << ")";
}

template<typename T>
ostream& prints (ostream& out, const T& v) {
    out << "[";
    for (auto it = v.begin(); it != v.end(); ++it) {
        out << " " << *it;
    }
    out << " ]\n";

    return out;
}
#define PRINTS(C) template<typename T> ostream& operator << (ostream& out, const C<T>& v) { return prints(out, v); } 
#define PRINTS2(C) template<typename T, typename U> ostream& operator << (ostream& out, const C<T, U>& v) { return prints(out, v); } 
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
void println (const T& t, Ts... ts) {
    cerr << t << " ";
    println(ts...);
}

ll n, m, k, q;
vector<ll> hubs;
vector<vector<pll>> adj2, adj;
vector<vector<ll>> dto, dfrom;

vector<ll> dijk (ll source) {
    set<pll> q;
    vector<ll> d (n, 1e18);

    q.insert({ 0, source });
    d[source] = 0;

    while (q.size()) {
        ll i = q.begin()->second;
        q.erase(q.begin());

        for (auto& p : adj[i]) {
            auto j = p.first, w = p.second;

            if (d[i] + w < d[j]) {
                q.erase({ d[j], j });
                d[j] = d[i] + w;
                q.insert({ d[j], j });
            }
        }
    }

    return d;
}

int main () {
    initio("vacationgold");

    cin >> n >> m >> k >> q;
    
    adj.resize(n);
    adj2.resize(n);
    hubs.resize(k);

    while (m-->0) {
        ll a, b, w;
        cin >> a >> b >> w;
        a--;
        b--;

        adj[a].push_back({ b, w });
        adj2[b].push_back({ a, w });
    }
    for (auto& h : hubs) {
        cin >> h;
        h--;

        dto.push_back(dijk(h));
    }
    swap(adj, adj2);

    for (auto& h : hubs) {
        dfrom.push_back(dijk(h));
    }

    ll take = 0, dist = 0;
    while (q-->0) {
        ll a, b;
        cin >> a >> b;
        a--;
        b--;

        ll best = 1e18;

        for (int i = 0; i < k; i++) {
            best = min(best, dfrom[i][a] + dto[i][b]);
        }

        if (best < 1e18) {
            take++;
            dist += best;
        }
    }
    cout << take << "\n" << dist << "\n";

    return 0;
}
