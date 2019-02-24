#include <bits/stdc++.h>
using namespace std;
const int N = 305;
int n,m;
string a[N][N], b[N][N];
char s[1000000];
#define x first
#define y second

typedef pair<int,int> P;
typedef pair<P, P> Mov;

Mov rev(Mov v) {
	return Mov(v.second, v.first);
}

int cnt[N][2];

vector<Mov> ans;

void add_move(int x1, int y1, int x2, int y2) {
	ans.push_back(Mov(P(x1, y1), P(x2, y2)));
	assert(y2 <= 1);
	cnt[x2][y2]++;
}

void solve(string a[N][N]) {
	memset(cnt, 0, sizeof cnt);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (auto ch: a[i][j]) {
				int nj = ch - '0', ni = i;
				if (j == nj) ni = i > 0 ? 0 : 1;
				add_move(i, j, ni, nj);
			}
		}
	}
	
	for (int i = 1; i < n; i++)
	for (int j = 0; j < 2; j++)
	for (int k = 0; k < cnt[i][j]; k++)
		add_move(i, j, 0, j);
}

vector<Mov> result;

void move(Mov v) {
	int x1 = v.first.x, y1 = v.first.y;
	int x2 = v.second.x, y2 = v.second.y;
	result.push_back(Mov(P(x1+1,y1+1), P(x2+1,y2+1)));
}


int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
	for (int j = 0; j < m; j++) {
		scanf("%s", s);
		a[i][j] = s;
	}

	for (int i = 0; i < n; i++)
	for (int j = 0; j < m; j++) {
		scanf("%s", s);
		b[i][j] = s;
	}
	
	
	for (int i = 0; i < n; i++)
	for (int j = 0; j < m; j++)
		reverse(a[i][j].begin(), a[i][j].end());
	
	solve(a);
	for (auto v: ans) move(v);
	ans.clear();
	
	solve(b);
	reverse(ans.begin(), ans.end());
	for (auto v: ans) move(rev(v));
	
	printf("%d\n", (int) result.size());
	for (auto v: result) {
		printf("%d %d %d %d\n", v.x.x, v.x.y, v.y.x, v.y.y);
	}
}
