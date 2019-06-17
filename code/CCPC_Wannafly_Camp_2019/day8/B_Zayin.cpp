#include<bits/stdc++.h>
#define maxn 10050
#define maxm 100050
using namespace std;

struct Edge {
    int u,v;
}   E[maxm];

int n,m;
int vs,vt;
void init() {
    scanf("%d%d",&n,&m);
    vs=n,vt=n+1;
    for (int i=0;i<m;++i)   {
        scanf("%d%d",&E[i].u,&E[i].v);
        if (E[i].u>E[i].v)
            swap(E[i].u,E[i].v);
    }
}

int tot;
int cost[maxm];
int head[maxn],edge[maxm],nxt[maxm];

void join(int u,int v)  {
    cost[tot]=1; edge[tot]=v; nxt[tot]=head[u]; head[u]=tot++;
    cost[tot]=0; edge[tot]=u; nxt[tot]=head[v]; head[v]=tot++;
}

int d[maxn];
queue<int> q;

int cur[maxn];
bool bfs()  {
    for (int i=0;i<=vt;++i) d[i]=0,cur[i]=head[i];
    q.push(vs),d[vs]=1;
    while (!q.empty())  {
        int i=q.front();    q.pop();
        for (int k=head[i],j;~k;k=nxt[k]) {
            if (d[j=edge[k]]||!cost[k])   continue;
            q.push(j),d[j]=d[i]+1;
        }
    }
    return d[vt];
}

deque<int> stk;

int dfs(int i=vs,int f=maxn)    {
    if (!f) return 0;
    if (i==vt)  return f;
    int sf=0;
    for (int &k=cur[i],j;~k;k=nxt[k])  {
        if (cost[k]&&d[i]+1==d[j=edge[k]])  {
            int a=dfs(j,min(cost[k],f));
            sf+=a,f-=a;
            cost[k]-=a,cost[k^1]+=a;
            if (!f) break;
        }
    }
    return sf;
}
bool judge(int x)   {
    tot=0;
    memset(head,-1,sizeof(head));
    for (int i=0;i<x;++i) join(vs,i);
    for (int i=x;i<n;++i) join(i,vt);
    for (int i=0;i<m;++i)
        if ((E[i].u<x)&&(E[i].v>=x))
            join(E[i].u,E[i].v);
    int ans=0;
    while (bfs())   ans+=dfs();
    return ans==x;
}
void solve()    {
    int l=0,r=n+1;
    while (l<r) {
        int mid=(l+r+1)>>1;
        if (judge(mid))
            l=mid;
        else
            r=mid-1;
    }
    printf("%d\n",l);
}
int main()  {
    init();
    solve();
    return 0;
}
