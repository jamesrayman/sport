#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll n, m;
vector<string> v;

int main () {
    cin >> n >> m;
    v.resize(n);

    for (auto& x : v) cin >> x;

    ll i, j;
    queue<ll> q;

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            if (v[i][j] == 'A') {
                q.push(i);
                q.push(j);
                q.push('a');
            }
        }
    }

    while (!q.empty()) {
        i = q.front();
        q.pop();
        j = q.front();
        q.pop();
        char c = q.front();
        q.pop();

        if (i < 0 || i >= n || j < 0 || j >= m || (v[i][j] != '.' && v[i][j] != 'A' && v[i][j] != 'B')) continue;
        
        if (v[i][j] == 'B') {
            string s;
            
            while (v[i][j] != 'a') {
                s += c;
                if (c == 'L') j++;
                if (c == 'R') j--;
                if (c == 'U') i++;
                if (c == 'D') i--;

                c = v[i][j];
            }

            reverse(s.begin(), s.end());
            cout << "YES " << s.size() << " " << s;
            return 0;
        }
        v[i][j] = c;

        q.push(i+1);
        q.push(j);
        q.push('D');
        q.push(i-1);
        q.push(j);
        q.push('U');
        q.push(i);
        q.push(j-1);
        q.push('L');
        q.push(i);
        q.push(j+1);
        q.push('R');
    }
    cout << "NO";

    return 0;
}
