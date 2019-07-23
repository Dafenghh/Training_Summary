#include <bits/stdc++.h>
using namespace std;
int n,m;
const int N = 102;
const int Mod = 998244353;
int lst_max[N][4], lst_min[N][4], dp[2][N][N][N]; 
void Mini(int &a, int b) {
    if (b < a) a = b;
}

void Maxi(int &a, int b) {
    if (a < b) a = b;
}
typedef long long ll;
void add(int &a, ll b) {
    a = (a + b) % Mod;
}
void solve() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    for (int j = 1; j <= 3; j++) {
        lst_min[i][j] = 0;
        lst_max[i][j] = max(i-j, 0);
    }

    for (int i = 0; i < m; i++) {
        int l,r,x;
        scanf("%d%d%d", &l, &r, &x);
        
        if (x < 4) {
            for (int i = l; i <= r; i++) {
                Mini(lst_max[i][x], l-1);
            }
        }
        
        Maxi(lst_min[r][x-1], l);
      //  printf("!!!%d, %d: %d\n", i, x-1, lst_min[i][x-1]);
    }

    for (int i = 1; i <= n; i++)
    for (int j = 1; j <= 3; j++) {
      //  printf("%d %d: %d %d\n", i,j,lst_min[i][j],lst_max[i][j]);
        if (lst_min[i][j] > lst_max[i][j]) {
      //      printf("!%d %d: %d %d\n", i,j,lst_min[i][j],lst_max[i][j]);
            puts("0");
            return;
        }
    }
    memset(dp, 0, sizeof dp);
    dp[1][0][0][0] = 4;
    for (int i = 1; i < n; i++) {
        int now = i & 1;
        for (int j = lst_min[i+1][1]; j <= lst_max[i+1][1]; j++)
        for (int k = lst_min[i+1][2]; (k == 0 || k < j) && k <= lst_max[i+1][2]; k++)
        for (int t = lst_min[i+1][3]; (t == 0 || t < k) && t <= lst_max[i+1][3]; t++) {
            dp[now^1][j][k][t] = 0;
        }

        for (int j = lst_min[i][1]; j <= lst_max[i][1]; j++)
        for (int k = lst_min[i][2]; (k == 0 || k < j) && k <= lst_max[i][2]; k++)
        for (int t = lst_min[i][3]; (t == 0 || t < k) && t <= lst_max[i][3]; t++) {
       //     printf("dp[%d][%d][%d][%d]=%d\n", i,j,k,t, dp[now][j][k][t]);


            add(dp[now^1][j][k][t], dp[now][j][k][t]);
            if (j == 0) add(dp[now^1][i][k][t], 3LL*dp[now][j][k][t]);
            else {
                add(dp[now^1][i][k][t], dp[now][j][k][t]);
                if (k == 0) add(dp[now^1][i][j][t], 2*dp[now][j][k][t]);
                else {
                    add(dp[now^1][i][j][t], dp[now][j][k][t]);
                    add(dp[now^1][i][j][k], dp[now][j][k][t]);
                }
            }
        }
    }

    int ans = 0;

    for (int j = lst_min[n][1]; j <= lst_max[n][1]; j++)
    for (int k = lst_min[n][2]; (k == 0 || k < j) && k <= lst_max[n][2]; k++)
    for (int t = lst_min[n][3]; (t == 0 || t < k) && t <= lst_max[n][3]; t++) {
            add(ans, dp[n&1][j][k][t]);
    } 
    printf("%d\n", ans);
}


int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
}