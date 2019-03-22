#include<bits/stdc++.h>
#define maxn 1005
using namespace std;

int n,m;
vector<int> G[maxn];
void init() {
    scanf("%d%d",&n,&m);
    while (m--) {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
}

bool vis[maxn];
int dep[maxn];
int fa[maxn],son[maxn];

void dfs1(int i)    {
    vis[i]=1,dep[i]=dep[fa[i]]+1;
    for (int j:G[i])    {
        if (fa[i]==j)   continue;
        if (!vis[j])
            fa[j]=i,dfs1(j);
        else    
        if (dep[i]>dep[j])
            for (int k=i;fa[k]!=j;k=fa[k])
                son[fa[k]]=k;
    }
}
int T,X[maxn],Y[maxn];
void dfs2(int i,int d)    {
    vis[i]=0;
    X[i]=++T,Y[i]=d;
    for (int j:G[i])    {
        if (!vis[j]||son[i]==j)    continue;
        dfs2(j,d+1);
    }
    if (son[i])
        dfs2(son[i],d);
}
void solve()    {
    dfs1(1);
    dfs2(1,1);
    for (int i=1;i<=n;++i)
        printf("%d %d\n",X[i],Y[i]);
}
int main()  {
    init();
    solve();
    return 0;
}
