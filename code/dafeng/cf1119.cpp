#include <bits/stdc++.h>
using namespace std;

const int N = 1e6+10;
int hp[N], a[N];
int main() {
    int n,m,tot=0;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d", hp + i);
        tot+=hp[i];
        a[i] = (a[i-1] + hp[i]) % n;
    }
    int ans = (tot+n-1)/n;
    printf("%d\n",ans);
    a[m] = n;
    sort(a+1, a+m+1);
    for (int i = m; i >= 1; i--) {
        a[i] -= a[i-1];
    }
    for (int i = 1; i <= m; i++) {
        printf("%d%c", a[i], " \n"[i==m]);
    }
    int cnt = 0;
    for (int i = 1, v=1; i <= m; i++) {
        while (hp[i]>0 || i==m && v!=1) {
            hp[i] -= a[v];
            printf("%d%c", i, " \n"[v==m]);
            v++;
            if (v > m) v = 1, cnt++; 
        }
    }   
    assert(cnt == ans);
}