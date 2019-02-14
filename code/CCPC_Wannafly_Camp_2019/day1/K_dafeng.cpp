#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> P;
const int N = 1e5+10;
const int M = 220;
int n,m;
vector<int> G[N], T[N], route[N];
int d[N], deg[N], dfn[N], rr[N], clk, stk[N], up[N];

void dfs(int v) {
	dfn[v] = clk++;
	stk[d[v]] = v;
	up[v] = stk[(d[v]+1)/2];
	if (deg[v] != 0) route[v] = vector<int>(stk, stk + d[v] + 1);
	
	for (auto u: T[v]) {
		dfs(u);
	}
	rr[v] = clk;
}

void bfs(int s, int *d) {
	fill(d, d + n + 1, -1);
	d[s] = 0;
	queue<int> que;
	que.push(s);
	while (!que.empty()) {
		int v = que.front(); que.pop();
		for (auto u: G[v]) {
			if (d[u] == -1) {
				d[u] = d[v] + 1;
				que.push(u);
			}
		}
	}	
}

void Maxi(int &a, int b) {
	if (a < b) a = b;
}

P get(int v) {
	return P(dfn[v], rr[v]);
}

int dist[M][N], sp[M];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		int x,y;
		scanf("%d%d", &x, &y);
		G[x].push_back(y);
		G[y].push_back(x);
	}
	for (int i = 1; i <= n; i++) deg[i] = G[i].size();
	
	memset(d, -1, sizeof d);
	d[1] = 0;
	queue<int> que;
	que.push(1);
	while (!que.empty()) {
		int v = que.front(); que.pop();
		for (auto u: G[v]) {
			if (d[u] == -1) {
				d[u] = d[v] + 1;
				que.push(u);
				T[v].push_back(u);
				deg[u]--;
				deg[v]--;
			}
		}
	}
	
	int cnt = 0;
	
	for (int i = 1; i <= n; i++) {
		if (deg[i] == 0) continue;
		sp[cnt++] = i;
		bfs(i, dist[cnt-1]);
	}
	
	dfs(1);
	
	int ans = 0;
	for (int v = 2; v <= n; v++) {
		vector<P> vec;
		vec.push_back(get(up[v]));
		for (int i = 0; i < cnt; i++) {
			int u = sp[i];
			if (dist[i][v] <= d[u]) {
				vec.push_back(get(route[u][(dist[i][v] + d[u] + 1) / 2]));
			}
		}
		sort(vec.begin(), vec.end());	
		
		int l = -1, r = -1, len = 0;
		for (auto p: vec) {
			if (p.first <= r) Maxi(r, p.second);
			else {
				len += r - l;
				l = p.first;
				r = p.second;
			}
		}
		len += r - l;
		Maxi(ans, len);
	}
	printf("%d\n", n - ans);
}