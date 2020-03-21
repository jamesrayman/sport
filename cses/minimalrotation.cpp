#include <bits/stdc++.h>
using namespace std;

int n;
string s;
list<int> candidates;
 
char get (int i) {
    return s[i % n];
}
void sweep (int d) {
    char first = '~';
 
    for (auto i : candidates) {
        first = min(first, get(i + d));
    }
 
    int prev = -(1 << 27);
    candidates.remove_if([&](int i){
        if (first != get(i+d))
            return true;
 
        if (prev + d >= i) return true;
        prev = i;
        return false;
    });
 
 
}
 
int main() {
    cin >> s;
    n = s.size();
 
    for (int i = 0; i < n; i++) {
        candidates.push_back(i);
    }
 
    for (int i = 0; i < n && candidates.size() > 1; i++) {
        sweep(i);
    }
 
    int i = candidates.front();
 
    cout << s.substr(i) << s.substr(0, i) << "\n";
 
    return 0;
}