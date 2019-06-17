#include<bits/stdc++.h>
#define maxn 405
#define maxm maxn*maxn
using namespace std;
typedef long long LL;

int n,modu;
LL F[maxn]={1},I[maxn]={1,1};
LL pw[maxm]={1},h[maxn][maxn];
LL f[maxn][maxn],g[maxn][maxn];

int C2(int n)   {   return n*(n-1)/2;   }
LL C(int n,int m)   {   return n<m?0:F[n]*I[m]%modu*I[n-m]%modu;    }
LL inv(LL x)    {   return F[x-1]*I[x]%modu;    }
void add(LL &x,LL y)    {   x=(x+y)%modu;   }
int main()  {
    scanf("%d%d",&n,&modu);
    for (int i=1;i<maxm;++i)    pw[i]=pw[i-1]*2%modu;
    for (int i=0;i<=n;++i)
        for (int j=h[i][0]=1;j<=n;++j)
            h[i][j]=h[i][j-1]*(pw[i]-1+modu)%modu;
    for (int i=1;i<=n;++i)  F[i]=F[i-1]*i%modu;
    for (int i=2;i<=n;++i)  I[i]=modu-modu/i*I[modu%i]%modu;
    for (int i=1;i<=n;++i)  I[i]=I[i]*I[i-1]%modu;
    
    for (int i=1;i<n;++i)   {
        g[i][i]=pw[C2(i)];
        f[i][i]=g[i][i]*i%modu;
        for (int j=1;j<i;++j)  {
            for (int k=1;k<=i-j;++k)    {
                LL t=h[j][k]*C(i,j)%modu;
                add(g[i][j],g[i-j][k]*t);
                add(f[i][j],f[i-j][k]*t+g[i-j][k]*t%modu*i);
            }
            g[i][j]=g[i][j]*pw[C2(j)]%modu;
            f[i][j]=f[i][j]*pw[C2(j)]%modu;
        }
        // for (int j=1;j<=i;++j)
        //     printf("f[%d][%d]=%lld g[%d][%d]=%lld\n",i,j,f[i][j],i,j,g[i][j]);
    }
    LL ans=0;
    for (int i=0;i<n;++i)
        add(ans,f[n-1][i]);
    printf("%lld\n",ans*inv(n-1)%modu);
    return 0;
}
