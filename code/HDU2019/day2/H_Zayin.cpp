#include<bits/stdc++.h>
#define maxn 1505
#define maxm 200050
using namespace std;
typedef long long LL;

const int inf=1e9;

int n,m,vs,vt;

int tot;
int cap[maxm<<1];
int head[maxn],edge[maxm<<1],nxt[maxm<<1];

int flow[maxn];
int prt[maxn],cur[maxn];

int d[maxn],gap[maxn];

void join(int u,int v,int w)	{
	cap[tot]=w; edge[tot]=v; nxt[tot]=head[u]; head[u]=tot++;
	cap[tot]=w; edge[tot]=u; nxt[tot]=head[v]; head[v]=tot++;
}

int augment()	{
	int a=flow[vt];
	for (int i=vt;i!=vs;i=edge[prt[i]^1])
		cap[prt[i]]-=a,cap[prt[i]^1]+=a;
	return a;
}


LL isap()	{
	LL ans=0;
	memset(gap,0,sizeof(gap));
	for (int i=1;i<=vt;++i)	++gap[d[i]=0],cur[i]=head[i];
	int i=vs;
	flow[vs]=inf;
	while (d[vs]<vt)	{
		if (i==vt)
			ans+=augment(),i=vs;
		bool flag=0;
		for (int k=cur[i];~k;k=nxt[k])	{
			int j=edge[k];
			if (cap[k]&&d[i]==d[j]+1)	{
				flag=1;
				cur[i]=prt[j]=k;
				flow[j]=min(flow[i],cap[k]);
				i=j;
				break;
			}
		}
		if (flag)	continue;
		if (--gap[d[i]]==0)	break;
		d[i]=vt;
		for (int k=head[i];~k;k=nxt[k])
			if (cap[k])
				d[i]=min(d[i],d[edge[k]]+1);
		++gap[d[i]];
		cur[i]=head[i];
		if (i!=vs)
			i=edge[prt[i]^1];
	}
	return ans;
}

int main()	{
	while (~scanf("%d%d",&n,&m))	{
		vs=n+1,vt=n+2;
		tot=0;
		for (int i=1;i<=vt;++i)
			head[i]=-1;
//		memset(head,-1,sizeof(head));
		LL ans=0;
		while (m--)	{
			int u,v,a,b,c;
			scanf("%d%d%d%d%d",&u,&v,&a,&b,&c);
			ans+=a+b+c;
			join(vs,u,a+b),join(vs,v,a+b);
			join(u,v,a+c-b-b);
			join(u,vt,b+c),join(v,vt,b+c);
		}
		printf("%lld\n",ans-(isap()>>1));
	}
	return 0;
}
