#include<bits/stdc++.h>
#define y second
#define maxn 2000050
using namespace std;
typedef long long LL;

struct bus	{
	int a,b;
	LL s,t;
	double p;
	void read()	{	scanf("%d%d%lld%lld%lf",&a,&b,&s,&t,&p);	}
	bool operator < (const bus& B)		const	{
		return s>B.s;
	}
}	B[maxn];
int n,m;
LL K;

map<LL,double> dp[maxn];

int main()	{
	scanf("%d%d%lld",&m,&n,&K);
	for (int i=0;i<m;++i) B[i].read();
	sort(B,B+m);
	for (int i=0;i<n;++i) dp[i][K+1]=(i==1);
	for (int i=0;i<m;++i)	{
		double s=dp[B[i].a].begin()->y,t=dp[B[i].a].upper_bound(B[i].s)->y;
		dp[B[i].a][B[i].s]=max(s,B[i].p*dp[B[i].b].upper_bound(B[i].t)->y+(1-B[i].p)*t);
	}
	printf("%.9lf\n",dp[0].begin()->y);
	return 0;
}
