#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
const int N = 2e5+10;
int n,m,k;
typedef pair<int,int> P;
P a[N];

int ans[N], deg[N];
vector<int> G[N];

set<P> vert;

bool valid_vert[N];
bool valid_edge[N];

void dec(int v) {
	if (!valid_vert[v]) return;	
	vert.erase(P(deg[v], v));
	deg[v]--;
	vert.insert(P(deg[v], v));
}

void RemoveEdge(int i) {
	if (!valid_edge[i]) return;
	valid_edge[i] = false;	
	dec(a[i].x);
	dec(a[i].y);	
}

void Pop(int v) {
	valid_vert[v] = false;
	for (auto i: G[v]) RemoveEdge(i);
}

void Maintain() {
	while (!vert.empty()) {
		P p = *vert.begin();
		int v = p.second;
		if (p.first >= k) break;
		vert.erase(p);
		Pop(v);	
	}	
}

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &a[i].x, &a[i].y);
		deg[a[i].x]++;
		deg[a[i].y]++;
		G[a[i].x].push_back(i);
		G[a[i].y].push_back(i);
		
		valid_edge[i] = true;
	}
		
	for (int i = 1; i <= n; i++) {
		vert.insert(P(deg[i], i));
		valid_vert[i] = true;	
	}
	
	Maintain();	
	ans[m] = vert.size();
	for (int i = m; i >= 1; i--) {
		if (!valid_edge[i]) {
			ans[i-1] = ans[i];
			continue;
		}
		RemoveEdge(i);
		Maintain();
		ans[i - 1] = vert.size(); 	
	}
	for (int i = 1; i <= m; i++) {
		printf("%d\n", ans[i]);
	}
}