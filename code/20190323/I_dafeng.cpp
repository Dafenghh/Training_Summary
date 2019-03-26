#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3010;
int INF;
struct node{
	int cnt,l,r;
}T[N*20];
int tot = 0, root[N];

void ins(int &o, int last, int x, int l = 0, int r = INF+1) {
	o = ++tot;
	T[o] = T[last];
	T[o].cnt++;
	if (l + 1 == r) return;
		
	
	int mid = (l + r) / 2;
	if (x < mid) ins(T[o].l, T[last].l, x, l, mid);
	else ins(T[o].r, T[last].r, x, mid, r);

}

int query(int o, int L, int R, int l = 0, int r = INF+1) { // count >= x
	if (r <= L || R <= l) return 0;
	if (L <= l && r <= R) return T[o].cnt;
	int mid = (l + r) / 2;
	return query(T[o].l, L, R, l, mid) + query(T[o].r, L, R, mid, r);	 
}


ll solve(const vector<int> &a, const vector<int> &b) {
	int n = a.size();
	INF = n;
	assert(n == b.size());
	tot = 0;
	ll res = 0;
	for (int i = 0; i < n; i++) {
		int pre = max(0, i-b[i]);
		//printf("%d: %d %d %d %d\n", i, pre, query(root[i], i, N) , query(root[pre], i, N), res);
	
		res += query(root[i], i, N) - query(root[pre], i, N);
		
		ins(root[i+1], root[i], a[i]+i);
	}
	return res;
}



int r,c;
char s[6200][12010];

typedef pair<int,int> P;
#define x first
#define y second

P trans(int x, int y) {
	int i = x / 2, j = y / 2;
	if (i % 2 == 0) {
		assert(y%4==0);
	}
	else {
		assert(y%4==2);
	}
	return P(i, j);
} 

int a[N][N], b[N][N];


ll solve1() {
	memset(a,0,sizeof a);
	memset(b,0,sizeof b);
	ll res = 0;

	for (int i = 1; i < 2*r-1; i+=2) {
		
		for (int j = 0; j < 2*c-1; j++) {
			if (s[i][j] != '/' && s[i][j] != '\\') continue;
			P pre, cur;
			
			if (s[i][j] == '/') {
				pre = trans(i-1,j+1);
				cur = trans(i+1,j-1);
				
				a[cur.x][cur.y] = a[pre.x][pre.y] + 1;
				
			}
			else {
				pre = trans(i-1,j-1);
				cur = trans(i+1,j+1);
				
				b[cur.x][cur.y] = b[pre.x][pre.y] + 1;
			}

		}
		
		int x = (i+1)/2;
		
		vector<int> A,B;
		
		for (int j = (x&1); j < c; j += 2) {
			A.push_back(a[x][j]);
			B.push_back(b[x][j]);
			if (s[i+1][j*2+1] != '-') {
				int tmp = solve(A,B);
				
	/*			printf("%d %d: \n", i, j);
				for (auto x: A) printf("%d ", x); puts("");
				for (auto x: B) printf("%d ", x); puts("");
				printf("ans=%d\n", tmp);*/
				
				
				res += tmp;
				A.clear();
				B.clear();
			}
		}
		assert(A.empty());
		assert(B.empty());
	} 
	return res;
}


int main() {
	scanf("%d%d", &r, &c);

	fgets(s[0],2*c+2, stdin);
	for (int i = 0; i < 2 * r - 1; i++) {
		fgets(s[i],2*c+2, stdin);
		//printf("%d:%s\n", i, s[i]);
	}
	//return 0;
	
	
	if (r % 2 == 0) r++;
	
	ll ans = 0; 
	
	ans += solve1();
	
	for (int i = 0; i < (2*r-1)/2; i++) 
	for (int j = 0; j < 2*c-1;j++)
		swap(s[i][j], s[2*r-1-1-i][j]);
		
	for (int i = 0; i < 2*r-1; i++) {
		for (int j = 0; j < 2*c-1;j++) {
			char &c = s[i][j];
			if (c == '/') c = '\\';
			else if (c == '\\') c = '/';
		}
		//cout << i << ": "  << s[i] << endl;
	}
	
	
	ans += solve1();
	
	printf("%lld\n", ans);
		
}