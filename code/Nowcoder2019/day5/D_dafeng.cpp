#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5+10;
const int K = 63;
const int INF = 1e9+7;
  
int occ[N];
struct Seq{
    int num[N],a,b,p,pos,len;
  
    void calc() {
        for (int i = 1; i < N; i++) num[i] = (1LL*a*num[i-1]+b)%p;
        memset(occ, -1, sizeof occ);
        for (int i = 0; i < N; i++) {
            if (occ[num[i]] == -1) occ[num[i]] = i;
            else{
                pos = i;
                len = i-occ[num[i]];
                return;
            }
        }
    }
  
    int operator[](int i) {
        return num[i];
    }
  
}X,Y;
  
  
ll n;
  
int Min[N], Max[N];
  
void Mini(int &a, int b) {
    if (b < a) a = b;
}
  
void Maxi(int &a, int b) {
    if (a < b) a = b;
}
  
int a[N], min_nxt[K][N], max_nxt[K][N];
  
struct P {
    int x,y;
    P() {}
    P(int x, int y):x(x),y(y){}
    P operator+(const P&b) const {
        return P(x+b.x, y+b.y);
    }
    P operator-(const P&b) const {
        return P(x-b.x, y-b.y);
    }
    ll det(const P &b) const {
        return 1LL*x*b.y-1LL*y*b.x;
    }
    bool operator<(const P&b)const {
        return x<b.x || x == b.x && y < b.y;
    }
};
  
vector<P> convex(P *ps, int n) {
    sort(ps, ps+n);
    int k = 0;
    vector<P> qs(n*2);
    for (int i = 0; i < n; i++) {
        while (k > 1 && (qs[k-1] - qs[k-2]).det(ps[i]-qs[k-1]) <= 0) k--;
        qs[k++] = ps[i];
    }
    for (int i = n-2, t=k; i>=0; i--) {
        while (k > t && (qs[k-1] -qs[k-2]).det(ps[i]-qs[k-1]) <= 0) k--;
        qs[k++] =  ps[i];
    }
    qs.resize(k-1);
    return qs;
}
  
P ps[N*2];
  
  
int main() {
    for (int i = 0; i < N; i++) {
        Min[i] = INF;
        Max[i] = -INF;
    }
    scanf("%d%d%d%d%d%d%d%d%lld", &X.num[0], &Y.num[0], &X.a,&Y.a,&X.b,&Y.b,&X.p,&Y.p, &n);
      
    X.calc();
    Y.calc();
  
    if (X.len > Y.len) swap(X, Y);
  
    int pos = max(X.pos, Y.pos);
     
    if (n < pos) {
        for (int i = 0; i < n; i++) {
            Mini(Min[X[i]], Y[i]);
            Maxi(Max[X[i]], Y[i]);
        }
    }
    else {
        for (int i = 0; i < pos; i++) {
            Mini(Min[X[i]], Y[i]);
            Maxi(Max[X[i]], Y[i]);
        }
         
     
        a[0] = Y[pos];
        for (int i = 1; i < Y.len; i++) {
            a[i] = (1LL*Y.a*a[i-1]+Y.b)%Y.p;
        }
     
        for (int i = 0; i < Y.len; i++) {
            min_nxt[0][i] = max_nxt[0][i] = a[i];
        }
     
        for (int k = 1; k < K; k++) {
            for (int i = 0; i < Y.len; i++) {
                min_nxt[k][i] = min(min_nxt[k-1][i], min_nxt[k-1][(i+(1LL<<k-1)%Y.len*X.len)%Y.len]);
                max_nxt[k][i] = max(max_nxt[k-1][i], max_nxt[k-1][(i+(1LL<<k-1)%Y.len*X.len)%Y.len]);
            }
        }
     
        a[0] = X[pos];
     
        for (int i = 1; i < X.len; i++) {
            a[i] = (1LL*X.a*a[i-1]+X.b)%X.p;
        }
     
        for (int i = 0; i < X.len; i++) {
            if (n-pos-i-1<0) break;
            ll k = (n-pos-i-1)/X.len;
            if (k < 0) continue;
     
            ++k;
     
            int x = i%Y.len;
     
            for (int j = K-1; j >= 0; j--) {
                if (k >> j & 1) {
                    Mini(Min[a[i]], min_nxt[j][x]);
                    Maxi(Max[a[i]], max_nxt[j][x]);
                    x = (x + (1LL<<j)%Y.len*X.len)%Y.len;
                }
            }
        }
    }
 
 
  
    int sz = 0;
  
    for (int i = 0; i < N; i++) {
        if (Min[i] != INF) {
            ps[sz++] = P(i, Min[i]);
            ps[sz++] = P(i, Max[i]);
        }
    }
  
    vector<P> qs = convex(ps, sz);
  
    qs.push_back(qs[0]);
  
    ll ans = 0;
  
    for (int i = 0; i < qs.size()-1; i++) {
        ans += qs[i].det(qs[i+1]);
    }
  
  //  ans/=2;
    printf("%lld\n", abs(ans));
  
  
}
