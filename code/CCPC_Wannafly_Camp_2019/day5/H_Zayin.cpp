#include<bits/stdc++.h>
#define fi first
#define se second
#define mkp(x,y)    make_pair(x,y)
#define maxn 100050
#define modu 1000000007
#define sq(x)   (((x)*(x))%modu)
#define add(x,y)    ((x)=((x)+(y))%modu)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;

int n,m,N;

int tot;
int head[maxn],edge[maxn<<1],nxt[maxn<<1];

vector<pair<int,pii> > G[maxn];
vector<pii> Sz[maxn];

void join(int u,int v)
{
    edge[tot]=v; nxt[tot]=head[u]; head[u]=tot++;
    edge[tot]=u; nxt[tot]=head[v]; head[v]=tot++;
}

void init()
{
    scanf("%d%d",&n,&m);
    N=(LL)n*m%modu;

    tot=0;
    memset(head,-1,sizeof(head));
    for (int k=1;k<n;++k)   {
        int u,v;
        scanf("%d%d",&u,&v);
        join(u,v);
    }
    for (int k=1;k<m;++k)   {
        int a,b,u,v;
        scanf("%d%d%d%d",&a,&b,&u,&v);
        G[a].push_back(mkp(u,mkp(b,v)));
        G[b].push_back(mkp(v,mkp(a,u)));
    }
}

LL ans;

LL calc(int i,int fa=0) {
    LL sz=n;
    for (auto p:G[i])   {
        if (p.se.fi==fa)    continue;
        int u=p.fi,j=p.se.fi,v=p.se.se;
        LL t=calc(j,i);
        add(ans,t*(N-t+modu));
        Sz[i].push_back(mkp(u,t%modu));
        Sz[j].push_back(mkp(v,(N-t+modu)%modu));
        add(sz,t);
    }
    return sz;
}

int fa[maxn];
int son[maxn],top[maxn];
int dep[maxn],sz[maxn];

int T,id[maxn];

int dfs1(int i)    {
    for (int k=head[i];~k;k=nxt[k]) {
        int j=edge[k];
        if (fa[i]==j)   continue;
        fa[j]=i;
        sz[i]+=dfs1(j);
        if (sz[son[i]]<sz[j])
            son[i]=j;
    }
    return ++sz[i];
}

void dfs2(int i,int tp) {
    top[i]=tp,id[i]=++T;
    if (son[i]) dfs2(son[i],tp);
    for (int k=head[i];~k;k=nxt[k])  {
        int j=edge[k];
        if (fa[i]==j||son[i]==j)    continue;
        dfs2(j,j);
    }
}

struct node
{
    LL s1,s2,tag;
}   Tree[maxn<<2];

#define s1(k)   Tree[k].s1
#define s2(k)   Tree[k].s2
#define tag(k)  Tree[k].tag

void update(int k,int len)  {
    int ls=k<<1,rs=k<<1|1;
    LL t=s1(ls)+s1(rs);
    s1(k)=(t+tag(k)*len)%modu;
    s2(k)=(s2(ls)+s2(rs)+sq(tag(k))*len+2*t*tag(k))%modu;
}

void change(int k,int l,int r,int a,int b,LL t)
{
    if (a<=l&&r<=b) {
        add(tag(k),t);
        add(s2(k),sq(t)*(r-l+1)+2*s1(k)*t);
        add(s1(k),(r-l+1)*t);
    } else
    {
        int mid=(l+r)>>1;
        if (a<=mid)
            change(k<<1,l,mid,a,b,t);
        if (b>mid)
            change(k<<1|1,mid+1,r,a,b,t);
        update(k,r-l+1);
    }
}

void Add(int i,LL s)    {
    for (;i;i=fa[top[i]])
        change(1,1,n,id[top[i]],id[i],s);
}

void predo()    {
    calc(1);
    dfs1(1);
    dfs2(1,1);
    for (int i=1;i<=n;++i)
        Add(i,1);
}


void solve()
{
    for (int i=1;i<=m;++i)  {
        for (auto p:Sz[i])  Add(p.fi,p.se);
        add(ans,N*s1(1)-s2(1)+modu);
        for (auto p:Sz[i])  Add(p.fi,modu-p.se);
    }
    printf("%lld\n",ans);
}

int main()
{
    init();
    predo();
    solve();
    return 0;
}
