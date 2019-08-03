#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+10;
typedef long long ll;
int n;
int a[N], b[N], X[N], Y[N], num[N];

int Shrink(int a[]) {
    int sz = 0;
    for (int i = 0; i < n; i++) num[sz++] = a[i];
    sort(num, num+sz);
    sz = unique(num, num+sz)-num;
    for (int i = 0; i < n; i++) a[i] = lower_bound(num, num+sz) - num + 1;
    return sz;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d%d", a+i, b+i, X+i, Y+i);
    }
}