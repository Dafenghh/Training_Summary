#include<bits/stdc++.h>
#define maxn 100050
using namespace std;

const double inf=1e9;

int n;
double l[maxn],s[maxn],v[maxn];

int main()	{
	while (~scanf("%d",&n))	{
		for (int i=0;i<=n;++i)	scanf("%lf",l+i);
		for (int i=0;i<=n;++i)	scanf("%lf",s+i);
		for (int i=0;i<=n;++i)	scanf("%lf",v+i);
		double sum=0,ans=s[0]/v[0];
		for (int i=1;i<=n;++i)	{
			sum+=l[i];
			ans=max(ans,(sum+s[i])/v[i]);
//			cout<<i<<":"<<sum<<" "<<v[i]<<endl;
		}
		printf("%.9lf\n",ans);
	}
	return 0;
}
