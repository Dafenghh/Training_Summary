#include<bits/stdc++.h>
#define maxn 3050
#define modu 998244353
using namespace std;
typedef long long LL;
 
LL C[maxn][maxn];
 
void predo()    {
    for (int i=C[0][0]=1;i<maxn;++i)
        for (int j=C[i][0]=1;j<=i;++j)
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%modu;
}
 
int n,m;
 
char s[maxn],t[maxn];
 
void init() {
    scanf("%d%d",&n,&m);
    scanf("%s%s",s+1,t+1);
}
 
LL dp[maxn][maxn];
 
void add(LL &a,LL b)    {
    a=(a+b)%modu;
}
 
void solve()    {
    LL ans=0;
    for (int i=1;i<=n;++i)
        if (s[i]!='0')
            for (int j=m;i+j<=n;++j)
                add(ans,C[n-i][j]);
    for (int i=0;i<=n;++i)
        for (int j=0;j<=n;++j)
            dp[i][j]=0;
    for (int i=1;i<=n;++i)  {
        dp[i][0]=1;
        if (s[i]==t[1])  
            dp[i][1]=1;
    }
    for (int j=2;j<=m;++j)  {
        LL sum=0;
        for (int i=1;i<=n;++i)  {
            if (s[i]==t[j])
                add(dp[i][j],sum);
            add(sum,dp[i][j-1]);
        }
    }
    for (int j=m;j;--j) {
        LL sum=(j==1);
        for (int i=1;i<=n;++i) {
            if (s[i]>t[j])
                add(ans,sum*C[n-i][m-j]);
            // cout<<i<<" "<<j<<" "<<sum<<" "<<dp[i][j-1]<<" "<<(s[i]>t[j]?sum*C[n-i][m-j]:0)<<endl;
            if (j>1)
                add(sum,dp[i][j-1]);
        }
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
