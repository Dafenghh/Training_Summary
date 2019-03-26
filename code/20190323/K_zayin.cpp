#include<bits/stdc++.h>
#define maxn 10005
using namespace std;

int n,m;
int pos[maxn];
int d[maxn],D[maxn];

queue<int> q;

bool cmpd(int i,int j)	{
	return d[i]<d[j];
}
bool cmpD(int i,int j)	{
	return D[i]>D[j];
}

int main()	{
	scanf("%d%d",&n,&m);
	while (m--)	{
		int u,v;
		scanf("%d%d",&u,&v);
		++d[u],++d[v];
	}
	for (int i=0;i<n;++i)	pos[i]=i;
	sort(pos,pos+n,cmpd);
//	for (int i=0;i<n;++i)	cout<<d[i]<<" "; cout<<endl;
	int ans=n,t=2*n-2;
	for (int k=0;k<n;++k)	{
		int i=pos[k];
		D[i]=min(t-(n-k-1),d[i]);
		if (d[i]==D[i])	--ans;
		t-=D[i];
	}
	printf("%d\n%d %d\n",ans,n,n-1);
	
	sort(pos,pos+n,cmpD);
	for (int k=0;k<n;++k)	{
		int i=pos[k];
		if (k)	{
			assert(q.size());
			cout<<i<<" "<<q.front()<<endl;
			q.pop();
		}
		for (int j=1;j<=D[i]-(bool)k;++j)
			q.push(i);
	}
	return 0;
}
