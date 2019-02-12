#include<bits/stdc++.h>
#define maxn 200050
#define modu 998244353
using namespace std;
typedef long long LL;

int n,m;
int a[maxn],p[maxn];

int L[maxn],R[maxn];

LL F[maxn],I[maxn];

LL inv(LL a)
{
    a%=modu;
    LL ans=1;
    for (int k=modu-2;k;k>>=1)
    {
        if (k&1)
            ans=ans*a%modu;
        a=a*a%modu;
    }
    return ans;
}

void init()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;++i)  scanf("%d",a+i);
    for (int i=1;i<=n;++i)  scanf("%d",p+i);

    sort(a+1,a+n+1);
    R[0]=1,L[n+1]=n;
    a[0]=0,a[n+1]=m+1;
    for (int i=1;i<=n;++i)
        L[i]=i-1,R[i]=i+1;
    
    F[0]=1;
    for (int i=1;i<=m;++i)  F[i]=F[i-1]*i%modu;
    I[m]=inv(F[m]);
    for (int i=m;i;--i) I[i-1]=I[i]*i%modu;
}

LL C(int n,int m)   {
    return n<m?0:F[n]*I[m]%modu*I[n-m]%modu;
}

LL calc(int i,int j)    {
    return C(a[j]-a[i]-1,j-i-1);
}

void solve()
{
    LL ans=0,s=1;
    for (int k=n;k;--k)
    {
        int i=p[k],l=L[i],r=R[i];
        s=s*inv(calc(l,i)*calc(i,r))%modu;

        LL res=0;
        int x=a[i]-a[l]-1,y=a[r]-a[i],t=r-l-1;
        if (i-l>r-i)
        {
            for (int j=i-l;j<=t;++j)
                res=(res+C(x,j)*C(y,t-j))%modu;
        } else
        {
            for (int j=0;j<i-l;++j)
                res=(res+C(x,j)*C(y,t-j))%modu;
            res=(modu+C(x+y,t)-res)%modu;
        }
        ans=(ans+res*s)%modu;

        R[l]=r,L[r]=l;
        s=s*calc(l,r)%modu;
    }
    printf("%lld\n",ans);
}

int main()
{
    init();
    solve();
    return 0;
}
