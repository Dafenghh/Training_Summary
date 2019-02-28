#include<bits/stdc++.h>
#define maxb 705
#define maxn 10050
#define maxm 70050
using namespace std;

int n,id[maxb][maxb];
char mp[maxb][maxb];

int dir[5][2];
//const int dir[6][2]={{-2,0},{2,0},{-1,-3},{-1,3},{1,-3},{1,3}};

int ID(int i,int j) {
    if (!id[i][j])
        id[i][j]=++n;
    return id[i][j];
}

int tot;
int cost[maxm<<1];
int head[maxn],edge[maxm<<1],nxt[maxm<<1];

void join(int u,int v)  {
    // cout<<u<<" -> "<<v<<endl;
    edge[tot]=v; nxt[tot]=head[u]; head[u]=tot++;
    edge[tot]=u; nxt[tot]=head[v]; head[v]=tot++;
}

void init() {
    int H,D;
    scanf("%d%d",&H,&D);
    H=H*4+3,D=D*6+3;
    for (int i=0;i<H;++i)   
        do fgets(mp[i],maxn,stdin);  while(strlen(mp[i])<5);
    for (int i=0;i<H;++i)
        for (int j=0;j<D;++j)
            id[i][j]=0;

    dir[0][0]=-2,dir[0][1]=0;
    dir[1][0]=1,dir[1][1]=3;
    dir[2][0]=-1,dir[2][1]=-3;
    dir[3][0]=-1,dir[3][1]=3;
    dir[4][0]=1,dir[4][1]=-3;
    
    tot=n=0;
    memset(head,-1,sizeof(head));
    for (int j=4;j<D;j+=12)
        for (int i=2;i<H;i+=4)    {
            if (mp[i][j]!='*')  continue;
            for (int k=0;k<5;++k)   {
                int x=i+dir[k][0],y=j+dir[k][1];
                if (mp[x][y]!=' ')  continue;
                join(ID(i,j),ID(x+dir[k][0],y+dir[k][1]));
            }
        }
    for (int j=10;j<D;j+=12)
        for (int i=4;i<H;i+=4)    {
            if (mp[i][j]!='*')  continue;
                int k=0,x=i+dir[k][0],y=j+dir[k][1];
                if (mp[x][y]!=' ')  continue;
                join(ID(i,j),ID(x+dir[k][0],y+dir[k][1]));
            }
}

int vs,vt;

int d[maxn];
queue<int> q;

bool bfs()  {
    for (int i=1;i<=n;++i)  d[i]=-1;
    q.push(vs),d[vs]=0;
    while (!q.empty())  {
        int i=q.front();    q.pop();
        for (int k=head[i],j;~k;k=nxt[k]) {
            if (cost[k]&&d[j=edge[k]]==-1)  {
                q.push(j),d[j]=d[i]+1;
            }
        }
    }
    return ~d[vt];
}

int dfs(int i,int f)    {
    if (i==vt)  return f;
    int sum=0;
    for (int k=head[i];~k;k=nxt[k]) {
        int j=edge[k];
        if (!cost[k]||d[j]!=d[i]+1) continue;
        int a=dfs(j,min(f,cost[k]));
        cost[k]-=a,cost[k^1]+=a;
        f-=a,sum+=a;
        if (!f) break;
    }
    if (!sum)    d[i]=-1;
    return sum;
}

int Dinic()    {
    for (int k=0;k<tot;++k) cost[k]=1;
    int ans=0;
    while (bfs())   ans+=dfs(vs,maxn);
    return ans;
}

int fa[maxn];
int cut[maxn][maxn];

bool vis[maxn];

void dfs(int i) {
    vis[i]=1;
    for (int k=head[i],j;~k;k=nxt[k])
        if (cost[k]&&!vis[j=edge[k]])
            dfs(j);
}

void solve()    {
    assert(n<=3000);

    int ans=0;
    for (int i=1;i<=n;++i)  fa[i]=1;
    for (int i=1;i<=n;++i)
        for (int j=1;j<=n;++j)
            cut[i][j]=maxn;
    for (int i=2;i<=n;++i)  {
        vs=i,vt=fa[i];
        int C=Dinic();
        for (int j=1;j<i;++j)
            ans+=(cut[i][j]=cut[j][i]=min(cut[fa[i]][j],C));
        
        for (int j=1;j<=n;++j)  vis[j]=0;
        dfs(i);
        for (int j=i+1;j<=n;++j)
            if (vis[j]&&fa[j]==fa[i])
                fa[j]=i;
    }
    printf("%d\n",ans);
}

int main()  {
    int T,icase=0;
    scanf("%d",&T);
    while (T--) {
        init();
        printf("Case #%d: ",++icase);
        solve();
    }
    return 0;
}
