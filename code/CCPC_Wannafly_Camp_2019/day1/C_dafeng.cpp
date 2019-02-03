// 本题甚水
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}
int a[] = {2, 3, 4, 5, 6, 7, 9, 11, 13, 17, 19, 23, 29, 31, 37};

void solve(ll A, ll B) {
    if (gcd(A, B) == 1) {
        printf("1\n%lld %lld\n", A, B);
        return;
    }
    puts("2");
    for (auto x: a)
    for (auto y: a) {
        ll A1 = x, A2 = A - x;
        ll B2 = y, B1 = B - y;
        if (A2 >= 2 && B1 >= 2 && gcd(A1, B1) == 1 && gcd(A2, B2) == 1) {
            printf("%lld %lld\n%lld %lld\n", A1, B1, A2, B2);
            return;
        }
        swap(B1, B2);
        if (A2 >= 2 && B1 >= 2 && gcd(A1, B1) == 1 && gcd(A2, B2) == 1) {
            printf("%lld %lld\n%lld %lld\n", A1, B1, A2, B2);
            return;
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        ll A, B;
        scanf("%lld%lld", &A, &B);
        solve(A, B);
    }
}
