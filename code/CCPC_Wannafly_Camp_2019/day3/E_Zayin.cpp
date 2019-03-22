#include<bits/stdc++.h>
#define maxn 100050
#define modu 998244353
using namespace std;
typedef long long LL;

int n,m;

int tot;
int head[maxn],edge[maxn<<1],nxt[maxn<<1];

int dp[maxn];
int f[maxn],g[maxn];

void join(int u,int v)
{
    edge[tot]=v; nxt[tot]=head[u]; head[u]=tot++;
    edge[tot]=u; nxt[tot]=head[v]; head[v]=tot++;
}

void init()
{
    tot=0;
    memset(head,-1,sizeof(head));

    scanf("%d%d",&n,&m);
    for (int k=1;k<n;++k)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        join(u,v);
    }
}

void dfs1(int i,int fa=0)
{
    f[i]=0;
    for (int k=head[i];~k;k=nxt[k])
    {
        int j=edge[k];
        if (fa==j)  continue;
        dfs1(j,i);
        f[i]+=!f[j];
        dp[i]+=dp[j];
    }
    if (!f[i])   ++dp[i];
}

void dfs2(int i,int fa=0)
{
    for (int k=head[i];~k;k=nxt[k])
    {
        int j=edge[k];
        if (fa==j)  continue;

        f[j]+=!(f[i]-!f[j]);
        dfs2(j,i);
    }
}

void solve()
{
    dfs1(1);
    dfs2(1);

    LL ans=dp[1],tag=!f[1];
    printf("%lld\n",ans);
    while (m--)
    {
        int i;
        scanf("%d",&i);
        if (!tag)
            ans=(ans*n+dp[1])%modu,tag=!f[i];
        else
            ans=ans*n%modu,tag=0;
        printf("%lld\n",ans);
    }
}

int main()
{
    init();
    solve();
    return 0;
}
