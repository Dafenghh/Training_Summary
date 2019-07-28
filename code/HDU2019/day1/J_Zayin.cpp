#include<bits/stdc++.h>
#define maxn 105
#define modu 998244353
using namespace std;
typedef long long LL;

int n;
int a[maxn],b[maxn];
int pa[maxn],pb[maxn];

void init() {
    scanf("%d",&n);
    for (int i=1;i<=n;++i) pa[i]=pb[i]=0;
    for (int i=1;i<=n;++i)  scanf("%d",a+i),pa[a[i]]=i;
    for (int i=1;i<=n;++i)  scanf("%d",b+i),pb[b[i]]=i;
}

LL dp[maxn][maxn][maxn];

void add(LL &a,LL b)    {
    a=(a+b)%modu;
}

LL calc(int i,int l,int r)  {
    if (l>r)    return 1;
    if (~dp[i][l][r])   return dp[i][l][r];
    LL &ans=dp[i][l][r]; ans=0;
    if (a[i]&&pb[a[i]])    {
        if (l<=pb[a[i]]&&pb[a[i]]<=r)   {
            int l1=pb[a[i]]-l,l2=r-pb[a[i]];
            ans=calc(i+1,l,pb[a[i]]-1)*calc(i+l1+1,pb[a[i]]+1,r)%modu;
        }
    } else  {
        for (int j=l;j<=r;++j)  {
            if (b[j]&&a[i])   continue;
            add(ans,calc(i+1,l,j-1)*calc(i+j-l+1,j+1,r));
        }
    }
    return ans;
}

void solve()    {
    memset(dp,-1,sizeof(dp));
    LL ans=calc(1,1,n),cnt=1;
    for (int i=1;i<=n;++i)
        if (!pa[i]&&!pb[i])
            ans=ans*(cnt++)%modu;
    printf("%lld\n",ans);
}

int main()  {
    int T;
    scanf("%d",&T);
    while (T--) {
        init();
        solve();
    }
    return 0;
}
