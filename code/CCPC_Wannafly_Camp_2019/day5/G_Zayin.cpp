#include<bits/stdc++.h>
#define maxh 30
#define maxn 205
#define N 10000000
#define modu 1000000007
using namespace std;
typedef long long LL;

int n;
LL a[maxn];

vector<LL> P;
map<int,LL> C[maxh];

void calc(LL x)
{   
    for (LL i=2;i*i<=x;++i)
    {
        if (x%i)    continue;
        P.push_back(i);
        while (x%i==0)  x/=i;
    }
    if (x!=1)
        P.push_back(x);
}

int main()
{
    scanf("%d",&n);
    for (int i=0;i<n;++i)
        scanf("%lld",a+i);

    sort(a,a+n);
    for (int i=0;i<n;++i)
        for (int j=0;j<i;++j)
            if (a[i]==a[j])
                return puts("-1"),0;
            else
                calc(a[i]-a[j]);

    sort(P.begin(),P.end());
    P.resize(unique(P.begin(),P.end())-P.begin());

    LL ans=1;
    for (LL p:P)
    {
        for (LL pe=p,c=1;pe<=N;pe*=p,++c)
        {
            C[c].clear();
            for (int i=0;i<n;++i)
                ++C[c][a[i]%pe];
        }
        
        int mx=0;
        for (int i=0;i<n;++i)
        {
            int t=0;
            for (LL pe=p,c=1;pe<=N;pe*=p,++c)
                t+=C[c][a[i]%pe]-1;
            mx=max(mx,t);
        } 
        while (mx--)
            ans=ans*p%modu;
    }
    cout<<ans<<endl;
    return 0;
}
