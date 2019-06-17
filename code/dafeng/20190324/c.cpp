#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int N = 1e6+10;

int h[N];
struct comp{
    bool operator()(const int &x, const int &y) const{
        return h[x] > h[y] || h[x] == h[y] && x < y;
    }
};
set<int, comp> S;
int n,q, L[N], R[N];

struct node{
    int val, tag;
    int code;
}T[N*4];

int cnt[N], hc[N];

#define val(v) T[v].val
#define tag(v) T[v].tag
#define code(v) T[v].code

void pushup(int v) {
    int chl = v * 2 + 1, chr = v * 2 + 2;
    val(v) = min(val(chl), val(chr));
}

void build(int v = 0, int l = 1, int r = n + 1) {
    if (l + 1 == r) {
        val(v) = cnt[l];
        code(v) = hc[l];
        tag(v) = 0;
    }
    else {
        int mid = (l + r) / 2, chl = v * 2 + 1, chr = v * 2 + 2;
        build(chl, l, mid);
        build(chr, mid, r);
        pushup(v);
        tag(v) = 0;
        code(v) = 0;
    }
}


void add_val(int v, int x, int c) {
    val(v) += x;
    tag(v) += x;
    assert(val(v) >= 0);
    code(v) ^= c;
}

void pushdown(int v) {
    if (tag(v) != 0) {
        int chl = v * 2 + 1, chr = v * 2 + 2;
        add_val(chl, tag(v), code(v));
        add_val(chr, tag(v), code(v));
        tag(v) = 0;
        code(v) = 0;
    }
}

void update(int i) {
    assert(i >= 1 && i <= q && S.count(i));
    S.erase(i);
    h[i]++;
    S.insert(i);
}

void modify(int L, int R, int i, int v = 0, int l = 1, int r = n + 1) {
    if (R <= l || r <= L) return;
    if (l + 1 == r) {
        add_val(v, -1, i);
        if (val(v) == 1) update(code(v));
        return;
    }
    if (L <= l && r <= R && val(v) > 2) {
        add_val(v, -1, i);
        return;
    }

    int mid = (l + r) / 2, chl = v * 2 + 1, chr = v * 2 + 2;
    pushdown(v);
    modify(L, R, i, chl, l, mid);
    modify(L, R, i, chr, mid, r);
    pushup(v);
}



void solve() {
    S.clear();
    scanf("%d%d", &n, &q);
    memset(h, 0, sizeof h);
    memset(hc, 0, sizeof hc);
    memset(cnt, 0, sizeof cnt);

    for (int i = 1; i <= q; i++) {
        scanf("%d%d", L+i, R+i);
        R[i]++;
        cnt[L[i]]++;
        cnt[R[i]]--;
        hc[L[i]] ^= i;
        hc[R[i]] ^= i;
    }

    for (int i = 1; i <= n; i++) {
        cnt[i] += cnt[i-1];
        hc[i] ^= hc[i-1];
        if (cnt[i] == 1) {
            assert(hc[i] >= 1 && hc[i] <= q);
            h[hc[i]]++;
        }
    }
    for (int i = 1; i <= q; i++) S.insert(i);

    build();

    int ans = n;
    for (int t = 0; t < q; t++) {
        int i = *S.begin();
        S.erase(i);
        ans = min(ans, h[i]);
        modify(L[i], R[i], i);
    }
    printf("%d\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    for (int Ti = 1; Ti <= T; Ti++) {
        printf("Case #%d: ", Ti);
        solve();
    }
}
