#include<bits/stdc++.h>
#define maxn 550
using namespace std;
typedef long long LL;

int n,modu;

void add(LL &x,LL y)  {
    x=(x+y)%modu;
}

LL F[maxn]={1},I[maxn],V[maxn];
LL dp[maxn][maxn],t[maxn],p[maxn];

LL pw(LL a,LL k=modu-2) {
    LL ans=1;
    for (;k;k>>=1)  {
        if (k&1)
            ans=ans*a%modu;
        a=a*a%modu;
    }
    return ans;
}

LL Dp(int c,int n)   {
    return !c?dp[c][n]:(dp[c][n]-dp[c-1][n]+modu)%modu;
}

LL C(int n,int m)   {
    return n<m?0:F[n]*I[m]%modu*I[n-m]%modu;
}

LL calc0(int c)   {
    if (!c) return n==1;
    LL ans=0;
    for (int k=1;k<n;++k)
        add(ans,Dp(c-1,k)*dp[c-1][n-k]%modu*C(n,k));
    return (Dp(c,n)-ans+modu)%modu;
}

LL calc1(int c)   {
    if (!c) return n==2;
    LL ans=0;
    for (int k=1;k<n;++k)
        add(ans,Dp(c,k)*Dp(c,n-k)%modu*C(n-1,k-1));
    return ans;
}

int main()
{
    scanf("%d%d",&n,&modu);

    for (int i=1;i<=n;++i)  F[i]=F[i-1]*i%modu;
    I[n]=pw(F[n]);
    for (int i=n;i;--i) I[i-1]=I[i]*i%modu;
    for (int i=2;i<=n;++i)  V[i]=i*F[i-2]%modu;

    for (int j=0;j<=n;++j)   dp[j][1]=1;
    for (int j=1;j<=n;++j)  {
        for (int k=1;k<=n;++k)  t[k]=dp[j-1][k]*I[k-1]%modu;
        for (int i=1;i<=j;++i)  p[i]=(dp[j][i]=dp[j-1][i])*I[i]%modu;
        for (int i=j+1;i<=n;++i) {
            for (int k=1;k<i;++k)
                add(dp[j][i],p[i-k]*t[k]);
            dp[j][i]=dp[j][i]*V[i]%modu;
            p[i]=dp[j][i]*I[i]%modu;
		}
    }
    for (int c=0;2*c<n;++c) {
        printf("%lld ",calc0(c));
        if (2*c+1<n)
            printf("%lld ",calc1(c));
    }
    return 0;
}
