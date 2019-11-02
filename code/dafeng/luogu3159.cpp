#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct edge {
    int to,cap,cost,rev;
    edge() {}
    edge(int to, int cap, int cost, int rev):to(to), cap(cap), cost(cost), rev(rev){}
};
const int N = 1230;
const int INF = 1e9+7;
vector<edge> G[N];

void add_edge(int u, int v, int cap, int cost) {
   // printf("add_edge: %d %d %d %d\n", u, v, cap, cost);
    G[u].push_back(edge(v, cap, cost, G[v].size()));
    G[v].push_back(edge(u, 0, -cost, G[u].size()-1));
}

int iter[N], vis[N];
ll h[N], d[N];
int s,t,V;
int ret; // total cost

typedef pair<ll,int> P;
priority_queue<P, vector<P>, greater<P> > que;

bool dijk() {
    fill(d, d+V, INF);
    d[s] = 0;
    que.push(P(0,s));
    while (!que.empty()) {
        P p = que.top(); que.pop();
        int v = p.second;
        if (d[v] < p.first) continue;
        for (auto &e: G[v]) {
            if (e.cap > 0 && d[e.to] > d[v] + e.cost + h[v] - h[e.to]) {
                d[e.to] = d[v] + e.cost + h[v] - h[e.to];
                que.push(P(d[e.to], e.to));
            }
        }
    }
    for (int v = 0; v < V; v++) h[v] += d[v];
    for (int i = 0; i < V; i++) {
     //   printf("d[%d]=%lld\n", i, d[i]);
    }
    return h[t] < INF;
}

int dfs(int v, int f) {
   // cerr << "dfs: " << v << " " << f << endl;
    if (v == t) return f;
    vis[v] = 1;
    int ans = 0;
    for (int &i = iter[v]; i < G[v].size(); i++) {
        
        edge& e = G[v][i];
        //cerr<<"edge: " << v << " " << e.to << endl;
        if (!vis[e.to] && e.cap > 0 && h[e.to] == h[v] + e.cost) {
            int x = dfs(e.to, min(e.cap, f-ans));
            if (x) {
                ret += x*e.cost;
                e.cap -= x;
                G[e.to][e.rev].cap += x;
                ans += x;
            }
        }
    }
    vis[v] = 0;
    return ans;
}

int mincost() {
    int f = 0;
    while (dijk()) {
        //cerr << f <<" d=" << d[t] << " " << h[t] << endl;
        fill(iter, iter+V, 0);
        int x;
        while ((x=dfs(s, INF))) f += x;
    }
  //  cout << "f=" << f << endl;
    return f;
}
const int M = 22;
int n,m, a[M][M], b[M][M], c[M][M];
int getid(int i, int j, int k) {
    return i*m+j+k*n*m;
}

bool valid(int i, int j) {
    return i >= 0 && i < n && j >= 0 && j < m;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
        scanf("%1d", &a[i][j]);
    for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
        scanf("%1d", &b[i][j]);
    for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
        scanf("%1d", &c[i][j]);

    V = 3*n*m+2;
    s = V-2, t = V-1;
    int cnt01 = 0, cnt10 = 0;

    for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
        if (a[i][j] == 0 && b[i][j] == 1) {
            cnt01++;
          //  printf(": %d %d [1]\n", i, j);

            add_edge(getid(i,j,0), getid(i,j,1), (c[i][j]+1)/2, 0);
            add_edge(getid(i,j,1), getid(i,j,2), INF, 1);
            add_edge(getid(i,j,1), t, 1, 0);
        } else if (a[i][j] == 1 && b[i][j] == 0) {
          //  printf(": %d %d [2]\n", i, j);
            cnt10++;
            add_edge(getid(i,j,0), getid(i,j,1), INF, 0);
            add_edge(s, getid(i,j,1), 1, 0);
            add_edge(getid(i,j,1), getid(i,j,2), (c[i][j]+1)/2, 1);
        } else {
          //  printf(": %d %d [3]\n", i, j);
            add_edge(getid(i,j,0), getid(i,j,1), c[i][j]/2, 0);
            add_edge(getid(i,j,1), getid(i,j,2), INF, 1);
        }

        for (int di = -1; di<=1; di++)
        for (int dj = -1; dj<=1; dj++) {
            if (di==0 && dj==0) continue;
            int ni = i+di, nj = j+dj;
            if (!valid(ni,nj)) continue;
          //  printf("Add: %d %d %d %d\n", i, j, ni, nj);
            add_edge(getid(i,j,2), getid(ni,nj, 0), INF, 0);
        }
    }


 //   cerr << ": " << cnt01 << " " << cnt10 << endl;
    if (cnt01 != cnt10) return puts("-1"), 0;
    int res = mincost();
    //printf("res=%d\n", res);
    if (res != cnt01) return puts("-1"), 0;
    printf("%d\n", ret);

}
