#include<bits/stdc++.h>
#define rep(i,l,r) for (int i=l;i<=r;i++)
using namespace std;
const int inf=1e9;
const int maxn=1005;
struct node{int x,y;};
vector<node> g[maxn];
queue<node> q;
int n,m,s,t,k,ans;
int dis[maxn][maxn],vis[maxn][maxn];
int main(){
    scanf("%d%d%d%d%d",&n,&m,&s,&t,&k);
    rep(i,1,n) rep(j,0,k) dis[i][j]=inf,vis[i][j]=0;
    rep(i,1,m){
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        g[x].push_back((node){y,z});
        g[y].push_back((node){x,z});
    }
    dis[s][0]=0;
    q.push((node){s,0}); vis[s][0]=1;
    while (!q.empty()){
        node x=q.front(); q.pop();
        int u=x.x,id=x.y;
        vis[u][id]=0;
        for (auto p:g[u]){
            int v=p.x,c=p.y;
            if (dis[v][id]>dis[u][id]+c){
                dis[v][id]=dis[u][id]+c;
                if (!vis[v][id]) vis[v][id]=1,q.push((node){v,id});
            }
            if (id+1<=k&&dis[v][id+1]>dis[u][id]){
                dis[v][id+1]=dis[u][id];
                if (!vis[v][id+1]) vis[v][id+1]=1,q.push((node){v,id+1});
            }
        }
    }
    ans=inf;
    rep(i,0,k) ans=min(ans,dis[t][i]);
    printf("%d\n",ans);
    return 0;
}
