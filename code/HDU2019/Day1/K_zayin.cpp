#include<bits/stdc++.h>
#define maxn 10000050
#define modu 998244353
using namespace std;
typedef long long LL;

bool noprime[maxn];
int p[maxn],pnum;

int mu[maxn],phi[maxn];

LL pw(LL a,LL k=modu-2)	{
	LL ans=1;
	for (;k;k>>=1)	{
		if (k&1)
			ans=ans*a%modu;
		a=a*a%modu;
	}
	return ans;
}

const LL inv6=pw(6);

void predo()	{
	phi[1]=mu[1]=1;
	for (int i=2;i<maxn;++i)	{
		if (!noprime[i])	{
			mu[i]=-1;
			phi[p[pnum++]=i]=i-1;
		}
		for (int j=0;j<pnum&&i*p[j]<maxn;++j)	{
			noprime[i*p[j]]=1;
			if (i%p[j])
				mu[i*p[j]]=-mu[i],
				phi[i*p[j]]=phi[i]*(p[j]-1);
			else	{
				phi[i*p[j]]=phi[i]*p[j];
				break;
			}
		}
//		if (i>30)	continue;
//		cout<<i<<":"<<mu[i]<<endl;
	}
}

__int128 n;
char s[100];

LL N;

__int128 sqrt3(__int128 n)	{
	__int128 l=0,r=maxn;
	while (l<r)	{
		__int128 mid=(l+r+1)/2;
		if (mid*mid*mid<=n)
			l=mid;
		else
			r=mid-1;
	}
	return l;
}

__int128 sqr3(__int128 x)	{	return x*x*x;	}

void init()	{
	n=0;
	scanf("%s",s);
	for (int i=0;s[i];++i)
		n=n*10+s[i]-'0';
	N=(LL)sqrt3(n);
//	cout<<"N:"<<N<<endl;
}

LL S0(LL n)	{	return n;	}
LL S1(LL n)	{	return n*(n+1)/2%modu;	}
LL S2(LL n)	{	return n*(n+1)%modu*(2*n+1)%modu*inv6%modu; }

LL calc1_bf(LL n)	{
	LL ans=0;
	for (int i=1;i<=n;++i)
		for (int j=sqr3(i);j<sqr3(i+1);++j)
			for (int d=1;d<=n;++d)
				if (i%d==0&&j%d==0)
					ans+=phi[d];
	return ans;
}

LL calc1(LL n)	{
	LL ans=0;
	for (int d=1;d<=n;++d)	{
		LL k=n/d;
		LL t=(3*S2(k)*d+3*S1(k)+S0(k))%modu;
		LL bf=0;
		for (int i=d;i<=n;i+=d)
			bf+=(sqr3(i+1)-1)/d-(sqr3(i)-1)/d;
//		cout<<d<<":"<<k<<" "<<t<<" "<<bf<<endl;
		ans=(ans+phi[d]*t+modu)%modu;
	}
	return ans;
}

LL calc2(LL n,__int128 l,__int128 r)	{
	LL ans=0;
	for (LL t,i=1;i*i<=n;++i)	{
		if (n%i)	continue;
		t=r/i-(l-1)/i;
		ans=(ans+phi[i]*t+modu)%modu;
		if (i*i==n)	continue;
		LL j=n/i;
		t=r/j-(l-1)/j;
		ans=(ans+phi[j]*t+modu)%modu;
	}
	return ans;
}

void solve()	{
	LL ans1=calc1(N-1),ans2=calc2(N,sqr3(N),n);
	LL ans=(ans1+ans2)%modu;
	//cout<<ans1<<"+"<<ans2<<"="<<ans<<" ~ "<<calc1_bf(N-1)<<endl;
	printf("%lld\n",ans);
}

int main()	{
	predo();
	int T;
	scanf("%d",&T);
	while (T--)	{
		init();
		solve();
	}
	return 0;
}