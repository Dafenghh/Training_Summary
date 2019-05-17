#include <bits/stdc++.h>
using namespace std;

const int Mod = 998244353;
const int N = 505;
int dp[N][N];
int C[N][N];
void init() {
    C[0][0] = 1;
    for (int i = 1; i < N; i++) {
        C[i][0] = 1;
        for (int j = 1; j < N; j++) C[i][j] = (C[i-1][j-1] + C[i-1][j]) % Mod;
    }
}
int a[N];
typedef long long ll;
void add(int &a, ll b) {
    a = (a + b) % Mod;
}

int main() {
    init();
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    a[0] = -1, a[n+1] = -2;
    for (int l = n; l >= 0; l--)
    for (int r = l + 1; r <= n+1; r++) {
        if (a[l] == a[r]) dp[l][r] = 0;
        else if (r-l==1) dp[l][r] = 1;
        else {
            for (int k = l+1; k < r; k++) {
                add(dp[l][r], 1LL * dp[l][k] * dp[k][r] % Mod * C[r-l-2][k-l-1]);
            }
        }
        //printf("dp[%d][%d] = %d\n", l,r,dp[l][r]);
    }
    printf("%d\n", dp[0][n+1]);
}