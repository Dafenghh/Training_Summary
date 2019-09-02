#include<bits/stdc++.h>
#define maxn 1000050
using namespace std;

int n,k,m;

vector<int> g[maxn];

bool used[maxn];

int main()	{
	int T;
	scanf("%d",&T);
	while (T--)	{
		scanf("%d%d",&n,&k),m=n/k;
		if (k==1) {
			puts("yes");
			for (int i=1;i<=n;++i)	printf("%d%c",i," \n"[i==n]);
//			puts("");
			continue;
		}
		if (n==k||((~k&1)&&(m&1)))	{
			puts("no");
			continue;
		}
		for (int i=0;i<=k;++i)	g[i].clear();
		if (~m&1)	{
			for (int t=0;t<m;t+=2)
				for (int i=1;i<=k;++i)	{
					g[i].push_back(i+t*k); 
					g[i].push_back((t+2)*k-i+1);
				}
		}  else
		if (k&1)	{
//			cout<<"in2"<<endl;
			for (int t=3;t<m;t+=2)
				for (int i=1;i<=k;++i)	{
					g[i].push_back(i+t*k);  
					g[i].push_back((t+2)*k-i+1);
				}
			for (int i=1;i<=k;++i)
				g[i].push_back(i+2*k);
			for (int i=1,j=(k+1)/2;i<=k;++i)	{
				g[j].push_back(i+k);
				if (++j>k)	j=1;
			}
			g[(k+1)/2].push_back(k);
			for (int i=1,j=k;i<k;i+=2,--j)	{
				g[j].push_back(i);
				g[j-(k+1)/2].push_back(i+1);
			}
		} 
		
		for (int i=1;i<=n;++i)	used[i]=0;
		for (int i=1;i<=k;++i)	{
			assert(g[i].size()==m);
			long long sum=0;
			for (int x:g[i])	{
				assert(!used[x]);
				sum+=x;
				used[x]=1;
			}
			assert(sum==(long long)n*(n+1)/2/k);
		}
		
		puts("yes");
		for (int i=1;i<=k;++i)	{
			for (int j=0;j<g[i].size();++j)
				printf("%d%c",g[i][j]," \n"[j==m-1]);
//			puts("");
		}
	}
	return 0;
}
