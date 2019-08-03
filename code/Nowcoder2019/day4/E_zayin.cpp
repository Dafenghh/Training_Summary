#include<bits/stdc++.h>
#define maxn 62
#define modu 998244353
using namespace std;
typedef long long LL;
  
LL n,a;
  
LL C[maxn][maxn];
  
LL con[maxn][maxn];
LL ca[maxn][3],cb[maxn][3];
  
LL pw(LL a,LL k)    {
    LL ans=1;
    for (a%=modu;k;k>>=1)  {
        if (k&1)
            ans=ans*a%modu;
        a=a*a%modu;
    }
    return ans;
}
  
void add(LL &a,LL b)    {
    a=(a+b)%modu;
}
  
void predo()    {
    for (int i=C[0][0]=1;i<maxn;++i)
        for (int j=C[i][0]=1;j<=i;++j)
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%modu;
    for (int a=0;a<maxn;++a)
        for (int i=0;i<=a;++i)  {
            add(ca[a][i%3],C[a][i]);
        }
    for (int b=0;b<maxn;++b)
        for (int j=0;j<=b;++j)  {
            add(cb[b][(j<<1)%3],C[b][j]);
        }
    for (int a=0;a<maxn;++a)
        for (int b=0;b<maxn;++b)
            for (int i=0;i<3;++i)
                add(con[a][b],ca[a][i]*cb[b][(3-i)%3]);
}
  
LL A,B;
  
void init() {
    scanf("%lld%lld",&n,&a);
    A=0,B=0;
    for (int i=0;i<maxn;++i)
        if (a>>i&1) {
            if (i&1)
                ++B;
            else
                ++A;
        }
}
  
LL sgn(LL x)    {
    return x&1?modu-1:1;
}
  
void solve()    {
    LL ans=0;
    for (int a=0;a<=A;++a)
        for (int b=0;b<=B;++b)  {
            LL t=C[A][a]*C[B][b]%modu*pw(con[a][b],n)%modu;
            // cout<<a<<" "<<b<<" "<<t<<" "<<sgn(A+B-a-b)*t<<endl;
            add(ans,sgn(A+B-a-b)*t);
        }
    printf("%lld\n",ans);
}
  
int main()  {
    predo();
    int T;
    scanf("%d",&T);
    while (T--) {
        init();
        solve();
    }
    return 0;
}
