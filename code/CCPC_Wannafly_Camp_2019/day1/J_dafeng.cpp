#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
const int N = 1e5+10;
int n, m, sz;
int nums[N], id[N];
P a[N];
queue<int> que[N];
void Mini(ll &a, ll b) {
    if (b < a) a = b;
}

struct node{
    int cnt;
    ll tot;
}T[4*N];

void add(int x, int c, int v = 0, int l = 0, int r = sz) {
    T[v].cnt += c;
    T[v].tot += nums[x] * c;
    if (l + 1 == r) return;
    int mid = (l + r) / 2, chl = v * 2 + 1, chr = v * 2 + 2;
    if (x < mid) add(x, c, chl, l, mid);
    else add(x, c, chr, mid, r);
}

ll query(ll k, int v = 0, int l = 0, int r = sz) {
    if (l + 1 == r) return 1LL * k * nums[l];
    int mid = (l + r) / 2, chl = v * 2 + 1, chr = v * 2 + 2;
    if (T[chl].cnt >= k) return query(k, chl, l, mid);
    return T[chl].tot + query(k - T[chl].cnt, chr, mid, r);
}


int main() {
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++) {
        int x,y;
        scanf("%d%d", &x, &y);
        a[i] = P(x, y);
        nums[i] = x;
    }
    
    sort(nums, nums + m);
    sz = unique(nums, nums + m) - nums;

    sort(a, a + m);
    for (int i = 0; i < m; i++) {
        int x = a[i].first, c = a[i].second;
        x = lower_bound(nums, nums + sz, x) - nums; 
        que[c].push(x);
        add(x, 1);
    }

    for (int i = 1; i <= n; i++) id[i] = i;
    sort(id + 1, id + n + 1, [&](int x, int y)->bool{
        return que[x].size() > que[y].size();
    });

    int cnt = 0;
    ll tot = 0, ans = 1e18;
    for (int h = que[id[1]].size(); h >= 0; h--) {
        
        for (int j = 1; j <= n; j++) {
            int i = id[j];
            if (que[i].size() <= h) break;
            while (que[i].size() > h) {
                int x = que[i].front();
                que[i].pop();
                add(x, -1);
                ++cnt;
                tot += nums[x];
            }
        }

        if (cnt > h) Mini(ans, tot);
        else {
            int rest = h + 1 - cnt;
            if (T[0].cnt >= rest) Mini(ans, tot + query(rest));
        }
    }
    printf("%lld\n", ans);
}