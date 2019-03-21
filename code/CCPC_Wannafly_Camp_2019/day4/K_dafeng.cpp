#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+10;

const int K = 2;
const int Mod[K] = {(int)1e9+7, 998244353};

struct Hash{
    int a[K];
    explicit Hash(int x = 0) {
        for (int i = 0; i < K; i++) a[i] = x % Mod[i];
    }
    int& operator[](int i) {
        return a[i];
    }
    const int& operator[](int i)const{
        return a[i];
    }
    Hash operator+(const Hash &b)const{
        Hash res;
        for (int i = 0; i < K; i++) res[i] = (a[i] + b[i]) % Mod[i];
        return res;
    }
    Hash operator*(const Hash &b)const{
        Hash res;
        for (int i = 0; i < K; i++) res[i] = 1LL * a[i] * b[i] % Mod[i];
        return res;
    }
    bool operator==(const Hash &b) const{
        for (int i = 0; i < K; i++) {
            if (a[i] != b[i]) return false;
        }
        return true;
    }
};

const int M = 18;

Hash all_one[M+1], pw[M+1]; // 1<<(1<<x)

const int MEM = 40000000;
struct node{
    Hash dat;
    int l,r;
}T[MEM];

int tot = 0;

void init() {
	tot = 0;
    pw[0] = Hash(2);
    all_one[0] = Hash(1);
    for (int i = 1; i <= M; i++) {
        all_one[i] = all_one[i-1] * pw[i-1] + all_one[i-1];
        pw[i] = pw[i-1] * pw[i-1];
    }  
    for (int i = 0; i <= M; i++) {
    	T[tot+1] = {all_one[i], tot, tot};
    	++tot;    
    }
}

inline void push_up(int o, int k) {
    int chl = T[o].l, chr = T[o].r;
    T[o].dat = T[chr].dat * pw[k-1] + T[chl].dat;
}

void set_bit(int &o, int last, int x, int val, int l = 0, int k = M) { // len=1<<k
	assert(val == 0 || val == 1);
    int r = l + (1 << k);
    o = ++tot;
    assert(tot < MEM);
    T[o] = T[last];
    if (k == 0) T[o].dat = Hash(val);
    else {
    	int mid = l + (1 << (k-1));
        if (x < mid) set_bit(T[o].l, T[last].l, x, val, l, k-1);
        else set_bit(T[o].r, T[last].r, x, val, mid, k-1);
        push_up(o, k);
    }
}

void wipe(int &o, int last, int L, int R, int val, int l = 0, int k = M) {
	int r = l + (1 << k);
    if (R <= l || r <= L) o = last;
    else if (L <= l && r <= R) {
    	if (val == 0) o = 0;
    	else o = k + 1;
    }
    else {
        o = ++tot;
        assert(tot < MEM);
        T[o] = T[last];
        int mid = (l + r) / 2;
        wipe(T[o].l, T[last].l, L, R, val, l, k-1);
        wipe(T[o].r, T[last].r, L, R, val, mid, k-1);
        push_up(o, k);
    }
}

int sign(int o, int k = M) {
    if (k == 0) return T[o].dat[0];
    return sign(T[o].r, k-1);
}

int compare(int u, int v, int l = 0, int k = M) {
    if (T[u].dat == T[v].dat) return 0;
   
    if (T[u].dat == Hash(0)) return -1;
    if (T[v].dat == Hash(0)) return 1;

	if (T[u].dat == T[k+1].dat) return 1;
	if (T[v].dat == T[k+1].dat) return -1;

    int c = compare(T[u].r, T[v].r, l + (1 << (k-1)),k-1);
    if (c != 0) return c;
    return compare(T[u].l, T[v].l, l, k-1);
}

int find_pos(int o, int x, int val, int l = 0, int k = M) { //-1 not found
    int r = l + (1 << k);
    assert(l < r);
    if (val == 0) {
   		if (T[o].dat == all_one[k]) return -1;
    	if (x <= l && T[o].dat == Hash(0)) return l;    
    }
    else {
		if (x <= l && T[o].dat == all_one[k]) return l;
		if (T[o].dat == Hash(0)) return -1;  
    }
 
    int mid = (l + r) / 2;
    if (x < mid) {
        int pos = find_pos(T[o].l, x, val, l, k-1);
        if (pos != -1) return pos;
    }

    return find_pos(T[o].r, x, val, mid, k-1);
}

typedef bitset<(1<<M)> Num;

void getNum(int o, Num &num, int l = 0, int k = M) {
	if (k == 0) {
		assert(T[o].dat[0] == 0 || T[o].dat[0] == 1);
		num[l] = T[o].dat[0];
	}
	else {
		getNum(T[o].l, num, l, k - 1);
		getNum(T[o].r, num, l + (1 << (k-1)), k-1);
	}
}


struct BigNum{
    int root;
    explicit BigNum(int root = 0):root(root) {}
    BigNum operator+(int x)const{
    	if (x == 0) return *this;
		int sign = 1;
        if (x < 0) x = -x, sign = 0;
        x--;
	    int pos = find_pos(root, x, sign^1);
        if (pos == -1) pos = 1 << M;
	    int o = root;
	    if (pos < (1 << M)) set_bit(o, o, pos, sign);
	    if (x < pos) wipe(o, o, x, pos, sign^1);
	    return BigNum(o);    	
    }
    bool operator<(const BigNum &b)const{    
        int x = sign(root), y = sign(b.root);
        if (x != y) return x > y;
        return compare(root, b.root) < 0;
    }
    bool operator>(const BigNum&b) const{
        return b < *this;
    }
	Num get() const{
		Num num;
		getNum(root, num);
		return num;
	}
};

Num operator+(const Num&a, const Num&b){
	Num c;
	int carry = 0;
	for (int i = 0; i < (1 << M); i++) {
		carry += a[i];
		carry += b[i];
		c[i] = carry & 1;
		carry >>= 1;
	}
	return c;
}

void print(Num a) {
	if (a[(1<<M)-1] == 1) {
		int i = 0;
		while (i < (1 << M) && a[i] == 0) i++;
		for (int j = i + 1; j < (1 << M); j++) a.flip(j);
		printf("-");
	}
	int i = (1<<M)-1;
	while (i > 0 && a[i] == 0) --i;
	for (; i >= 0; i--) printf("%d", a[i] == 1 ? 1 : 0);
	puts("");
}

void Maxi(BigNum &a, const BigNum &b) {
	if (a < b) a = b;
}

int n,m;
vector<int> G[N], G2[N];

int a[N], qry[30], fa[N];
BigNum f[N], g[N];
void dfs(int v, int p) {
    fa[v] = p;
	for (auto u: G[v]) {
		if (u == p) continue;
		G2[v].push_back(u);
		dfs(u,v);
		Maxi(f[v], f[u]);
	}
	f[v] = f[v] + a[v];
}

void dfs2(int v) {
	BigNum tmp;
	for (auto u: G2[v]) {
		Maxi(g[u], tmp);
		Maxi(tmp, f[u]);
	}
    tmp = BigNum(0);
    for (int i = G2[v].size() - 1; i >= 0; i--) {
        int u = G2[v][i];
		Maxi(g[u], tmp);
		Maxi(tmp, f[u]);        
    }

	for (auto u: G2[v]) {
        g[u] = g[u] + a[v];
        Maxi(g[u], g[v] + a[v]);
        Maxi(g[u], BigNum(0));
		dfs2(u);
	}
}

int main() {
    init();
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a+i);
    for (int i = 0; i < n - 1; i++) {
    	int u,v;
    	scanf("%d%d", &u, &v);
    	G[u].push_back(v);
    	G[v].push_back(u);
    }
    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
    	scanf("%d", qry+i);
    }
    int root = qry[0];
    dfs(root, -1);
    dfs2(root);
    vector<BigNum> vec;
    for (int i = 0; i < q; i++) {
        int v = qry[i];
        vec.clear();
        for (auto u: G[v]) {
            if (u == fa[v] && BigNum(0) < g[v]) vec.push_back(g[v]);
            if (u != fa[v] && BigNum(0) < f[u]) vec.push_back(f[u]);
        }
        if (vec.size() > 4) partial_sort(vec.begin(), vec.begin() + 4, vec.end(), greater<BigNum>());
        Num ans;
        ans = ans + (BigNum(0)+a[v]).get();
        for (int j = 0; j < 4 && j < vec.size(); j++) {
            ans = ans + vec[j].get(); 
        }
        print(ans);
    }
}