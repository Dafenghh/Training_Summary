#include <bits/stdc++.h>
using namespace std;
const int N = 5050;
const int INF = 1e9+7;
int n, a[N], tp[N];
 
struct edge{
    int to, cap, rev;
};
 
vector<edge> G[N];
 
void add_edge(int u, int v, int cap) {
    G[u].push_back((edge){v, cap, (int)G[v].size()});
    G[v].push_back((edge){u, 0, (int)G[u].size()-1});
}
 
void connect(int u, int v) {
    assert(tp[u] != tp[v]);
    if (tp[u] > tp[v]) swap(u, v);
    add_edge(u, v, 1);
}
 
int V;
 
int level[N], iter[N];
 
void bfs(int s) {
    memset(level, -1, sizeof level);
    level[s] = 0;
    queue<int> que;
    que.push(s);
    while (!que.empty()) {
        int v = que.front(); que.pop();
        for (auto &e: G[v]) {
            if (e.cap > 0 && level[e.to] == -1) {
                level[e.to] = level[v] + 1;
                que.push(e.to);
            }
        }
    }
}
 
int dfs(int v, int t, int f) {
    if (v == t) return f;
    for (int &i = iter[v]; i < G[v].size(); i++) {
        auto &e = G[v][i];
        if (e.cap > 0 && level[v] < level[e.to]) {
            int d = dfs(e.to, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
 
    return 0;
}
 
int max_flow(int s, int t) {
    int flow = 0;
    for (;;) {
        bfs(s);
        if (level[t] <0) return flow;
        memset(iter, 0, sizeof iter);
        int f;
        while ((f=dfs(s, t, INF)) > 0) flow += f;
    }
}
 
bool used[N];
 
void dfs2(int v) {
    used[v] = true;
    for (auto &e: G[v]) {
        if (e.cap > 0 && !used[e.to]) {
            dfs2(e.to);
        }
    }
}
 
 
int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", a+i);
        tp[i] = __builtin_popcount(a[i])%2;
    }
 
    for (int i = 0; i < n; i++)
    for (int j = i+1; j < n; j++) {
        if (__builtin_popcount(a[i]^a[j]) == 1) {
            connect(i, j);
        }
    }
    int s = n, t = n+1;
    V = n+2;
    for (int i = 0; i < n; i++) {
        if (tp[i] == 0) add_edge(s, i, 1);
        else add_edge(i, t, 1);
    }
    int flow = max_flow(s, t);
 
    dfs2(s);
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        if (tp[i] == 0 && used[i] || tp[i] == 1 && !used[i]) ans.push_back(i);
         
    }
 
    assert(ans.size() == n - flow);
    printf("%d\n", ans.size());
    for (int i = 0; i <ans.size(); i++) {
        printf("%d%c", a[ans[i]], " \n"[i==ans.size()-1]);
    }
}
