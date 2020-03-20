#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Segment {
    ll i = 0, j = -1;
    vector<ll> f = vector<ll>(26, 0);
    bool asc = true;

    bool operator< (const Segment& other) const {
        return i < other.i;
    }

    void pourTo (Segment& other, int a, ll& x) {
        if (x > f[a]) {
            other.f[a] += f[a];
            x -= f[a];
            f[a] = 0;
        }
        else {
            other.f[a] += x;
            f[a] -= x;
            x = 0;
        }
    }

    Segment add (Segment& other) {
        Segment s;

        if (i <= other.i && other.j <= j) {
            other.i = other.j+1;

            for (int i = 0; i < 26; i++) {
                f[i] += other.f[i];
            }
            return s;
        }
        if (other.i <= i && j <= other.j) {
            s.i = other.i;
            s.j = i - 1;
            s.asc = other.asc;

            ll x = i - other.i;

            if (other.asc) {
                for (int a = 0; x > 0; a++) {
                    other.pourTo(s, a, x);
                }
                x = j - i + 1;
                for (int a = 0; x > 0; a++) {
                    other.pourTo(*this, a, x);
                }
            }
            else {
                for (int a = 25; x > 0; a--) {
                    other.pourTo(s, a, x);
                }
                x = j - i + 1;
                for (int a = 25; x > 0; a--) {
                    other.pourTo(*this, a, x);
                }
            }
            other.i = j+1;

            return s;
        }
        else {
            if (i < other.i) {
                ll x = j - other.i + 1;

                if (other.asc) {
                    for (int a = 0; x > 0; a++) {
                        other.pourTo(*this, a, x);
                    }
                }
                else {
                    for (int a = 25; x > 0; a--) {
                        other.pourTo(*this, a, x);
                    }
                }
                other.i = j+1;
            }
            else {
                ll x = other.j - i + 1;

                if (other.asc) {
                    for (int a = 25; x > 0; a--) {
                        other.pourTo(*this, a, x);
                    }
                }
                else {
                    for (int a = 0; x > 0; a++) {
                        other.pourTo(*this, a, x);
                    }
                }
                other.j = i-1;
            }

            return s;
        }
    }
};

ll n;
set<Segment> s;

int main () {
    ll q;
    string t;
    cin >> n >> q >> t;

    for (int i = 0; i < n; i++) {
        Segment seg;
        seg.i = seg.j = i;
        seg.f[t[i] - 'a']++;

        s.insert(seg);
    }

    while (q-->0) {
        ll i, j, k;
        cin >> i >> j >> k;
        i--;
        j--;

        Segment seg;
        seg.i = i;
        seg.j = j;
        seg.asc = k;

        vector<Segment> ss;

        ll runs = 0;
        while (true) {
            // for (auto tt : s) {
            //     cerr << tt.i << " " << tt.j << " : ";
            // }
            // cerr << "\n";
            auto it = s.lower_bound(seg);
            if (runs > 0 && (it == s.end() || it->i > j)) break;

            if (it != s.begin()) {
                it--;
                if (it->j < i) it++;
            } 

            if (it == s.end()) break;

            Segment r = *it; 
            s.erase(it);

            Segment rr = seg.add(r);
            if (r.i <= r.j) ss.push_back(r);
            if (rr.i <= rr.j) ss.push_back(rr);

            runs++;
        }
        for (auto& sss : ss) s.insert(sss);

        s.insert(seg);

        // cerr << "> ";
        // for (auto tt : s) {
        //     cerr << tt.i << " " << tt.j << " : ";
        // }
        // cerr << "\n";

        // cerr << "[" << i << " " << j << "]\n";
    }

    for (auto seg : s) {
        t = "";
        for (char c = 'a'; c <= 'z'; c++) {
            while (seg.f[c-'a']-->0) t += c;
        }
        if (!seg.asc) reverse(t.begin(), t.end());

        cout << t;
    }
    cout << "\n";

    return 0;
}