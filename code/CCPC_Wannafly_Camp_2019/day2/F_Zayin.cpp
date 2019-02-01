#include<bits/stdc++.h>
#define maxn 1000050
#define modu 998244353
using namespace std;
typedef long long LL;

bool noprime[maxn];
int p[maxn],pnum;

LL mu[maxn];
LL s1[maxn],s2[maxn];

map<int,LL> S1,S2;

void predo()
{
    mu[1]=1;
    for (int i=2;i<maxn;++i)
    {
        if (!noprime[i])
            mu[p[pnum++]=i]=-1;
        for (int j=0;j<pnum&&i*p[j]<maxn;++j)
        {
            noprime[i*p[j]]=1;
            if (i%p[j])
                mu[i*p[j]]=-mu[i];
            else
                break;
        }
    }
    for (int i=1;i<maxn;++i)
        for (int j=i;j<maxn;j+=i)
            s2[j]+=mu[i]*mu[j/i];
    for (int i=1;i<maxn;++i)
        s1[i]=(s1[i-1]+modu+mu[i])%modu,s2[i]=(s2[i]+modu+s2[i-1])%modu;
    for (int i=1;i<maxn;++i)
        if (s1[i]<0||s2[i]<0)
            cout<<i<<" "<<s1[i]<<" "<<s2[i]<<endl;
}

LL Sum1(LL n)
{
    if (n<maxn) return s1[n];
    if (S1.count(n))    return S1[n];
    LL s=1;
    for (LL i=2,j;i<=n;i=j+1)
    {
        j=n/(n/i);
        s=(s+modu-Sum1(n/i)*(j-i+1)%modu)%modu;
    }
    return S1[n]=s;
}

LL Sum2(LL n)
{
    if (n<maxn) return s2[n];
    if (S2.count(n))    return S2[n];
    LL s=Sum1(n);
    for (LL i=2,j;i<=n;i=j+1)
    {
        j=n/(n/i);
        s=(s+modu-Sum2(n/i)*(j-i+1)%modu)%modu;
    }
    return S2[n]=s;
}

int main()
{
    predo();

    LL n,ans=0;
    scanf("%lld",&n);
    for (LL i=1,j;i<=n;i=j+1)
    {
        j=n/(n/i);
        ans+=(n/i)%modu*(n/i)%modu*(Sum2(j)-Sum2(i-1)+modu)%modu;
        ans%=modu;
    }
    printf("%lld\n",ans);
    return 0;
}
