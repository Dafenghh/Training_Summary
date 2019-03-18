#include<bits/stdc++.h>
#define maxn 10050
#define maxm 505
#define modu 1000000
using namespace std;
typedef long long LL;

int n,m;
vector<int> G[maxn],son[maxn];
void init()	{
	for (int i=1;i<=n;++i)	G[i].clear(),son[i].clear();
	for (int k=1;k<n;++k)	{
		int u,v;
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
}

int fa[maxn];
LL L[maxn][maxm],R[maxn][maxm];
LL dp[maxn][maxm];

void add(LL &x,LL y)	{
	x=(x+y)%modu;
}
void dfs(int i)	{
	int S=0;
	son[i].resize(1);
	for (int j:G[i])	{
		if (fa[i]==j)	continue;
		fa[j]=i,dfs(j);
		son[i].push_back(j),++S;
	}
	for (int c=0;c<=m+1;++c)	dp[i][c]=0;
	for (int c=1;c<=m+1;++c)	L[0][c]=R[S+1][c]=1;
	for (int k=1;k<=S;++k)	{
		LL t=dp[son[i][k]][m+1];
		for (int c=m+1;c;--c)
			t=(t+dp[son[i][k]][c-1])%modu,
			L[k][c]=L[k-1][c]*t%modu;
	}
	for (int k=S;k;--k)	{
		LL t=dp[son[i][k]][m+1];
		for (int c=m+1;c;--c)
			t=(t+dp[son[i][k]][c-1])%modu,
			R[k][c]=R[k+1][c]*t%modu;
	}
	for (int k=1;k<=S;++k)
		for (int c=1;2*c<m;++c)
			add(dp[i][c],L[k-1][m-c]*R[k+1][m-c]%modu*dp[son[i][k]][c-1]);
	dp[i][0]=L[S][m],dp[i][m+1]=L[S][m+1];
	for (int c=(m+1)/2;c<=m;++c)
		dp[i][c]=(L[S][c]-L[S][c+1]+modu)%modu;
}
void solve()	{
	dfs(1);
	LL ans=0;
	for (int c=0;c<=m+1;++c)
		add(ans,dp[1][c]);
	printf("%lld\n",ans);
}

int main()	{
	int icase=0;
	while (scanf("%d%d",&n,&m),n||m)	{
		init();
		printf("Case #%d: ",++icase);
		solve();
	}
	return 0;
}
