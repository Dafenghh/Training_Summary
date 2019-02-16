#include<bits/stdc++.h>
#define maxn 100050
using namespace std;

int n,m;
vector<int> G[maxn];

int fa[maxn];
double p[maxn],snp[maxn];

void init()
{
	scanf("%d",&n);
	p[n]=1;
	for (int i=0;i<n;++i)
		scanf("%lf",&p[i]);
	for (int k=1;k<n;++k)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	G[n].push_back(0);
}

double ans;

void dfs(int i)
{
	for (int j:G[i])
	{
		if (fa[i]==j)	continue;
		fa[j]=i;
		dfs(j);
		snp[i]+=1-p[j];
	}
//	cout<<i<<" "<<sp[i]<<endl;
	ans+=p[i]*snp[i];
}

void solve()
{
	fa[n]=-1,dfs(n);
//	cout<<"init:"<<ans<<endl;
	scanf("%d",&m);
	while (m--)
	{
		int i;
		double P;
		scanf("%d%lf",&i,&P);
		ans+=p[fa[i]]*((1-P)-(1-p[i]));
		snp[fa[i]]+=(1-P)-(1-p[i]);
		ans+=(P-p[i])*snp[i];
		p[i]=P;
		printf("%.9lf\n",ans);
	}
}

int main()
{
	init();
	solve();
	return 0;
}