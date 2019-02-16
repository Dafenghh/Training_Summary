#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+10;
const int B = 200;
const int M = N/B+10;
int bit[N], a[N], n, blk[M], blk_tot[M], f[N];
inline int lowbit(int i) {
    return i & -i;
}
int query(int i) {
    int res = 0;
    for (; i > 0; i -= lowbit(i)) res += bit[i];
    return res;
}
void update(int i, int x) {
    for (; i <= n; i += lowbit(i)) bit[i] += x;
}
typedef long long ll;
const int Mod = 1e9 + 7;
void add(int &a, ll b) {
    a = (a + b) % Mod;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = n; i >= 1; i--) {
        int x = a[i], b = x / B;
        int &ans = f[x];
        for (int j = b * B; j < x; j++) {
            if (f[j] == 0) continue;
            add(ans, 1LL * f[j] * query(j));
        }
        for (int j = 0; j < b; j++) add(ans, blk_tot[j]);
        add(ans, 1);

        add(blk[b], ans);
        for (int j = x + 1; j < (b + 1) * B && j <= n; j++) add(blk_tot[b], f[j]);
        for (int j = b + 1; j <= n / B; j++) add(blk_tot[j], blk[j]);

        int pre = query(x);
        update(x, -pre);
        update(x + 1, pre + 1);
    }
    int ans = Mod-n;
    for (int i = 1; i <= n; i++) add(ans, f[i]);
    printf("%d\n", ans);
}