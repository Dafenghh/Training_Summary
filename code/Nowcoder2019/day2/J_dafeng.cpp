#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e7+10;
int tot[N], f[N], cur, st, ed;
ll ans = 0;
void Next() {
    if (cur == ed) {
        ed = (ed + 1) % N;
        assert(ed != st);
        f[ed] = 0;
        tot[ed] = 0;
    }
 
    int pre = cur;
    cur = (cur + 1) % N;
    f[cur] += f[pre] + 1;
    tot[cur] += f[pre];
    ans += tot[cur];
  
    f[pre] = 0;
}
  
bool Prev() {
    bool flag = false;
    if (cur == st) {
        st = (st + N - 1) % N;
        assert(ed != st);
        f[st] = 0;
        tot[st] = 0;
        flag = true;
    }
 
    int pre = cur;
    cur = (cur + N - 1) % N;
    f[cur]++;
    ans += tot[cur];
  
    return flag;
}
  
const int M = 1e6+10;
int L[M], R[M], sum[M], n;
  
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d%d", L+i, R+i);
    sum[n] = R[n] - L[n] + 1;
    for (int i = n - 1; i >= 1; i--) {
        sum[i] = R[i] - L[i] + 1;
        if (-(L[i+1]-R[i]-1) + sum[i+1] > 0) sum[i] += -(L[i+1]-R[i]-1) + sum[i+1];
    }
  
    f[cur] = 1;
    int rpos = 1e9;
    int i = 1, pos = 0;
  
    for (; pos < rpos;) {
        if (i <= n && pos == L[i]) {
            for (; pos <= R[i]; pos++) Next();
            ++i;
            continue;
        }
         
        if (Prev()) {
            if (i > n) break;
            if (L[i] - pos - 1 >= sum[i]) {
                pos = L[i]-sum[i];
                st = ed = cur = f[0] = tot[0] = 0;
                continue;
            }
        }     
        pos++;
  
    }
    printf("%lld\n", ans);  
}
