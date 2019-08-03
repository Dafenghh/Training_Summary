#include<bits/stdc++.h>
#define rep(i,l,r) for (int i=l;i<=r;i++)
using namespace std;
#define PII pair<int,int>
#define fi first
#define se second
const int maxn=200500;
struct node{int x,y,z,id,op;}q[maxn*2];
PII mx[maxn][5],t[maxn],tmp[maxn][4];
vector<int> g[maxn];
int in[maxn],out[maxn],dep[maxn],res[maxn][4],fa[maxn][22];
int n,m,cnt,idx;
void insert(PII &a,PII mx[]){
    if (a>mx[1]) {mx[3]=mx[2]; mx[2]=mx[1]; mx[1]=a; return;}
    if (a>mx[2]) {mx[3]=mx[2]; mx[2]=a; return;}
    mx[3]=max(mx[3],a);
}
void dfs(int u){
    mx[u][1]=mx[u][2]=mx[u][3]={0,u};
    in[u]=++idx;
    for (int i=1;i<=20;i++) fa[u][i]=fa[fa[u][i-1]][i-1];
    for (auto v:g[u]){
        if (v==fa[u][0]) continue;
        fa[v][0]=u;
        dep[v]=dep[u]+1;
        dfs(v);
        PII p={mx[v][1].fi+1,mx[v][1].se};
        insert(p,mx[u]);
    }
    out[u]=idx;
}
void dfs2(int u){
    for (auto v:g[u]){
        if (v==fa[u][0]) continue;
        rep(i,1,3) {
            if (in[v]<=in[mx[u][i].se]&&in[mx[u][i].se]<=out[v]) continue;
            PII p={mx[u][i].fi+dep[v]-dep[u],mx[u][i].se};
            insert(p,mx[v]);
            break;
        }
        dfs2(v);
    }
}
bool jud(int &a,int &b,int &c){
    if (a+b+c<2*max(max(a,b),c)) return 0;
    if ((a+b-c)&1) return 0;
    if ((a+c-b)&1) return 0;
    if ((b+c-a)&1) return 0;
    return 1;
}
bool cmp(node a,node b){
    if (a.x!=b.x) return a.x>b.x;
    if (a.y!=b.y) return a.y>b.y;
    if (a.z!=b.z) return a.z>b.z;
    return a.op>b.op;
}
#define low(i) (i&(-i))
inline void ins(int x,PII y){
    while (x<=n) t[x]=max(t[x],y),x+=low(x);
}
inline PII ask(int x){
    PII ans={0,0};
    while (x) ans=max(ans,t[x]),x-=low(x);
    return ans;
}
int lca(int x,int y){
    if (dep[x]<dep[y]) swap(x,y);
    int t=dep[x]-dep[y];
    for (int i=20;i>=0;i--) if (t>>i&1) x=fa[x][i];
    for (int i=20;i>=0;i--) if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
    if (x==y) return x;
    return fa[x][0];
}
int get(int x,int y,int t){
    int f=lca(x,y);
    if (t<=dep[x]-dep[f]){
        for (int i=20;i>=0;i--) if (t>>i&1) x=fa[x][i];
        return x;
    }
    t-=dep[x]-dep[f];
    t=dep[y]-dep[f]-t;
    for (int i=20;i>=0;i--) if (t>>i&1) y=fa[y][i];
    return y;
}
void getans(int &o,int &aim){
    res[q[o].id][tmp[q[o].id][1].se]=get(aim,mx[aim][1].se,q[o].x)-1;
    res[q[o].id][tmp[q[o].id][2].se]=get(aim,mx[aim][2].se,q[o].y)-1;
    res[q[o].id][tmp[q[o].id][3].se]=get(aim,mx[aim][3].se,q[o].z)-1;
}
bool cmptmp(PII &a,PII &b){
    return a>b;
}
int main(){
    scanf("%d",&n);
    rep(i,2,n) {
        int x,y; scanf("%d%d",&x,&y); x++; y++;
        g[x].push_back(y); g[y].push_back(x);
    }
    dfs(1);
    dfs2(1);
    scanf("%d",&m);
    rep(i,1,m){
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        if (!jud(a,b,c)) res[i][1]=-1; 
        tmp[i][1]={(a+b-c)/2,1}; tmp[i][2]={(a+c-b)/2,2}; tmp[i][3]={(b+c-a)/2,3};
        sort(tmp[i]+1,tmp[i]+1+3,cmptmp);
        q[i].x=tmp[i][1].fi; q[i].y=tmp[i][2].fi; q[i].z=tmp[i][3].fi;
        q[i].id=i; q[i].op=0;
    }
    int cnt=m;
    rep(i,1,n){
        q[++cnt].x=mx[i][1].fi; q[cnt].y=mx[i][2].fi; q[cnt].z=mx[i][3].fi;
        q[cnt].id=i; q[cnt].op=1;
        // printf("%d:\n",i);
        // rep(j,1,3) printf("%d %d\n",mx[i][j].fi,mx[i][j].se);
    }
    sort(q+1,q+1+cnt,cmp);
    rep(i,1,cnt) {
        if (!q[i].op){
            if (res[q[i].id][1]==-1) continue;
            PII aim=ask(n-q[i].y);
            if (aim.fi<q[i].z) res[q[i].id][1]=-1;
            else getans(i,aim.se);
        }
        else {
            ins(n-q[i].y,{q[i].z,q[i].id});
        }
    }
//    rep(i,1,cnt) printf("%d %d %d\n",q[i].x,q[i].y,q[i].z);
    rep(i,1,m) {
        if (res[i][1]==-1) {puts("-1"); continue;}
        rep(j,1,3) printf("%d ",res[i][j]);
        puts("");
    }
    return 0;
}
