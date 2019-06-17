#include <bits/stdc++.h>
using namespace std;
const int N = 5e5+10;
typedef pair<int,int> P;
map<P, int> M;

vector<P> ans[2];
typedef long long ll;
ll X,Y,Z,a[N];

int calc(int i, int j) {
	assert(i<j);
	if (M.count(P(i,j))) return M[P(i,j)];
	if ((i*X+j*Y)%Z < a[i]+a[j]) return 0;
	return 1;
}

int get(int i, int j) {
	if (i > j) swap(i,j);
	int c = calc(i, j);
	ans[c].push_back(P(i,j));
	return c;
}

void Print(const vector<P> &v) {
	for (auto i: v) {
		printf("%d %d\n", i.first, i.second);
	}
}


int main() {
	int n,m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		int a,b,c;		
		scanf("%d%d%d", &a, &b, &c);
		if (a > b) swap(a,b);
		M[P(a,b)] = c;
	}
	scanf("%lld%lld%lld\n", &X, &Y, &Z);
	for (int i = 1; i <= n; i++) scanf("%lld", a + i);
	stack<int> rest[2];
	int c = get(1,2) ^ 1;
	rest[c].push(1);
	for (int i = 2; i < n; i++) {
		assert(!rest[c].empty());
		assert(rest[c^1].empty());
		if (get(i,i+1) == c) {
			while (!rest[c].empty() && get(rest[c].top(), i+1) == c) {
				rest[c].pop();
			} 
			if (rest[c].empty()) {
				c ^= 1;
				rest[c].push(1);			
			}
		}
		else {
			rest[c].push(i);
		}
	}
	
	if (ans[0].size() == n-1) Print(ans[0]);
	else if (ans[1].size() == n-1) Print(ans[1]);
	else assert(0);
}
