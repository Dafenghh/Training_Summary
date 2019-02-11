#include<bits/stdc++.h>
#define maxn 3050
#define modu 998244353
using namespace std;
typedef long long LL;

int n;

LL m,F2[maxn]={1};
LL F[maxn]={1},I[maxn];

LL pw(LL a,LL k)
{
    LL ans=1;
    for (;k;k>>=1)
    {
        if (k&1)
            ans=ans*a%modu;
        a=a*a%modu;
    }
    return ans;
}

LL C(int n,int m)
{
    return n<m?0:F[n]*I[m]%modu*I[n-m]%modu;
}

int main()
{
    for (int i=1;i<maxn;++i)
        F2[i]=F2[i-1]*2%modu;
    for (int i=1;i<maxn;++i)
        F[i]=F[i-1]*i%modu;
    I[maxn-1]=pw(F[maxn-1],modu-2);
    for (int i=maxn-1;i;--i)
        I[i-1]=I[i]*i%modu;
    
    int T;
    scanf("%d",&T);
    while (T--)
    {
        LL ans=0;
        scanf("%d%lld",&n,&m);
        for (int i=0;i<=n;++i)
        {
            LL sum=1LL*i*i+1LL*(n-i)*(n-i)-1LL*i*(n-i);
            // cout<<i<<" "<<sum<<endl;
            if (sum>=m)
                ans=(ans+C(n,i))%modu;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
