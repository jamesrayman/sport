#include <bits/stdc++.h>
#define I long long
#define M [100][100]
using namespace std;
 
I m = 1e9+7, n, i, j, k, a, b, c;
 
inline I x (I a M, I b M) {
	I r M;
 
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			r[i][j] = 0;
 
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			for (k = 0; k < n; k++) {
				r[i][j] += a[i][k] * b[k][j];
				if (r[i][j] > m) r[i][j] %= m;
			}
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			a[i][j] = r[i][j];
}
 
I f (I b M, I e) {
	I r M;
 
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			r[i][j] = 0;
 
	for (i = 0; i < n; i++)
		r[i][i] = 1;
 
	while (e) {
		if (e % 2) x(r, b);
		x(b, b);
		e /= 2;
	}
 
	return r[0][n-1] % m;
}
 
int main () {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	cin >> n >> c >> k;
	I r M;
 
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			r[i][j] = 0;
 
	while (c--) {
		cin >> a >> b;
		r[a-1][b-1]++;
	}
	cout << f(r, k);
}