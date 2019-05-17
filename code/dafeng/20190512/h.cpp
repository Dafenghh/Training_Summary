#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+10;
const int INF = 1e9+7;
int n,q,k, id[N];
inline int lowbit(int i) {
	return i & -i;
}
typedef long long ll;
struct BIT {
	ll dat[N];
	void add(int i, ll x) {
		++i;
		for (; i <= n; i += lowbit(i)) dat[i] += x;
	}
	ll sum(int i) const{
		++i;
		ll res = 0;
		for (; i > 0; i -= lowbit(i)) res += dat[i];
		return res;
	}
};

BIT idx[2], cnt[2];
BIT cycle[2];

ll get(const BIT& bit, int l, int r) {
	if (l > r) return 0;
	return bit.sum(r) - bit.sum(l-1);	
}

ll solve(int l, int r, ll d) {
	ll len = d * k % n;
	ll res = get(cycle[d&1], l, r);	
	res += get(idx[0], l, r) - get(cnt[0], l, r) * len + get(cnt[0], l, len-1) * n;
	res += get(idx[1], l, r) + get(cnt[1], l, r) * len - get(cnt[1], n-len, r) * n;
	return res;
}

char s[N];
int ct[N], cpos[N][2];

void remove(int i) {
	int k = (s[i] == '(' ? 0 : 1);
	idx[k].add(i, -i);
	cnt[k].add(i, -1);
	
	cycle[0].add(i, cpos[i][0]);
	cycle[1].add(i, cpos[i][1]);
}

void build() {
	for (int i = 0; i < n; i++) {
		int k = (s[i] == '(' ? 0 : 1);
		idx[k].add(i, i);
		cnt[k].add(i, 1);	
	}
}

struct Qry {
	int l,r,d,id;	
}Q[N];

bool used[N];

int next(int i) {
	if (s[i] == '(') return (i-k+n)%n;
	return (i+k)%n;	
}

void dfs(int v, int pre, int root) {
	if (used[v]) return;
	used[v] = true;
	int u = next(v);
	if (u == root) {
		ct[v] = INF;
	}
	else if (u == pre) {
		ct[v] = 0;
		cpos[v][0] = v;
		cpos[v][1] = u;
	}
	else {
		dfs(u, v, root);
		if (ct[u] == INF) ct[v] = INF;
		else {
			ct[v] = ct[u] + 1;
			cpos[v][0] = cpos[u][1];
			cpos[v][1] = cpos[u][0];
		}
	}
}

void calc() {
	for (int i = 0; i < n; i++) {
		if (used[i]) continue;
		dfs(i, -1, i);
	}
}

ll ans[N];
int main() {
	scanf("%d%d%d%s", &n, &q, &k, s);
	for (int i = 0; i < q; i++) {
		scanf("%d%d%d", &Q[i].l, &Q[i].r, &Q[i].d);
		Q[i].id = i;	
	}
	calc();
	build();
	
	sort(Q, Q+q, [](const Qry &a, const Qry &b) {
		return a.d < b.d;
	});
	for (int i = 0; i < n; i++) id[i] = i;
	sort(id, id + n, [&](int a, int b) {
		return ct[a] < ct[b];	
	});
	
	int j = 0;
	
	for (int i = 0; i < q; i++) {
		while (j < n && ct[id[j]] <= Q[i].d) {
			remove(id[j]);
			++j;
		}
		ans[Q[i].id] = solve(Q[i].l, Q[i].r, Q[i].d);
	}
	for (int i = 0; i < q; i++) printf("%lld\n", ans[i]);

}