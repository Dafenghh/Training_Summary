#include<bits/stdc++.h>
#define maxn 20
#define maxm 105
#define maxs 1048576
#define modu 998244353
#define I2 499122177
using namespace std;
typedef long long LL;

const int num[]={1,0,2};

int n;
LL f[maxs],bit[maxs];

LL cnt[maxm];

LL sq(LL x)   {
    return x*x;
}

int main()
{
    scanf("%d",&n);
    for (int i=0;i<n;++i)
    {
        int s=0,x;
        for (int j=0;j<10;++j)
            scanf("%d",&x),s|=num[x]<<(j<<1);
        ++f[s];
    }

    for (int len=2;len<=maxs;len<<=1)
    {
        int m=len>>1;
        for (LL *p=f;p!=f+maxs;p+=len)
            for (int i=0;i<m;++i)
            {
                LL x=p[i],y=p[i+m];
                p[i]=(x+y)%modu;
                p[i+m]=(x-y+modu)%modu;
            }
    }

    for (int i=0;i<maxs;++i)
        f[i]=f[i]*f[i]%modu;
        
    for (int len=2;len<=maxs;len<<=1)
    {
        int m=len>>1;
        for (LL *p=f;p!=f+maxs;p+=len)
            for (int i=0;i<m;++i)
            {
                LL x=p[i],y=p[i+m];
                p[i]=(x+y)*I2%modu;
                p[i+m]=(x-y+modu)*I2%modu;
            }
    }

    for (int s=1;s<maxs;++s)    bit[s]=bit[s>>1]+(s&1);
    for (int s=0;s<maxs;++s)
    {
        int x=0;
        for (int i=0;i<10;++i)
            x+=sq(bit[s>>(i<<1)&3]);
        cnt[x]=(cnt[x]+f[s])%modu;
    }

    LL ans=0;
    for (int i=0;i<maxm;++i)
        ans=(ans+sq(cnt[i]))%modu;
    printf("%lld\n",ans);
    return 0;
}
