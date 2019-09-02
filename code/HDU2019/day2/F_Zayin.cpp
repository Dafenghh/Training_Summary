#include<bits/stdc++.h>
#define maxn 3000050
#define modu 998244353
using namespace std;
typedef long long LL;

const LL inv2=(modu+1)>>1;

int n,N;
LL a[maxn];

LL sq(LL x)	{
	x%=modu;
	return x*x%modu;
}

LL C2(LL x)	{
	return x*(x-1)%modu*inv2%modu;
}

int main()	{
	while (~scanf("%d",&n))	{
		for (N=1;N<n;N<<=1);
		for (int i=0;i<N;++i)	a[i]=0;
		for (int i=0;i<n;++i)	a[i]=1;
		
//		for (int i=0;i<N;++i)	cout<<a[i]<<" "; cout<<endl;
		for (int len=2;len<=N;len<<=1)	{
			int m=len>>1;
			for (LL *p=a;p!=a+N;p+=len)
				for (int i=0;i<m;++i)	{
					LL x=p[i],y=p[i+m];
					p[i]=(x+y)%modu;
					p[i+m]=(x-y+modu)%modu;
				}
		}
		for (int i=0;i<N;++i)	a[i]=a[i]*a[i]%modu*a[i]%modu;
		for (int len=2;len<=N;len<<=1)	{
			int m=len>>1;
			for (LL *p=a;p!=a+N;p+=len)
				for (int i=0;i<m;++i)	{
					LL x=p[i],y=p[i+m];
					p[i]=(x+y)*inv2%modu;
					p[i+m]=(x-y+modu)*inv2%modu;
				}
		}
//		for (int i=0;i<N;++i)	cout<<a[i]<<" "; cout<<endl;
		LL ans1=0,ans2=0,ans=0;
		for (int i=0;i<N;++i)
			ans=(ans+C2(a[i])*sq(i))%modu;
		ans=(ans*2)%modu;
		for (int i=0;i<N;++i)
			ans1=(ans1+a[i]*i)%modu,ans2=(ans2+sq(a[i]*i))%modu;
		ans=(ans+sq(ans1)-ans2+modu)%modu*inv2%modu;
		printf("%lld\n",ans);
	}
	return 0;
}
