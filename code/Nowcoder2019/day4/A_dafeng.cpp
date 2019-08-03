#include <bits/stdc++.h>
using namespace std;
const int N= 1e5+10;
const int INF = 1e9+7;
vector<int> G[N];
int n,k;
int f[N], g[N];
 
bool sp[N];
 
void Maxi(int &a, int b) {
    if (b > a) a = b;
}
 
void dfs(int v, int p = -1) {
    f[v] = -INF;
    if (sp[v]) f[v] = 0;
    for (auto u: G[v]) {
        if (u == p) continue;
        dfs(u, v);
        f[v] = max(f[v], f[u]+1);
    }
 
    int len = 0;
    for (auto u: G[v]) {
        if (u == p) continue;
        Maxi(g[u], len);
        Maxi(len, f[u] + 2);
    }
 
    len = 0;
    for (int i = G[v].size() - 1; i >= 0; i--) {
        int u = G[v][i];
        if (u == p) continue;
        Maxi(g[u], len);
        Maxi(len, f[u] + 2);
    }
}
int ans = N;
void dfs2(int v, int p = -1) {
  //  printf("%d:%d %d\n", v, f[v], g[v]);
    if (p != -1) Maxi(g[v], g[p] + 1);
  //  printf("%d:%d %d\n", v, f[v], g[v]);
 
 
    ans = min(ans, max(g[v], f[v]));
    for (auto u: G[v]) {
        if (u == p) continue;
        dfs2(u, v);
    }
}
 
 
int main() {
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n - 1; i++) {
        int u,v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for (int i = 0; i < k; i++) {
        int x;
        scanf("%d", &x);
        sp[x] = true;
    }
    dfs(1);
    dfs2(1);
    printf("%d\n", ans);
}
