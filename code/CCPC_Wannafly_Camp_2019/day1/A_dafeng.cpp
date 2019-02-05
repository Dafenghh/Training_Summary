#include <bits/stdc++.h>
using namespace std;
void Maxi(int &a, int b) {
    if (a < b) a = b;
}
void Mini(int &a, int b) {
    if (b < a) a = b;
}
int main() {
    int n,r,m,k,s;
    scanf("%d%d%d%d%d", &n, &r, &m, &k, &s);
    int Min[2] = {s, n}, Max[2] = {s, 1};
    bool hasB = false;
    for (int i = 0; i < r; i++) {
        int x,y;
        scanf("%d%d", &x, &y);
        if (y == 1) hasB = true;
        Mini(Min[y], x);
        Maxi(Max[y], x);
    }
    int L[2] = {1, 1}, R[2] = {n, n};
    for (int i = 0; i < m; i++) {
        int x;
        scanf("%d", &x);
        for (int j = 0; j < 2; j++){
            if (x <= Min[j]) Maxi(L[j], x);
            if (x >= Max[j]) Mini(R[j], x);
        }
    }
    if (s <= Min[0]) Maxi(L[0], s);
    if (s >= Max[0]) Mini(R[0], s);

    int ans = 0;
    if (hasB) {
        ans += 2 * k;
        Mini(L[0], L[1]);
        Maxi(R[0], R[1]);
    }
    ans += 2 * (R[0] - L[0]);
    printf("%d\n", ans);
}