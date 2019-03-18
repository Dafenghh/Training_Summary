#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct P{
	ll x,y;
	
	explicit P(ll x = 0, ll y = 0):x(x), y(y) {}
	P operator+(const P &b) const{
		return P(x+b.x, y+b.y);
	}
	P operator-(const P &b) const{
		return P(x-b.x, y-b.y);
	}	
	ll operator*(const P&b) const {
		return x * b.y - y * b.x;
	}
	
	bool operator < (const P&b) const{
		return (*this)*b > 0;
	}
	 
};

struct Ans{
	P val,p1,p2;
	bool operator < (const Ans&b) const{
		return val < b.val;
	}
	double get() const{
		assert(val.x != 0);
		return (double)val.y/val.x/2;
	}
};

const int N = 302;

int a[N][N], n;

ll sum[N][N], b[N], s[N];

P conv[N];

int top;

bool test(const P&p) {
	if (top >= 1 && conv[top].y >= p.y) return true;
	if (top >= 2 && (conv[top]-conv[top-1])*(p-conv[top]) <= 0) return true; 
	return false;
}

Ans solve(int L, int R) {
	int d = R-L+1;
	for (int i = 1; i <= n; i++) {
		b[i] = sum[R][i] - sum[L-1][i];
		s[i] = s[i-1] + b[i];
	}
	
	top = 1;
	conv[top] = P();
	Ans ans = {P(2, a[1][1]), P(1,1), P(1,1)};
	
	for (int i = 1; i <= n; i++) {
		int l = 0, r = top;
		P p(i+d, s[i]);
		while (l + 1 < r) {
			int mid = (l + r) / 2;
			if ((p- conv[mid]) * (conv[mid+1] - conv[mid]) <= 0) l = mid;
			else r = mid;
		}
		Ans tmp = {p-conv[r], P(conv[r].x+1,L), P(i, R)};
		ans = max(ans, tmp);
		
		//if (L == 6 && R == 6)
			//printf("%d %d %d %d: %.10lf %d %d %d %d\n", L, R, i, r, tmp.get(), tmp.p1.x, tmp.p1.y, tmp.p2.x, tmp.p2.y);
		
	
		p = P(i, s[i]);
		while (test(p)) --top;
		conv[++top] = p;
		

	} 
	
	return ans;
}

ll gcd(ll x, ll y) {
	if (y == 0) return x;
	return gcd(y, x % y);
}
int main() {
	int test = 0;
	for (;;) {
		scanf("%d", &n);
		if (n == 0) break;
		for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			scanf("%d", &a[i][j]);
			sum[i][j] = sum[i-1][j] + a[i][j];
		}

		Ans ans = {P(2, a[1][1]), P(1,1), P(1,1)};

		for (int l = 1; l <= n; l++)
		for (int r = l; r <= n; r++) {
			ans = max(ans, solve(l, r));
		}		
	
		printf("Case #%d: The maximal value is %.10lf, rectangle corners are (%lld, %lld) and (%lld, %lld).\n",
			++test, ans.get(), ans.p1.x, ans.p1.y, ans.p2.x, ans.p2.y);

	
		//printf("Case #%d: %.10lf\n", ++test, ans.get());
	}
	
}