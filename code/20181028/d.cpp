#include <bits/stdc++.h>
using namespace std;
const int N = 205;
const int Mod = 1e9+7;
void add(int &a, int b) {
    a = (a + b) % Mod;
}
int a[N], m[N][N], n, dp[N][N][N][3];
void init() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
        scanf("%1d", &m[i][j]);
}

void solve() {

    for (int i = 1; i <= n; i++) m[0][i] = 1;
    int ans = 0;
    for (int i = 0; i <= n; i++)
    for (int j = 0; j <= n; j++)
    for (int k = 0; k <= n; k++)
    for (int t = 0; t < 3; t++)
        dp[i][j][k][t] = 0;

    dp[0][0][0][0] = 1;
    for (int i = 0; i <= n; i++)
    for (int j = 0; j <= n; j++)
    for (int k = 0; k <= n; k++) {
        if (a[i] == a[j] && a[j] == a[k]) { // valid 0
            add(ans, dp[i][j][k][0]);
            add(dp[i+1][j][k][1], dp[i][j][k][0]);
        }
        if (a[j] == a[k]) {
            add(dp[i+1][j][k][1], dp[i][j][k][1]);
            if (m[a[j]][a[i]]) add(dp[i][j+1][k][2], dp[i][j][k][1]);
        }
    }
}


int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        init();
        solve();
    }
}