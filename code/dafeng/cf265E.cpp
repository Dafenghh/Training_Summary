#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+10;
const int M = 1 << 22;
const int K = 2;
const int Mod[K] = {(int)1e9+7, (int)1e9+9};

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

Hash all_one[M+1], pw[M+1];


struct node{
    Hash dat;
    int l,r;
}T[M*6];

int tot = 0;

inline void push_up(int o, int l, int r) {
    int mid = (l + r) / 2, chl = T[o].l, chr = T[o].r;
    T[o].dat = T[chr].dat * pw[mid-l] + T[chl].dat;
}

void set_bit(int &o, int last, int x, int l = 0, int r = M) {
    o = ++tot;
    T[o] = T[last];
    if (l + 1 == r) T[o].dat = Hash(1);
    else {
        int mid = (l + r) / 2;
        if (x < mid) set_bit(T[o].l, T[last].l, x, l, mid);
        else set_bit(T[o].r, T[last].r, x, mid, r);
        push_up(o, l, r);
    }
}

void wipe(int &o, int last, int L, int R, int l = 0, int r = M) {
    if (R <= l || r <= L) o = last;
    else if (L <= l && r <= R) o = 0;
    else {
        o = ++tot;
        T[o] = T[last];
        int mid = (l + r) / 2;
        wipe(T[o].l, T[last].l, L, R, l, mid);
        wipe(T[o].r, T[last].r, L, R, mid, r);
        push_up(o, l, r);
    }
}

int compare(int u, int v) {
    if (T[u].dat == T[v].dat) return 0;
    if (T[u].dat == Hash(0)) return -1;
    if (T[v].dat == Hash(0)) return 1;

    int c = compare(T[u].r, T[v].r);
    if (c != 0) return c;
    return compare(T[u].l, T[v].l);
}

int find_zero(int o, int x, int l = 0, int r = M) { //-1 not found
    //cerr << "find: " << x << " " << l << " " << r << endl;
    assert(l < r);
    if (T[o].dat == all_one[r-l]) return -1;
    if (x <= l && T[o].dat == Hash(0)) return l;
    int mid = (l + r) / 2;
    if (x < mid) {
        int pos = find_zero(T[o].l, x, l, mid);
        if (pos != -1) return pos;
    }

    return find_zero(T[o].r, x, mid, r);
}

struct BigNum{
    int root;
    explicit BigNum(int root = 0):root(root) {}
    BigNum operator+(int x)const{ // + 1<<x
        int pos = find_zero(root, x);
        //cerr << "pos: " << pos << endl;
        int o;
        set_bit(o, root, pos);
        //cerr << "set bit ok" << endl;
        wipe(o, o, x, pos);
        return BigNum(o);
    }
    bool operator<(const BigNum &b)const{
        return compare(root, b.root) < 0;
    }
    void print() const{
        printf("%d\n",T[root].dat[0]); 
    }
};


void init() {
    pw[0] = Hash(1);
    for (int i = 1; i <= M; i++) {
        all_one[i] = all_one[i-1] * Hash(2) + Hash(1);
        pw[i] = pw[i-1] * Hash(2);
    }  
}

int n,m;

struct edge{
    int to, cost;
};
vector<edge> G[N];
typedef pair<BigNum, int> P;

BigNum d[N];
int Prev[N];

int main() {
    init();
   
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u,v,x;
        scanf("%d%d%d", &u, &v, &x);
        G[u].push_back({v, x});
        G[v].push_back({u, x});
    }
    int s,t;
    scanf("%d%d", &s, &t);
    memset(Prev, -1, sizeof Prev);
    priority_queue<P, vector<P>, greater<P> > que;
    d[s] = BigNum(0);
    Prev[s] = 0;
    que.push(P(d[s], s));
    while (!que.empty()) {
        P p = que.top(); que.pop();
        int v = p.second;
        if (d[v] < p.first) continue;
        for (auto &e: G[v]) {
            int u = e.to;
            BigNum cost = d[v] + e.cost;
            if (Prev[u] == -1 || cost < d[u]) {
                d[u] = cost;
                Prev[u] = v;
                que.push(P(d[u], u));
            }
        }
    }
    
    if (Prev[t] == -1) puts("-1");
    else {
        d[t].print();
        vector<int> path;
        int v = t;
        while (v != s) {
            assert(v > 0);
            path.push_back(v);
            v = Prev[v];
        }
        path.push_back(s);
        reverse(path.begin(), path.end());
        printf("%d\n", path.size());
        for (auto v: path) printf("%d ", v);
        puts("");
    }


}