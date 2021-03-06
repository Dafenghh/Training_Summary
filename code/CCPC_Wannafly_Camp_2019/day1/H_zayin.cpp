#include<bits/stdc++.h>
#define maxh 8
#define maxn 105
using namespace std;

int n,m;
int h[maxn];

int Log2[maxn]={-1};
int ST[maxh][maxn];

vector<int> H(1,0);

int dp[maxn][maxn][maxn];

int Min(int i,int j)
{
    return h[i]<h[j]?i:j;
}

void init()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;++i)
        scanf("%d",h+i),H.push_back(h[i]);
    
    sort(H.begin(),H.end());
    H.resize(unique(H.begin(),H.end())-H.begin());

    for (int i=1;i<=n;++i)  Log2[i]=Log2[i>>1]+1;
    for (int i=1;i<=n;++i)  ST[0][i]=i;
    for (int j=1;(1<<j)<=n;++j)
        for (int i=1;i+(1<<j)-1<=n;++i)
            ST[j][i]=Min(ST[j-1][i],ST[j-1][i+(1<<(j-1))]);
}

int T;

int getpos(int l,int r)
{
    int t=Log2[r-l+1];
    return Min(ST[t][l],ST[t][r-(1<<t)+1]);
}

int ans;

int calc(int l,int r)
{
    if (l>r)    return 0;
    int p=getpos(l,r),t=lower_bound(H.begin(),H.end(),h[p])-H.begin();

    int ls=calc(l,p-1),rs=calc(p+1,r);

    ++T;
    for (int i=0;i<H.size();++i)
    {
        if (H[i]>h[p])   break;
        for (int k=1;k<=m;++k)
        {
            int res=0;
            for (int j=0;j<=k;++j)
                res=max(res,dp[ls][i][j]+dp[rs][i][k-j]);
            for (int j=0;j<k;++j)
                res=max(res,dp[ls][t][j]+dp[rs][t][k-1-j]+(h[p]-H[i])*(r-l+1));
            
            dp[T][i][k]=res;
            ans=max(ans,res);
        }
    }
    return T;
}

void solve()
{
    calc(1,n);
    printf("%d\n",ans);
}

int main()
{
    init();
    solve();
    return 0;
}