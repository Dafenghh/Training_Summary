#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+10;
const int K = 20;
int n,m;
vector<int> oriG[N];
int clk, pre[N], low[N];

struct edge{
	int to,cost;
};

vector<edge> G[N*2];


int d[N*2],depth[N*2], parent[K][N*2], Cnt[N*2];


void dfs2(int v, int p) {
	Cnt[v]++;
	assert(Cnt[v] == 1);
	parent[0][v] = p;
	
	for (auto &e: G[v]) {
		int u = e.to;
		if (u == p) continue;
		d[u] = d[v] + e.cost;
		depth[u] = depth[v] + 1;
		dfs2(u, v);
	}
}

void init_lca() {
	dfs2(1, 0);
	for (int k = 0; k + 1 < K; k++) {
		for (int v = 1; v <= n; v++) {
			if (parent[k][v] < 0) parent[k + 1][v] = -1;
			else parent[k+1][v] = parent[k][parent[k][v]]; 
		}
	}
}

int lca(int u, int v) {
	if (depth[u] > depth[v]) swap(u,v);
	for (int k = 0; k < K; k++) {
		if ((depth[v] - depth[u]) >> k & 1) v = parent[k][v];
	}
	if (u == v) return u;
	for (int k = K - 1; k >= 0; k--) {
		if (parent[k][u] != parent[k][v]) {
			u = parent[k][u];
			v = parent[k][v];
		}
	}
	return parent[0][u];
}



void add_edge(int u, int v, int cost) {
	G[u].push_back((edge){v, cost});
	G[v].push_back((edge){u, cost});
}

typedef pair<int, int> P;

int sz;

stack<int> stk;

void Add(vector<int> &vec) {
	if (vec.size() <= 1) return;
	for (auto v: vec){
		add_edge(v, sz, 1);
	}
	vec.clear();
}

int cnt=0;
int fa[N];

vector<int> vec;

void dfs(int u) {
    //printf("dfs: %d\n", u);
	//if (u % 100 == 0) printf("dfs: %d %d\n", u, stk.size());
	low[u] = pre[u] = ++clk;
	stk.push(u);
	for (auto v: oriG[u]) {
		 if (v == fa[u]) continue;
		 if (!pre[v]) {
			++cnt;
			fa[v] = u;
			dfs(v);

			--cnt;
			low[u]= min(low[u], low[v]);
			
			
			
			if (low[v] > pre[u]) {
				add_edge(u, v, 2);
			}
			else if (low[v] == pre[u]) {
				++sz;
				
				while (!stk.empty() && stk.top() != v) {
					vec.push_back(stk.top());
					stk.pop();
				}
				assert(!stk.empty());
				stk.pop();
				vec.push_back(v);
				vec.push_back(u);
				Add(vec);	
			}
		}
		else if (pre[v] < pre[u] && v != fa[u]) low[u] = min(low[u], pre[v]);
	}
	if (low[u] == pre[u]) {
		assert(!stk.empty() && stk.top() == u);
		stk.pop();
	}

}






int solve(int u, int v) {
	int l = lca(u, v);
	return d[u] + d[v] - 2 * d[l];
}


int main() {
	int q;
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 0; i < m; i++) {
		int u,v;
		scanf("%d%d", &u, &v);
		oriG[u].push_back(v);
		oriG[v].push_back(u);
	}
	
	sz = n;
	dfs(1);
	n = sz;

	init_lca();
	
	for (int qi = 1; qi <= q; qi++) {
		int u,v;
		scanf("%d%d", &u, &v);
		printf("%d\n", solve(u,v)/2);
	}
	
	
}