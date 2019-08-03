#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+10;
const int M = 1e9;
 
int a[N], b[N], X[N], Y[N], n, id[N], num[N], sz;
 
typedef long long ll;
const ll INF = 1e18+7;
int Shrink(int a[]) {
    for (int i = 0; i < n; i++) num[i] = a[i];
    sort(num, num+n);
    int sz = unique(num, num+n)-num;
    for (int i = 0; i < n; i++) a[i] = lower_bound(num, num+sz, a[i]) - num + 1;
    return sz;
}
 
struct Node {
    ll Max, tag;
}T[N*4];
 
#define Max(v) T[v].Max
#define tag(v) T[v].tag
 
void add_val(int v, ll val) {
    Max(v) += val;
    tag(v) += val;
}
 
void push_down(int v) {
    int chl = v * 2 + 1, chr = v * 2 + 2;
    if (tag(v)) {
        add_val(chl, tag(v));
        add_val(chr, tag(v));
        tag(v) = 0;
    }
}
 
void push_up(int v) {
    int chl = v * 2 + 1, chr = v * 2 + 2;
    Max(v) = max(Max(chl), Max(chr));
}
 
void add(int L, int R, ll val, int v = 0, int l = 0, int r = sz+1) {
    if (r <= L || R <= l) return;
    if (L <= l && r <= R) {
        add_val(v, val);
        return;
    }
 
    push_down(v);
    int mid = (l+r)/2, chl = v*2+1, chr=v*2+2;
    add(L,R,val, chl, l, mid);
    add(L,R,val, chr, mid, r);
    push_up(v);
}
 
ll query(int L, int R, int v = 0, int l = 0, int r = sz+1) {
    if (r <= L || R <= l) return -INF;
    if (L <= l && r <= R) return Max(v);
    push_down(v);
    int mid = (l+r)/2, chl = v*2+1, chr=v*2+2;
    return max(query(L, R, chl, l, mid), query(L, R, chr, mid, r));
}
 
void change(int x, ll val, int v = 0, int l = 0, int r = sz+1) {
    if (l + 1 == r) {
        Max(v) = val;
        return;
    }
    push_down(v);
    int mid = (l+r)/2, chl = v*2+1, chr=v*2+2;
    if (x < mid) change(x, val, chl, l, mid);
    else change(x, val, chr, mid, r);
    push_up(v);
}
 
void build(int v = 0, int l = 0, int r = sz+1) {
    Max(v) = tag(v) = 0;
    if (l + 1 == r) return;
    int mid = (l+r)/2, chl = v*2+1, chr=v*2+2;
    build(chl, l, mid);
    build(chr, mid, r);
}
 
void solve() {
     
    for (int i = 0; i < n; i++) scanf("%d%d%d%d", X+i, Y+i,a+i, b+i ), id[i] = i;
     
    sz = Shrink(Y);
     
    build();
    sort(id, id+n, [&](int i, int j) {
        return X[i] < X[j] || X[i] == X[j] && Y[i] < Y[j];
    });
 
    for (int l = 0, r = 0; l < n; l = r) {
        while (r < n && X[id[r]] == X[id[l]]) ++r;
        for (int k = l; k < r; k++) {
            int i = id[k];
            ll pre = query(0, Y[i] + 1);
            change(Y[i], pre);
        }
        for (int k = l; k < r; k++) {
            int i = id[k];
            add(0, Y[i], a[i]);
            add(Y[i], sz+1, b[i]);
        }
    }
    printf("%lld\n", query(0,sz+1));
}
 
 
int main() {
    while(scanf("%d", &n) != EOF) {
        solve();
    }
 
}