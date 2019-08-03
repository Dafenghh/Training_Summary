#include <bits/stdc++.h>
using namespace std;
 
const int N = 1e5+10;
 
struct Node {
    int son[2], val, rnd, sz, max;
}T[N];
int tot, root;
 
void update(int v) {
    int chl = T[v].son[0], chr = T[v].son[1];
    T[v].sz = T[chl].sz + T[chr].sz + 1;
    T[v].max = max({T[v].val, T[chl].max, T[chr].max});
}
 
int new_node(int val) {
    ++tot;
    T[tot].max = val;
    T[tot].val = val;
    T[tot].rnd = rand();
    T[tot].sz = 1;
    return tot;
}
 
int merge(int u, int v) { // u < v
    if (!u || !v) return u + v;
    if (T[u].rnd < T[v].rnd) {
        T[u].son[1] = merge(T[u].son[1], v);
        update(u);
        return u;
    } else {
        T[v].son[0] = merge(u, T[v].son[0]);
        update(v);
        return v;
    }
}
 
void split_max(int now, int k, int &u, int &v) { // <= k , > k
    if (!now) u = v = 0;
    else if (T[now].max <= k) {
        u = now;
        v = 0;
    } else {
        int &chl = T[now].son[0], &chr = T[now].son[1];
        if (T[chl].max > k) {
            v = now;
            split_max(chl, k, u, chl);
        } else if (T[now].val > k) {
            u = chl;
            v = now;
            chl = 0;
        } else {
            u = now;
            split_max(chr, k, chr, v);
        }
        update(now);
    }
}
 
void split_sz(int now, int k, int &u, int &v) {
    if (!now) u = v = 0;
    else if (T[now].sz <= k) {
        u = now;
        v = 0;
    } else {
        int &chl = T[now].son[0], &chr = T[now].son[1];
        if (k <= T[chl].sz) {
            v = now;
            split_sz(chl, k, u, chl);
        } else {
            k -= T[chl].sz + 1;
            u = now;
            split_sz(chr, k, chr, v);
        }
        update(now);
    }
}
 
int kth(int now, int k) {
    for (;;) {
        int chl = T[now].son[0], chr = T[now].son[1];
        if (k <= T[chl].sz) now = chl;
        else if (k == T[chl].sz + 1) return now;
        else {
            k -= T[chl].sz + 1;
            now = chr;
        }
    }
}
 
void query() {
    int i;
    scanf("%d", &i);
    printf("%d\n", T[kth(root, i)].val);
}
 
void change() {
    int l,m,r;
    scanf("%d%d%d", &l, &m, &r);
    int cnt = r - m, u, v;
    split_sz(root, m, u, v);
 
    while (cnt > 0 && v > 0) {
        int w = kth(v, 1);
        if (T[u].max < T[w].val) break;
        int u1, u2, v1, v2, v3;
        split_max(u, T[w].val, u1, u2);
        split_max(v, T[w].val, v1, v3);    
        split_sz(v1, cnt, v1, v2);
        cnt -= T[v1].sz;
        u = merge(merge(u1, v1), u2);
        v = merge(v2, v3);
    }
    root = merge(u, v);
}
 
 
int n,q;
int main() {
    srand(time(NULL));
     
    scanf("%d%d", &n, &q);
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        root = merge(root,new_node(x));
    }
 
    while (q--) {
        int op;
        scanf("%d", &op);
        if (op == 1) change();
        else query();
    }
 
}
