#include<bits/stdc++.h>
#define maxh 24
#define maxn 400050
#define Fa(i)   F[i][1]
using namespace std;

int n,m;
vector<int> G[maxn];

void init()	{
	scanf("%d",&n);
	for (int k=1;k<n;++k)	{
		int u,v;
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
}

bool vis[maxn];

int fa[maxn];
int sz[maxn],mx[maxn];
int Q[maxn],l,r;

vector<int> F[maxn];
int P1,P2;
int pool1[maxn*maxh*2],pool2[maxn*maxh*4];
int *pos1[maxn],*pos2[maxn][maxh];
int len1[maxn],len2[maxn][maxh];

int getvert(int v)	{
	for (fa[Q[l=r=1]=v]=0;l<=r;mx[Q[l]]=0,sz[Q[l++]]=1)
		for (int j:G[Q[l]])
			if (fa[Q[l]]!=j)	{
				fa[j]=Q[l];
				if (!vis[j])	Q[++r]=j;
			}
}

int getroot(int v)	{
	getvert(v);
	int rt=0;mx[rt]=maxn;
	for (int k=r;k;--k)	{
		int i=Q[k];
		sz[fa[i]]+=sz[i];
		mx[fa[i]]=max(mx[fa[i]],sz[i]);
		mx[i]=max(mx[i],r-sz[i]);
		if (mx[rt]>mx[i])
			rt=i;
	}
	return rt;
}

int dis[maxn];

void calc(int v)	{
	pos1[v]=pool1+P1;
	for (int k=dis[Q[1]]=1;k<=r;++k)	{
		int i=Q[k];
		++pos1[v][dis[i]];
		len1[v]=max(len1[v],dis[i]);
		for (int j:G[i])
			if (!vis[j]&&fa[i]!=j)
				dis[j]=dis[i]+1;
	}
	for (int i=1;i<=len1[v];++i)	pos1[v][i]+=pos1[v][i-1];
	P1+=++len1[v];
	
	for (int j:F[v])	fa[j]=0;
	getvert(v);
	for (int j=0;j<F[v].size();++j)	{
		if (j&&!fa[F[v][j]])	continue;
		pos2[v][j]=pool2+P2;
		for (int k=1;k<=r;++k)	dis[Q[k]]=maxn;
        dis[v]=0;
		for (int k=fa[F[v][j]];k;k=fa[k])	dis[k]=0;
		for (int k=1;k<=r;++k)	{
			int i=Q[k];
			++pos2[v][j][dis[i]];
			len2[v][j]=max(len2[v][j],dis[i]);
			for (int j:G[i])
				if (!vis[j]&&fa[i]!=j&&dis[j])
					dis[j]=dis[i]+1;
		}
		for (int i=1;i<=len2[v][j];++i)
			pos2[v][j][i]+=pos2[v][j][i-1];
		P2+=++len2[v][j];
	}
}

void dfs1(int i,int fa=0)	{
	int rt=getroot(i);
	F[rt].push_back(rt);
	for (int j:F[fa])
		F[rt].push_back(j);
	calc(rt);
	vis[rt]=1;
	for (int j:G[rt])
		if (!vis[j])
			dfs1(j,rt);
}

int T,pos[maxn],dep[maxn];
int Log2[maxn<<1];
int ST[maxh][maxn<<1];
void dfs2(int i,int fa=0)   {
    dep[i]=dep[fa]+1;
    ST[0][pos[i]=T++]=i;
    for (int j:G[i])
        if (fa!=j)
            dfs2(j,i),ST[0][T++]=i;
}

int Min(int i,int j)    {   return dep[i]<dep[j]?i:j;   }
int Lca(int i,int j)    {
    int l=pos[i],r=pos[j];
    if (l>r)    swap(l,r);
    int t=Log2[r-l+1];
    return Min(ST[t][l],ST[t][r-(1<<t)+1]);
}
void predo()	{
	dfs1(1);
    dfs2(1);
    Log2[0]=-1;
    for (int i=1;i<=T;++i)  Log2[i]=Log2[i>>1]+1;
    for (int j=1;(1<<j)<=T;++j)
        for (int i=0;i+(1<<j)<=T;++i)
            ST[j][i]=Min(ST[j-1][i],ST[j-1][i+(1<<(j-1))]);
}

int dis_vert(int u,int v)   {   return dep[u]-dep[v];  }
int dis_path(int u,int v,int p)  {
    int z=Lca(u,v);
    if (Lca(p,z)==z)
        return min(dis_vert(p,Lca(p,u)),dis_vert(p,Lca(p,v))); 
    return dep[z]+dep[p]-dep[Lca(z,p)]*2;
}

int Len1(int i,int d)   {   return d>=0?pos1[i][min(d,len1[i]-1)]:0;  }
int Len2(int i,int j,int d) {   
    if (!len2[i][j]||d<0) return 0;
    return pos2[i][j][min(d,len2[i][j]-1)];
}

int jump(int s,int t,int D) {
    if (s==t)   return 0;
    int ans=0;
    for (int u=s,j;u!=t;) {
        for (j=1;;++j)  {
            if (j>=F[u].size())  exit(0);
            int d=dis_path(s,t,F[u][j]);
            ans-=Len1(F[u][j-1],D-d);
            if (!d) break;
            ans+=Len2(F[u][j],0,D-d);
        }
        ans+=Len2(u,j,D);
        u=F[u][j];
    }
    return ans;
}

int query(int U,int V,int D)  {
    int u=U,v=V;
    while (u!=v)  {
        if (F[u].size()<F[v].size())  swap(u,v);
        u=Fa(u);
    }
    int ans=jump(U,u,D)+jump(V,u,D)+Len2(u,0,D);
    for (;F[u].size()>1;u=Fa(u))    {
        int d=dis_path(U,V,Fa(u));
        ans+=Len2(Fa(u),0,D-d)-Len1(u,D-d);
    }
    return ans;
}

void solve()	{
	int ans=0;
	scanf("%d",&m);
	while (m--)	{
		int u,v,d;
		scanf("%d%d%d",&u,&v,&d);
		u^=ans,v^=ans,d^=ans;
        ans=query(u,v,d);
        printf("%d\n",ans);
	}
}
int main()	{
	init();
	predo();
	solve();
	return 0;
}
