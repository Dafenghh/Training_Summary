#include <bits/stdc++.h>
using namespace std;
const int N = 10024;
const int M = 102;
 
char ch[M][2], s[M][N];
int len[M];
int n,m, cnt[20], sum[20];
 
int deg[N];
char val[N];
vector<int> G[N];
void add_edge(int u, int v) {
    G[u].push_back(v);
    ++deg[v];
}
 
int main() {
    scanf("%d%d", &n, &m);
    memset(cnt, -1, sizeof cnt);
 
    for (int i = 0; i < m*(m-1)/2; i++) {
        scanf("%s%d", &ch[i], &len[i]);
 
        if (len[i] != 0) scanf("%s", &s[i]);
 
        int c[2]={0};
        for (int j = 0; j < len[i]; j++) {
            ++c[(s[i][j]==ch[i][1])];
        }
        for (int j = 0; j < 2; j++) {
            if (cnt[ch[i][j]-'a'] == -1) cnt[ch[i][j]-'a'] = c[j];
            if (cnt[ch[i][j]-'a'] != c[j]) return puts("-1"), 0;
        }
    }
 
 
    for (int i = 0; i < m; i++) sum[i+1] = sum[i] + cnt[i];
 
    if (sum[m] != n) return puts("-1"), 0;
 
    int sz = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j <cnt[i]; j++)
            val[sz++] = 'a' + i;
    }
 
    for (int i = 0; i < m*(m-1)/2; i++) {
        int id[2];
        for (int j = 0; j < 2; j++) id[j] = sum[ch[i][j]-'a'];
        int pre = -1;
 
        for (int j = 0; j < len[i]; j++) {
            int x = (s[i][j]==ch[i][1]);
            int now = id[x]++;
            if (pre != -1) add_edge(pre, now);
            pre = now;
        }
    }
 
    vector<int> ans;
 
    queue<int> que;
    for (int i = 0; i < n; i++) {
        if (deg[i] == 0) que.push(i);
    }
 
    while (!que.empty()) {
        int v = que.front(); que.pop();
        for (auto u:G[v]) {
            deg[u]--;
            if (deg[u] == 0) que.push(u);
        }
        ans.push_back(v);
    }
    if (ans.size() < n)return puts("-1"), 0;
    for (int i = 0; i < n; i++) putchar(val[ans[i]]);
    puts("");
 
 
 
}