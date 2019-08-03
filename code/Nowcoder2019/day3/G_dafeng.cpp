#include <bits/stdc++.h>
using namespace std;
const int N = 3e5+10;
const int K = 20;
typedef long long ll;
int a[N], n, Log2[N], st[N][K];
 
int Max(int i, int j) {
    return a[i] > a[j] ? i : j;
}
 
int query(int l, int r) {
    int t = Log2[r-l+1];
    return Max(st[l][t], st[r-(1<<t)+1][t]);
}
 
void init() {
    Log2[0] = -1;
    for (int i = 1; i < N; i++) Log2[i] = Log2[i/2] + 1;
}
 
 
ll sum[N];
 
ll ans = 0;
 
void solve(int l, int r) {
    if (l >= r) return;
 
    int k = query(l, r);
    if (k-l < r-k) {
        int st = k;
        for (int i = l-1; i < k && st <= r; i++) {
            st = lower_bound(sum+st, sum+r+1, sum[i] + 2 * a[k]) - sum;
            ans += r - st + 1;
        }
    }
    else {
        int st = l - 1;
        for (int j = k; j <= r; j++) {
            st = upper_bound(sum + st, sum + k, sum[j] - 2*a[k]) - sum;
            ans += st - (l-1);
        }
    }
 
 
    solve(l, k-1);
    solve(k+1, r);
}
 
 
void solve() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
     
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i-1] + a[i];
        st[i][0] = i;
    }
 
    for (int t = 1; t < K; t++)
    for (int i = 1; i+(1<<(t-1)) <= n; i++)
        st[i][t] = Max(st[i][t-1], st[i+(1<<(t-1))][t-1]);
 
    ans = 0;
    solve(1, n);
     
    printf("%lld\n", ans);
 
     
}
 
 
int main() {
    init();
 
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
}
