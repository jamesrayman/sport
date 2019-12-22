#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;

    Point operator-(const Point& other) const {
        return { x-other.x, y-other.y };
    }
    bool operator<(const Point& other) const {
        if (x == other.x) return y > other.y;
        return x < other.x;
    }
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};
int n;
vector<Point> v;

vector<vector<int>> under;

long long cross (Point a, Point b) {
    return a.x * b.y - a.y * b.x;  
}

bool und (Point a, Point b, Point c) {
    return cross(b-a, c-a) < 0;
}

int f (Point a, Point b) {
    int r = 0;

    for (auto& c : v) {
        if (c == a || c == b) continue;
        if (c.x < a.x || b.x <= c.x) continue;
        
        if (und(a, b, c)) r++;
    }

    return r;
}

int main () {
    ifstream input ("triangles.in");
    ofstream output ("triangles.out");

    input >> n;
    v.resize(n);
    under.resize(n, vector<int>(n, 0));

    for (auto& p : v) {
        input >> p.x >> p.y;
        p.y += p.x * 2000000;
    }

    sort(v.begin(), v.end());

    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            under[i][j] = f(v[i], v[j]);
            //cout << "(" << v[i].x << ", " << v[i].y << ") (" << v[j].x << ", " << v[j].y << ") " << under[i][j] << "\n";
        }
    }
    vector<int> r (n-2);
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            for (int k = j+1; k < n; k++) {
                int u = 0;
                
                if (und(v[i], v[k], v[j])) {
                    u = under[i][k] - under[i][j] - under[j][k] - 1;
                }
                else {
                    u = under[i][j] + under[j][k] - under[i][k];
                }
                //cout << i << " " << j << " " << k << " " << u << "\n";

                r[u]++;
            }
        }
    }

    for (auto x : r) output << x << "\n";
}
