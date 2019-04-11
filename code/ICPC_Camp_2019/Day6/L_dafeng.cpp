#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,Mod;
ll mod_pow(ll x, ll n) {
    ll res = 1;
    for (; n > 0; n >>= 1) {
        if (n & 1) res = res * x % Mod;
        x = x * x % Mod;
    }
    return res;
}
const int N = 450;
void add(ll &a, ll b) {
    a = (a + b) % Mod;
}
ll f[N][N], g[N][N], h[N][N], a[N][N];
ll C[N][N];

void init() {
    C[0][0] = 1;
    for (int i = 1; i < N; i++) {
        C[i][0] = 1;
        for (int j = 1; j < N; j++) C[i][j] = (C[i-1][j-1] + C[i-1][j]) % Mod;
    }


    for (int k = 0; k < N; k++) {
        ll base = mod_pow(2, k) - 1;
        for (int j = 0; j < N; j++) {
            a[k][j] = mod_pow(2, k*(k-1)/2) * mod_pow(base, j) % Mod;
        }
    }


}

int main() {
    
    scanf("%d%d", &n, &Mod);
    init();
    f[0][0] = 1;
    for (int i = 0; i <= n-1; i++)
    for (int j = 0; j <= i; j++) {
        add(h[i][j], g[i][j]);
        for (int k = 1; i+k <= n-1; k++) {
            if (n-i-2>=0) {
                add(f[i+k][k], f[i][j] * C[n-i-2][k] % Mod * a[k][j]);
                add(g[i+k][k], f[i][j] * C[n-i-2][k-1] % Mod * a[k][j]);
            }
            add(g[i+k][k], g[i][j] * C[n-i-1][k] % Mod * a[k][j]);
            add(h[i+k][k], h[i][j] * C[n-i-1][k] % Mod * a[k][j]);
        }
    }
    ll ans = 0;
    for (int j = 0; j <= n - 1; j++) add(ans, h[n-1][j]);
    add(ans, Mod);
    printf("%lld\n", ans);

}