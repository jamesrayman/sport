#import <iostream>

long m = 1e9+7, k = 1, v ['  '], c, u;

main () {
    for (; u = v[c = getchar()], c > 32; k = (2*k - u + m) % m)
        v[c] = k;

    std::cout << (k-1+m)%m;
}
