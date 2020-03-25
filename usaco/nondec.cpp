#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<int, int>;
ll mod = 1e9+7;

void initio (string file = "") {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    if (file != "") {
        freopen((file + ".in").c_str(), "r", stdin);
        freopen((file + ".out").c_str(), "w", stdout);
    }
}

struct Seg {
    ll n;
    int t [20];

    ll f (ll a, ll b) {
        int r = a + b;
        if (r >= mod) r -= mod;
        return r;
    }

   void build (ll k) {
        n = k;

        for (int i = 0; i < 20; i++) t[i] = 0;
    }

    ll query (ll i, ll j) {
        ll r = 0;
        for (; i <= j; i++) {
            r = f(r, t[i]);
        } 
        return r;
    }

    void update (ll i, ll x) {
        t[i] += x;
        if (t[i] >= mod) t[i] -= mod;
    }
};
template<typename T>
struct SegTree {
    ll n;
    vector<T> t;
    T noval = 0;

    T f (T a, T b) {
        return (a + b) % mod;
    }

    void combine (ll p) {
        t[p] = f(t[2*p], t[2*p+1]);
    }

    void build (const vector<T>& v, ll p, ll lo, ll hi) {
        if (lo == hi) {
            t[p] = v[lo];
            return;
        }
        
        ll mid = (lo + hi)/2;
        build(v, 2*p, lo, mid);
        build(v, 2*p+1, mid+1, hi);

        combine(p);
    }
    void build (ll k) {
        n = k;

        t.assign(4*n, noval);
    }

    T query (ll p, ll lo, ll hi, ll i, ll j) {
        if (hi < i || j < lo) return noval;
        if (i <= lo && hi <= j) return t[p];

        ll mid = (lo + hi)/2;
        return f(query(2*p, lo, mid, i, j),
                 query(2*p+1, mid+1, hi, i, j));
    }
    T query (ll i, ll j) {
        return query(1, 0, n-1, i, j);
    }

    void update (ll p, ll lo, ll hi, ll i, T x) {
        if (hi < i || i < lo) return;
        if (lo == hi) {
            t[p] += x;
            t[p] %= mod;
            return;
        }

        ll mid = (lo + hi)/2;
        update(2*p, lo, mid, i, x);
        update(2*p+1, mid+1, hi, i, x);
        combine(p);
    }

    void update (ll i, T x) {
        update(1, 0, n-1, i, x);
    }
};

ll n, k;
vector<int> v;
vector<ll> ans;

vector<pair<int, pll>> qs;

void solve (ll lo, ll hi, const vector<int>& is) {
    if (is.size() == 0) return;
    if (lo == hi) {
        for (auto& ii : is) {
            ans[qs[ii].first] = 2;
        }
        return;
    }
    ll mid = (lo+hi) / 2;
    vector<int> loq, hiq;
    // cerr << "[ " << lo << ", " << mid << ", " << hi << " ]" << qs.size() << "\n";

    for (auto& ii : is) {
        auto& q = qs[ii];
        if (q.second.second <= mid) {
            loq.push_back(ii);
            continue;
        }
        if (q.second.first > mid) {
            hiq.push_back(ii);
            continue;
        }
    }

    solve(lo, mid, loq);
    solve(mid+1, hi, hiq);

    if (loq.size() + hiq.size() == is.size()) return;

    vector<vector<ll>> la (k, vector<ll>(hi-lo+1, 0)), ha = la;

    Seg t;

    for (int j = 0; j < k; j++) {
        t.build(k);
        for (int i = mid; i >= lo; i--) {
            t.update(v[i], (j >= v[i]) + t.query(v[i], k-1));
            la[j][i-lo] = 1+t.query(0, k-1);
        }
    }

    for (int j = 0; j < k; j++) {
        t.build(k);
        for (int i = mid+1; i <= hi; i++) {
            t.update(v[i], (j == v[i]) + t.query(0, v[i]));
            ha[j][i-lo] = t.query(0, k-1);
        }
    }

    for (auto& ii : is) {
        auto& q = qs[ii];
        if (q.second.second <= mid) {
            continue;
        }
        if (q.second.first > mid) {
            continue;
        }
        // cerr << q.second.first << " " << q.second.second << "\n";

        auto& ansi = ans[q.first];

        for (int i = 0; i < k; i++) {
            ansi += la[i][q.second.first-lo] * ha[i][q.second.second-lo];
            // cerr << la[i][q.second.first-lo] << " " << ha[i][q.second.second-lo] << " " << la[k-1][q.second.first-lo] << "\n";
            ansi %= mod;
        }
        ansi += la[k-1][q.second.first-lo];
        ansi %= mod;
        // cerr << ans[q.first] << " " << q.first << "\n";
    }
}

int main() {
    initio("nondec");
    ll q;

    cin >> n >> k;
    v.resize(n);

    for (auto& x : v) {
        cin >> x;
        x--;
    }

    cin >> q;
    ans.resize(q);
    vector<int> is;

    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;

        qs.push_back({ i, { a-1, b-1 } });
        is.push_back(i);
    }

    solve(0, n-1, is);

    for (auto& x : ans)
        cout << x << "\n";

    return 0;
}

