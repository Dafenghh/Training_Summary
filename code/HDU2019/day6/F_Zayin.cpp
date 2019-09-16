#include<bits/stdc++.h>
#define maxn 105
using namespace std;
typedef long long LL;

int n,m;
int x[maxn],y[maxn],k[maxn],r[maxn];

vector<int> X,Y;


LL count(LL n,int m)	{
	return (n+(60-m))/60;
}

int main()	{
	int T;
	scanf("%d",&T);
	while (T--)	{
		scanf("%d%d",&n,&m);
		X={0,m+1},Y={0,m+1};
		for (int i=1;i<=n;++i)	{
			scanf("%d%d%d%d",x+i,y+i,k+i,r+i);
			X.push_back(x[i]);
			Y.push_back(y[i]);
		}
		
		auto shink=[&](vector<int> &a)	{
			sort(a.begin(),a.end());
			a.resize(unique(a.begin(),a.end())-a.begin());
		};
		shink(X),shink(Y);
		
//		for (int i=0;i<=m;++i)
//			for (int j=0;j<=m;++j)	{
//				bool flag=1;
//				for (int p=1;p<=n;++p)
//					flag&=((abs(i-x[p])+abs(j-y[p]))%k[p]==r[p]);
//				if (!flag)	continue;
//				cout<<"point:"<<i<<" "<<j<<endl;
//			}
		
		LL ans=0;
		for (int i=0;i<X.size()-1;++i)
			for (int j=0;j<Y.size()-1;++j)	{
				for (int s=0;s<60;++s)
					for (int t=0;t<60;++t)	{
						bool flag=1;
						for (int p=1;p<=n;++p)	{
							int zx,zy;
							if (x[p]<=X[i])	zx=s-x[p]; else zx=x[p]-s;
							if (y[p]<=Y[j])	zy=t-y[p]; else zy=y[p]-t;
							zx%=60;
							zy%=60;
							flag&=((zx+zy+120)%k[p]==r[p]);
						}
						if (!flag)	continue;
						LL cs=count(X[i+1]-1,s)-count(X[i]-1,s);
						LL ct=count(Y[j+1]-1,t)-count(Y[j]-1,t);
						if (!cs||!ct)	continue;
//						cout<<i<<" "<<j<<" | "<<X[i]<<" "<<X[i+1]<<" "<<Y[j]<<" "<<Y[j+1]<<" | "<<s<<" "<<t<<" | "<<cs<<" "<<ct<<endl;
						ans+=cs*ct;
					}
			}
		printf("%lld\n",ans);
	}
	return 0;
}
