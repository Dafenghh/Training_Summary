#include<bits/stdc++.h>
#define maxn 200050
using namespace std;

int tot;
int cost[maxn<<1];
int head[maxn],edge[maxn<<1],nxt[maxn<<1];

vector<pair<int,int> > G[maxn];

int con[maxn];
vector<int> upl[maxn][2],upr[maxn][2];
int down[maxn][2];
int dp[maxn][2];

void join(int u,int v,int w)	{
	cost[tot]=w; edge[tot]=v; nxt[tot]=head[u]; head[u]=tot++;
	cost[tot]=w; edge[tot]=u; nxt[tot]=head[v]; head[v]=tot++;
}

void dfs1(int i,int fa)	{
	G[i].resize(1);
	for (int k=head[i];~k;k=nxt[k])	{
		int j=edge[k];
		if (fa==j)	continue;
		dfs1(j,i);
		con[j]=min(dp[j][1]+cost[k],dp[j][0]);
		G[i].push_back(make_pair(j,cost[k]));
	}
	for (int c=0;c<=1;++c)
		upl[i][c].resize(G[i].size()+1),upr[i][c].resize(G[i].size()+1);
		
	upl[i][0][0]=upl[i][1][0]=0;
	for (int k=1;k<G[i].size();++k)	{
		int j=G[i][k].first,w=G[i][k].second;
		upl[i][0][k]=max(upl[i][0][k-1],dp[j][0]+w);
		upl[i][1][k]=min(max(upl[i][1][k-1],dp[j][0]+w),max(upl[i][0][k-1],con[j]));
	}
	
	upr[i][0][G[i].size()]=upr[i][1][G[i].size()]=0;
	for (int k=G[i].size()-1;k;--k)	{
		int j=G[i][k].first,w=G[i][k].second;
		upr[i][0][k]=max(upr[i][0][k+1],dp[j][0]+w);
		upr[i][1][k]=min(max(upr[i][1][k+1],dp[j][0]+w),max(upr[i][0][k+1],con[j]));
//		cout<<i<<" "<<k<<":"<<j<<"("<<con[j]<<") "<<w<<" ~ "<<max(upr[i][k+1][1],dp[j][0]+w)<<" "<<max(upr[i][k+1][0],con[j])<<" "<<min(max(upr[i][k+1][1],dp[j][0]+w),max(upr[i][k+1][0],con[j]))<<" "<<upr[i][k][1]<<endl;
	}
	
	dp[i][0]=upr[i][0][1];
	dp[i][1]=upr[i][1][1];
//	cout<<"up:"<<i<<" "<<dp[i][0]<<" "<<dp[i][1]<<endl;
//	cout<<"G["<<i<<"]:"; for (int k=1;k<G[i].size();++k)	cout<<G[i][k].first<<" "; cout<<endl;
//	cout<<"upl["<<i<<"][0]:"; for (int k=1;k<G[i].size();++k)	cout<<upl[i][k][0]<<" "; cout<<endl;
//	cout<<"upl["<<i<<"][1]:"; for (int k=1;k<G[i].size();++k)	cout<<upl[i][k][1]<<" "; cout<<endl;
//	cout<<"upr["<<i<<"][0]:"; for (int k=1;k<G[i].size();++k)	cout<<upr[i][k][0]<<" "; cout<<endl;
//	cout<<"upr["<<i<<"][1]:"; for (int k=1;k<G[i].size();++k)	cout<<upr[i][k][1]<<" "; cout<<endl;
}

int min(int a,int b,int c,int d)	{
	return min(min(a,d),min(b,c));
}
int max(int a,int b,int c)	{
	return max(a,max(b,c));
}

void dfs2(int i,int fa)	{
	for (int k=1;k<G[i].size();++k)	{
		int j=G[i][k].first,w=G[i][k].second;
		down[j][0]=max(down[i][0],upl[i][0][k-1],upr[i][0][k+1])+w;
		down[j][1]=min(
						w+max(down[i][1],upl[i][0][k-1],upr[i][0][k+1]),
						w+max(down[i][0],upl[i][1][k-1],upr[i][0][k+1]),
						w+max(down[i][0],upl[i][0][k-1],upr[i][1][k+1]),
						  max(down[i][0],upl[i][0][k-1],upr[i][0][k+1])
						);
		dfs2(j,i);
	}
//	cout<<"down:"<<i<<" "<<down[i][0]<<" "<<down[i][1]<<endl;
}

int n;

int main()	{
	int T;
	scanf("%d",&T);
	while (T--)	{
		tot=0;
		memset(head,-1,sizeof(head));
		
		scanf("%d",&n);
		for (int k=1;k<n;++k)	{
			int u,v,w;
			scanf("%d%d%d",&u,&v,&w);
			join(u,v,w);
		}
		dfs1(1,0);
		dfs2(1,0);
		int ans=1e9,k=-1;
		for (int i=1;i<=n;++i)	{
			int t=min(max(down[i][1],dp[i][0]),max(down[i][0],dp[i][1]));
			if (ans>t)
				ans=t,k=i;
		}
		printf("%d %d\n",k,ans);
	}
	return 0;
}
