#include <bits/stdc++.h>
using namespace std;
const int N = 220;
const int K = 8;
typedef long long ll;
int gcd(int x, int y) {
    return y == 0 ? x : gcd(y, x % y);
}
int Log2[N]={-1};

int ST[K][N];

void init(int* a, int n) {
    for (int i = 0; i < n; i++) ST[0][i] = a[i];
    for (int j = 1; (1 << j) <= n; j++)
        for (int i = 0; i+(1<<(j-1)) < n; i++)
            ST[j][i] = gcd(ST[j-1][i], ST[j-1][i+(1<<(j-1))]);
}

int Gcd_range(int l, int r) { //[l, r]
    assert(l<=r);
    int t = Log2[r-l+1];
    return gcd(ST[t][l], ST[t][r-(1<<t)+1]);
}

int a[N][N], b[N][N][N];
int n,m,x,y;

void Maxi(ll &a, ll b) {
    if (a < b) a = b;
}

ll solve() {



    ll res = 0;
    for (int i = 0, j = 0; i < m; i++) {
        if (j < i) j = i;
        while (j < m && Gcd_range(i, j) != 1) j++;
        Maxi(res, j-i);
    }
    return res;
}

int main() {
    for (int i = 1; i < N; i++) Log2[i] = Log2[i>>1] + 1;
    
    scanf("%d%d%d%d", &n, &m, &x, &y);
    int g = 0;
    for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
        scanf("%d", &a[i][j]), g = gcd(g, a[i][j]);
    
    if (g != 1) {
        printf("%lld\n", 1LL*n*m*x*y);
        return 0;
    }

    int n_ = n, m_ = m;

    n = min(2, x) * n;
    m = min(2, y) * m;

    for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
        a[i][j] = a[i%n_][j%m_];
    

    ll ans = 0;

    for (int j = 0; j < m; j++)
    for (int st = 0; st < n; st++) {
        b[st][st][j] = a[st][j];
        for (int ed = st + 1; ed < n; ed++)
            b[st][ed][j] = gcd(b[st][ed-1][j], a[ed][j]);
    }

    for (int st = 0; st < n; st++)
    for (int ed = st; ed < n; ed++) {
        init(b[st][ed], m);
        ll len_n = ed - st + 1;

        ll len_m = solve();
        if (len_n >= n_) len_n = n_ * x;
        if (len_m >= m_) len_m = m_ * y;
        Maxi(ans, len_n * len_m);
    }
    


    printf("%lld\n", ans);
    


}