#include<bits/stdc++.h>
#define maxn 550
#define modu 998244353
using namespace std;
typedef long long LL;

int n,a[maxn];

bool vis[maxn][maxn];
LL dp[maxn][maxn],C[maxn][maxn];

void add(LL &x,LL y)    {   x=(x+y)%modu;   }
LL calc(int l,int r)    {
    if (l+1==r) return 1;
    if (vis[l][r])  return dp[l][r];
    vis[l][r]=1;
    if (a[l]==a[r]) return dp[l][r]=0;
    for (int i=l+1;i<r;++i) {
        if (a[i]==a[l]||a[i]==a[r]) continue;
        // cout<<l<<" "<<r<<" "<<i<<" "<<calc(l,i)<<" "<<calc(i,r)<<" "<<C[r-l-2][i-l-1]<<endl;
        add(dp[l][r],calc(l,i)*calc(i,r)%modu*C[r-l-2][i-l-1]);
    }
    // printf("dp[%d][%d]=%lld\n",l,r,dp[l][r]);
    return dp[l][r];
}

int main()  {
    scanf("%d",&n);
    for (int i=1;i<=n;++i)
        scanf("%d",a+i);
    a[++n]=maxn;
    for (int i=C[0][0]=1;i<=n;++i) 
        for (int j=C[i][0]=1;j<=i;++j)
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%modu;
    printf("%lld\n",calc(0,n));
    return 0;
}
