#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int Mod = 1e9+7;
ll mod_pow(ll x, ll n) {
    ll res = 1;
    for (; n > 0; n >>= 1) {
        if (n & 1) res = res * x % Mod;
        x = x * x % Mod;
    }
    return res;
}

void FWT(int a[], int n) {
    for (int d = 1; d < n; d <<= 1)
    for (int i = 0; i < n; i += 2*d)
    for (int j = 0; j < d; j++) {
        int x = a[i+j], y = a[i+d+j];
        a[i+j] = x+y;
        a[i+d+j] = x-y;
    }
}
const int N = 1<<20;
int n,m,k, a[N], num[10];

void dfs(int i, int s, int sign) {
    if (i == m) {
        a[s] += sign;
        return;
    }
    dfs(i+1, s, sign);
    dfs(i+1, s^num[i], -sign);
}

void solve() {
    int sz = 1<<k;
    fill(a, a+sz, 0);
    for (int i = 0; i < n; i++) {
        for (int i = 0; i < m; i++) scanf("%d", num+i);
        dfs(0, 0, 1);
    }
    FWT(a, sz);
    int ans = 0;
    for (int i = 0; i < sz; i++) {
        assert(a[i]%(1<<m)==0);
        int c = mod_pow(3, i) * (a[i]/(1<<m)) % Mod;
        ans ^= c;
    }
    printf("%d\n", ans);
}

int main() {
    while (scanf("%d%d%d", &n, &m, &k) != EOF) {
        solve();
    }
}
