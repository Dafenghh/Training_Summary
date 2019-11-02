#include<bits/stdc++.h>
#define maxn 2050
#define maxb 3050
#define maxm 1000050
#define modu 1000000007
using namespace std;
typedef long long LL;

int n,A;
int a[maxn];

vector<int> G[maxn];

int m,w[maxn];
int id1[maxn],id2[maxn];

LL ans;

int id(int x)	{
	return x<maxn?id1[x]:id2[A/x];
}

bool vis[maxn];

int fa[maxn];
int Q[maxn],l,r;

int sz[maxn],mx[maxn]={maxn};

int getroot(int v)	{
	fa[v]=0;
	for (Q[l=r=1]=v;l<=r;++l)	{
		int i=Q[l];
		sz[i]=1,mx[i]=0;
		for (int j:G[i])	{
			if (fa[i]==j||vis[j])	continue;
			fa[Q[++r]=j]=i;
		}
	}
	int rt=0;
	for (int k=r;k;--k)	{
		int i=Q[k];
		sz[fa[i]]+=sz[i];
		mx[fa[i]]=max(mx[fa[i]],sz[i]);
		mx[i]=max(mx[i],r-sz[i]);
//		cout<<"mx("<<i<<"):"<<mx[i]<<" "<<sz[i]<<endl;
		if (mx[rt]>mx[i])
			rt=i;
	}
	return rt;
}

int L[maxn],R[maxn];

void dfs(int i,int fa=0)	{
	Q[++r]=i;
	L[i]=r;
	for (int j:G[i])	{
		if (fa==j||vis[j])	continue;
		dfs(j,i);
	}
	R[i]=r;
}

LL dp[maxn][maxb];

void calc(int rt)	{
//	cout<<"calc:"<<rt<<endl;
	r=0;
	dfs(rt);
//	for (int i=1;i<=r;++i)
//		cout<<Q[i]<<" ";
//	cout<<endl;
	for (int i=0;i<=r+1;++i)
		for (int j=0;j<=m;++j)
			dp[i][j]=0;
	for (int j=1;j<=m;++j)
		dp[r+1][j]=1;
	for (int k=r;k;--k)	{
		int i=Q[k];
		for (int j=1;j<=m;++j)	{
			dp[k][j]=dp[R[i]+1][j];
			if (w[j]<a[i])	continue;
			int t=id(w[j]/a[i]);
			dp[k][j]=(dp[k][j]+dp[k+1][t])%modu;
		}
//		cout<<k<<"("<<i<<"):";
//		for (int j=0;j<=m;++j) cout<<dp[k][j]<<" "; cout<<endl;
	}
	ans=(ans+dp[1][id(A)]-1+modu)%modu;
}

void solve(int i)	{
	int rt=getroot(i);
//	cout<<"solve:"<<i<<" "<<rt<<endl;
	calc(rt);
	vis[rt]=1;
	for (int j:G[rt])
		if (!vis[j])
			solve(j);
}


int main()	{
	int T;
	scanf("%d",&T);
	while (T--)	{
		scanf("%d%d",&n,&A);
		for (int i=1;i<=n;++i)	
			vis[i]=0,G[i].clear();
		
		ans=m=0;
		for (int i=1,j;i<=A;i=j+1)	{
			j=A/(A/i);
			w[++m]=A/i;
			if (w[m]<maxn)
				id1[w[m]]=m;
			else
				id2[j]=m;
		}
//		cout<<"w:"; for (int i=1;i<=m;++i) cout<<w[i]<<" "; cout<<endl;
		
		for (int i=1;i<=n;++i)
			scanf("%d",a+i);
		for (int k=1;k<n;++k)	{
			int u,v;
			scanf("%d%d",&u,&v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		solve(1);
		printf("%lld\n",ans);
	}
	return 0;
}
