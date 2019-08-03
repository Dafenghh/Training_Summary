#include <bits/stdc++.h>
using namespace std;
const int N = 3e6+10;
const int K = 22;
typedef long long ll;
const ll INF = 1e18+7;
int n, Log2[N];
  
struct RMQ_min {
    ll dat[4*N];
    ll*a;
  
    ll query(int L, int R, int v = 0, int l = 0, int r = n + 1) {
        if (R <= l || r <= L) return INF;
        if (L <= l && r <= R) return dat[v];
        int mid = (l + r) / 2, chl = v * 2 + 1, chr = v * 2 + 2;
        return min(query(L, R, chl, l, mid), query(L, R, chr, mid, r));
    }
  
    ll operator()(int l, int r) {
        return query(l, r+1);
    }
  
    void init(int v = 0, int l = 0, int r = n + 1) {
        if (l + 1 == r) {
            dat[v] = a[l];
            return;
        }
        int mid = (l + r) / 2, chl = v * 2 + 1, chr = v * 2 + 2;
        init(chl, l, mid);
        init(chr, mid, r);
        dat[v] = min(dat[chl], dat[chr]);
    }
  
    void build(ll*num) {
        a = num;
        init();
    }
}Sum_min;
  
struct ST_min {
    int st[K][N];
    ll*a;
    int Min(int i, int j) {
        return a[i] < a[j] ? i : j;
    }
   
    int operator()(int l, int r) {
        int t = Log2[r-l+1];
        return Min(st[t][l], st[t][r-(1<<t)+1]);
    }
   
    void build(ll*num) {
        a = num;
        for (int i = 0; i <= n; i++) st[0][i] = i;
   
        for (int t = 1; t < K; t++)
        for (int i = 0; i+(1<<(t-1)) <= n; i++)
            st[t][i] = Min(st[t-1][i], st[t-1][i+(1<<(t-1))]);   
    }
}A;
  
  
struct RMQ_max {
    ll dat[4*N];
    ll*a;
  
    ll query(int L, int R, int v = 0, int l = 0, int r = n + 1) {
        if (R <= l || r <= L) return -INF;
        if (L <= l && r <= R) return dat[v];
        int mid = (l + r) / 2, chl = v * 2 + 1, chr = v * 2 + 2;
        return max(query(L, R, chl, l, mid), query(L, R, chr, mid, r));
    }
  
    ll operator()(int l, int r) {
        return query(l, r+1);
    }
  
    void init(int v = 0, int l = 0, int r = n + 1) {
        if (l + 1 == r) {
            dat[v] = a[l];
            return;
        }
        int mid = (l + r) / 2, chl = v * 2 + 1, chr = v * 2 + 2;
        init(chl, l, mid);
        init(chr, mid, r);
        dat[v] = max(dat[chl], dat[chr]);
    }
  
    void build(ll*num) {
        a = num;
        init();
    }
}Sum_max;
  
  
  
  
ll sum[N], a[N], b[N];
  
ll ans = 0;
void Maxi(ll &a, ll b) {
    if (b > a) a = b;
}
void solve(int l, int r) {
    if (l > r) return;
  
    int k = A(l, r);
  //  printf("A(%d %d): %d\n", l,r,k);
  
    if (a[k] > 0) {
        ll x = Sum_min(l-1, k-1);
        ll y = Sum_max(k, r);
     //   printf("Sum_min(%d %d): %d\n", l-1,k-1,x);
      //  printf("Sum_max(%d %d): %d\n", k,r, y);
        Maxi(ans, a[k]*(y-x));
    }
    else if  (a[k] < 0) {
        ll x = Sum_max(l-1, k-1);
        ll y = Sum_min(k, r);
        Maxi(ans, a[k]*(y-x));      
    }
    else Maxi(ans, 0);
  
    solve(l, k-1);
    solve(k+1, r);
}
void init() {
    Log2[0] = -1;
    for (int i = 1; i < N; i++) Log2[i] = Log2[i/2] + 1;
}
const int maxn=1<<20;
char pool[maxn],*head=pool,*tail=pool;
#define getc() (head==tail&&(tail=(head=pool)+fread(pool,1,maxn,stdin),head==tail)?0:*head++)
#define isd(c) (c>='0'&&c<='9')
long long read(){
    ll x=0,f=1; char ch=getc();
    while (!isd(ch)) {if (ch=='-') f=-1; ch=getc();}
    while (isd(ch)) {x=x*10+ch-'0'; ch=getc();}
    return x*f;
}
 
void solve() {
//    scanf("%d", &n);
    n=read();
    for (int i = 1; i <= n; i++) a[i]=read();
    for (int i = 1; i <= n; i++) b[i]=read(), sum[i] = sum[i-1] + b[i];
  
  //  int st = clock();
    A.build(a);
  //  int ed = clock();
 //   printf("%d\n", ed-st);
    Sum_min.build(sum);
    Sum_max.build(sum);
    ans = -INF;
  
    solve(1, n);
      
    printf("%lld\n", ans);
}
  
  
int main() {
    //freopen("in.txt","r",stdin);
    init();
    solve();
}
