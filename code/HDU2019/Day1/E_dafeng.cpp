#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 10020;
const ll INF = 1e18;
typedef pair<int,int>P;
#define x first
#define y second
vector<P> G1[N], G2[N];
ll d1[N], d2[N];
int n,m;
void dijk(vector<P> G[], ll d[], int s) {
	fill(d+1, d+n+1, INF);	
	d[s] = 0;
	priority_queue<P, vector<P>, greater<P> > que;
	que.push(P(0,s));
	while (!que.empty()) {
		P p = que.top(); que.pop();
		int v = p.second;
		if (p.first > d[v]) continue;
		for (auto &e: G[v]) {
			int u = e.x;
			if (d[u] > d[v] + e.y) {
				d[u] = d[v] + e.y;
				que.push(P(d[u], u));
			}
		}
	}
}

struct edge{
	int to;
	ll cap;
	int rev;
	edge():to(0),cap(0), rev(0){}
	edge(int to, ll cap, int rev):to(to),cap(cap),rev(rev){}
};

vector<edge> G[N];

void add_edge(int u, int v, ll cap) {
	G[u].push_back(edge(v, cap, G[v].size()));
	G[v].push_back(edge(u, 0, G[u].size() - 1));
}

int level[N], iter[N];

void bfs(int s) {
	
	queue<int> que;
	level[s] = 0;
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

ll dfs(int v, int t, ll f) {
	if (v == t) return f;
	for (int &i = iter[v]; i < G[v].size(); i++) {
		edge &e = G[v][i];
		if (e.cap > 0 && level[e.to] == level[v] + 1) {
			ll d = dfs(e.to, t, min(f, e.cap));
			if (d > 0) {
				e.cap -= d;
				G[e.to][e.rev].cap += d;
				return d;
			}
		}
	}
	return 0;
}

ll max_flow(int s, int t) {
	ll flow = 0;
	for (;;) {
		memset(level, -1, sizeof level);
		memset(iter, 0, sizeof iter);
		bfs(s);
		if (level[t] < 0) return flow;
		flow += dfs(s, t, INF);
	}
}

void solve() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		int x,y,c;
		scanf("%d%d%d", &x, &y, &c);
		G1[x].push_back(P(y, c));
		G2[y].push_back(P(x, c));
	}

	dijk(G1, d1, 1);
	dijk(G2, d2, n);

	int s = 1, t = n;
	ll len = d1[n];
	for (int v = 1; v <= n; v++) {
		for (auto &e: G1[v]) {
			int u = e.x, c = e.y;
			if (d1[v] + c + d2[u] == len) {
				add_edge(v, u, c);
			}
		}
	}
	printf("%lld\n", max_flow(s,t));




	for (int i = 1; i <= n; i++) {
		G1[i].clear();
		G2[i].clear();
		G[i].clear();
	}
}




int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		solve();
	}	
	
}
