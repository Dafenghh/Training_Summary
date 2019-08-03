#include <bits/stdc++.h>
using namespace std;
const int N = 4004;
const int Mod = 1e9+7;
 
int dp[N][N];
 
typedef long long ll;
void add(int &a, ll b) {
    a = (a + b) % Mod;
}
 
void solve(int n, int m) {
    int tot = 2 * (n+m);
     
    for (int i = 0; i <= tot+1;i++)for (int j =0;j <= tot+1; j++) dp[i][j] = 0;
    dp[0][0] = 1;   
    for (int i = 0; i <= tot; i++)
    for (int j = 0; j <= i; j++) {
        if (j+1<=n || i-j >= j+1-n) add(dp[i+1][j+1], dp[i][j]); 
        if (i+1-j<=m || j >= i+1-j-m) add(dp[i+1][j], dp[i][j]);
    }
    printf("%d\n", dp[tot][n+m]);       
}
 
int main() {
    int n,m; 
    while (scanf("%d%d", &n, &m) != EOF) {
        if (n == 0 && m == 0) printf("%d\n", 1);
        else {
            solve(n, m);
        }
    }
}