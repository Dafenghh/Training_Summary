#include<bits/stdc++.h>
#define ALL(A)  A.begin(),A.end()
#define Unique(A)  sort(ALL(A)),A.resize(unique(ALL(A))-A.begin())
#define maxp 250
#define maxh 17
#define maxn 100050
using namespace std;

int n,m;
vector<int> G[maxn],T[maxn];
vector<int> P;
int dis[maxp][maxn];

void init()
{
    scanf("%d%d",&n,&m);
    while (m--)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
}

bool vis[maxn];
queue<int> q;

int F[maxh][maxn],*fa=F[0];
int sz[maxn],dep[maxn];

int Time,st[maxn],ed[maxn];

int dfs(int i)
{
    st[i]=++Time;
    for (int j=1;F[j-1][i];++j)
        F[j][i]=F[j-1][F[j-1][i]];
    for (int j:T[i])
        sz[i]+=dfs(j);
    ed[i]=Time;
    return ++sz[i];
}

void predo()
{
    memset(vis,0,sizeof(vis));
    q.push(1),vis[1]=1;
    while (!q.empty())
    {
        int i=q.front();    q.pop();
        for (int j:G[i])
        {
            if (vis[j])
            {
                if (fa[i]==j)   continue;
                P.push_back(i);
                P.push_back(j);
            } else
            {
                fa[j]=i,dep[j]=dep[i]+1;
                T[i].push_back(j);
                q.push(j),vis[j]=1;
            }
        }
    }

    // cout<<"1:"<<clock()<<endl;

    dfs(1);

    Unique(P);
    for (int k=0;k<P.size();++k)
    {
        int i=P[k];
        // dis[k].resize(maxn,-1);
        for (int i=1;i<=n;++i)
            dis[k][i]=-1;
        q.push(i),dis[k][i]=0;
        while (!q.empty())
        {
            int i=q.front();    q.pop();
            for (int j:G[i])
            {
                if (~dis[k][j]) continue;
                q.push(j);
                dis[k][j]=dis[k][i]+1;
            }
        }
    }
    // cout<<"2:"<<clock()<<endl;
}

bool cmp(int i,int j)   {
    return st[i]<st[j];
}

int low[maxn];

int kth_fa(int u,int k)
{
    while (k)
    {
        int t=k&(-k);
        u=F[low[t]][u];
        k^=t;
    }
    return u;
}

vector<int> vert;

void solve()
{
    // cout<<"???"<<endl;
    for (int i=0;(1<<i)<maxn;++i)
        low[1<<i]=i;

    int ans=0;
    for (int i=2;i<=n;++i)
    {
        vert.clear();
        vert.push_back(kth_fa(i,dep[i]/2));
        for (int k=0;k<P.size();++k)
        {
            int j=P[k],d=dis[k][i];
            if (dep[j]<d)   continue;
            vert.push_back(kth_fa(j,(dep[j]-d)/2));
        }
        Unique(vert);
        sort(ALL(vert),cmp);

        int sum=0,rt=0;
        for (int j:vert)
        {
            if (st[rt]<=st[j]&&ed[j]<=ed[rt])   continue;
            sum+=sz[rt=j];
        }

        // cout<<i<<"("<<sum<<"):";
        // for (int j:vert)
        //     cout<<j<<" ";
        // cout<<endl;
        ans=max(ans,sum);
    }
    // cout<<"3:"<<clock()<<endl;
    printf("%d\n",n-ans);
}

int main()
{
    init();
    // cout<<clock()<<endl;
    predo();
    // cout<<clock()<<endl;
    solve();
    // cout<<clock()<<endl;
    return 0;
}
