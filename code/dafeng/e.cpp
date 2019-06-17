#include <bits/stdc++.h>
using namespace std;

inline char gch()
{
    static char buf[100010], *h = buf, *t = buf;
    return h == t && (t = (h = buf) + fread(buf, 1, 100000, stdin), h == t) ? EOF : *h ++;
}
template <class T>
inline void re(T &x)
{
    x = 0;
    char a; bool b = 0;
    while(!isdigit(a = gch()))
        b = a == '-';
    while(isdigit(a))
        x = (x << 1) + (x << 3) + a - '0', a = gch();
    if(b == 1)
        x *= -1;
}


typedef pair<ll,int> P;
#define x first
#define c second
const ll INF = 1e18+7;
const int N = 1e5+10;
struct node {
	P mx[2];
	node() {
		mx[0] = P(-INF, 0);
		mx[1] = P(-INF, 1);
	}
	node(const P&p1, const P&p2) {
		mx[0] = p1;
		mx[1] = p2;
	}
	void set(ll x, int c) {
		mx[0] = P(x, c);
		mx[1] = P(-INF, N);
	}
};


ll getAns(const node& a, const node& b) {
	if (a.mx[0].c != b.mx[0].c) return a.mx[0].x + b.mx[0].x;
	return max(a.mx[0].x+b.mx[1].x, a.mx[1].x+b.mx[0].x); 
}

void Maxi(int &a, int b) {
	if (b > a) a = b;
}
int n;
node merge(const node&a, const node&b) {
    //if (n > 10000) return a;

    if (a.mx[0].x >= b.mx[0].x) {
        if (a.mx[1].x >= b.mx[0].x) return a;
        if (a.mx[0].c != b.mx[0].c) return node(a.mx[0], b.mx[0]);
        if (a.mx[1].x >= b.mx[1].x) return a;
        return node(a.mx[0], b.mx[1]);
    } else {
        if (b.mx[1].x >= a.mx[0].x) return b;
        if (b.mx[0].c != a.mx[0].c) return node(b.mx[0], a.mx[0]);
        if (b.mx[1].x >= a.mx[1].x) return b;
        return node(b.mx[0], a.mx[1]);
    }
}

struct ninja {
	ll x,y;
    int c;
}a[N];



int cnt_update = 0;
int cnt_query;
struct segTree {
	node dat[4*N];
	int type;
	ll f(ll x, ll y) const{
		return (type&1?1:-1)*x + (type&2?1:-1)*y;
	}
	segTree(int type):type(type) {}
	
	
	void build(int v = 0, int l = 1, int r = n + 1) {
		if (l + 1 == r) {
			dat[v].set(f(a[l].x, a[l].y), a[l].c);
		}		
		else {
			int mid = (l + r) / 2, chl = v * 2 + 1, chr = v * 2 + 2;
			build(chl, l, mid);
			build(chr, mid, r);
			dat[v] = merge(dat[chl], dat[chr]);
		}
	}
	node query(int L, int R, int v = 0, int l = 1, int r = n + 1) {
		++cnt_query;
		if (r <= L || R <= l) return node();
		if (L <= l && r <= R) return dat[v];
		int mid = (l + r) / 2, chl = v * 2 + 1, chr = v * 2 + 2;
		return merge(query(L, R, chl, l, mid), query(L, R, chr, mid, r));
	}
	void update(int pos, int v = 0, int l = 1, int r = n + 1) {
		++cnt_update;
		if (l + 1 == r) {
			dat[v].set(f(a[l].x, a[l].y), a[l].c);
		}
		else {
			int mid = (l + r) / 2, chl = v * 2 + 1, chr = v * 2 + 2;
			if (pos < mid) update(pos, chl, l, mid);
			else update(pos, chr, mid, r);
			dat[v] = merge(dat[chl], dat[chr]);
		}
	}
};

segTree T[4] = {0,1,2,3};

void solve() {
	int q;
	re(n); re(q);
	for (int i = 1; i <= n; i++) re(a[i].x), re(a[i].y), re(a[i].c);
	for (int i = 0; i < 4; i++) T[i].build();
	
//	cerr << "q begin: " << clock() << endl;
	while (q--) {
		int op;
		re(op);
		if (op == 1) {
			int k,x,y;
			re(k); re(x); re(y);
			a[k].x += x;
			a[k].y += y;
			for (int i = 0; i < 4; i++) T[i].update(k);
		}
		else if (op == 2) {
			int k,c;
			re(k); re(c);
			a[k].c = c;
			for (int i = 0; i < 4; i++) T[i].update(k);
		}
		else {
			int l,r;
			re(l); re(r);
			++r;
			node ns[4];
			for (int i = 0; i < 4; i++) {
				ns[i] = T[i].query(l, r);
			}
			ll ans = max(getAns(ns[0], ns[3]), getAns(ns[1], ns[2]));
			if (ans < 0) ans = 0;
			printf("%lld\n", ans);
		}
	}
	
//	cerr<<"update: " << cnt_update << endl;
//	cerr<<"query: " << cnt_query << endl;
	cnt_update = 0;
	cnt_query = 0;
}

int main() {
	int T;
	re(T);
	for (int i = 1; i <= T; i++) {
		printf("Case #%d:\n", i);
		solve();
		//cerr << clock() << endl;
	}
}