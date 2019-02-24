#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+10;
typedef pair<int,int> P;

struct Node{
	set<P> S;
	
	auto findNotGreater(int x) { // <= x
		auto it = S.lower_bound(P(x + 1, 0));
		if (it == S.begin()) return S.end();
		return --it;
	}
	
	auto findGreater(int x) { // > x
		return S.lower_bound(P(x + 1, 0));
	}
	
	void add(int x, int y) {
		auto it = findNotGreater(x);
		if (it == S.end()) S.insert(P(x,y));
		else if (it->second < y){
			if (it->first == x) S.erase(it);
			S.insert(P(x,y));
		}
		else return;
		
		for (auto it = findGreater(x); it != S.end(); ) {
			if (it->second > y) break;
			S.erase(it++);
		}	
	}	
}f[N];

int n,m;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		int a,b,w;
		scanf("%d%d%d", &a, &b, &w);
		auto it = f[a].findNotGreater(w-1);
		int y = 1;
		if (it != f[a].S.end()) y = it->second + 1;
		f[b].add(w, y);
	}
	int ans = 0;
	
	for (int i = 1; i <= n; i++) {
		if (f[i].S.empty()) continue;
		ans = max(ans, f[i].S.rbegin()->second);
	}
	
	printf("%d\n", ans);
	
}
