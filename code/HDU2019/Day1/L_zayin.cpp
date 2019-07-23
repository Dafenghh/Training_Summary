#include<bits/stdc++.h>
#define maxn 500050
#define modu 998244353
using namespace std;
typedef long long LL;

LL pw(LL a,LL k=modu-2)	{
	LL ans=1;
	for (;k;k>>=1)	{
		if (k&1)
			ans=ans*a%modu;
		a=a*a%modu;
	}
	return ans;
}

struct NTT	{
	LL I,w[maxn];
	int N,rev[maxn];
	
	void init(int n)	{
		for (N=1;N<=n;N<<=1)	;	I=pw(N);
		
		rev[0]=0,rev[1]=N>>1;
		for (int i=2;i<N;++i)
			rev[i]=rev[i>>1]>>1|rev[i&1];
		
		w[0]=1,w[1]=pw(3,(modu-1)/N);
		for (int i=2;i<N;++i)
			w[i]=w[i-1]*w[1]%modu;
	}
	
	void DFT(LL A[])	{
		for (int i=0;i<N;++i)
			if (i<rev[i])
				swap(A[i],A[rev[i]]);
		for (int len=2;len<=N;len<<=1)	{
			int m=len>>1;
			for (LL *p=A;p!=A+N;p+=len)
				for (int i=0;i<m;++i)	{
					LL u=p[i],v=p[i+m]*w[N/len*i]%modu;
					p[i]=(u+v)%modu;
					p[i+m]=(u-v+modu)%modu;
				}
		}
	}
	
	void IDFT(LL A[])	{
		DFT(A);
		reverse(A+1,A+N);
		for (int i=0;i<N;++i)
			A[i]=A[i]*I%modu;
	}
	
} T;

int n,m;
LL a[maxn],b[maxn];

LL F[maxn]={1,1},I[maxn]={1,1};

int cnt[4];

LL C(int n,int m)	{
	return n<m?0:F[n]*I[m]%modu*I[n-m]%modu;
}

void init()	{
	scanf("%d%d",&n,&m);
	T.init(2*n);
	for (int i=0;i<T.N;++i)	a[i]=0;
	for (int i=0;i<4;++i)	cnt[i]=0;
	for (int i=0;i<n;++i)	scanf("%lld",a+i),a[i]%=modu;
	for (int i=0;i<m;++i)	{
		int x;
		scanf("%d",&x);
		++cnt[x];
	}
}

void solve()	{
//	cout<<cnt[0]<<" "<<cnt[1]<<" "<<cnt[2]<<" "<<cnt[3]<<endl;
	for (int c=1;c<=3;++c)	{
		for (int i=0;i<T.N;++i)	b[i]=0;
		if (!cnt[c])	continue;
		for (int i=0;i<n;++i)	{
			if (i%c) continue;
			int t=i/c;
			b[i]=C(t+cnt[c]-1,t);
//			cout<<i<<":"<<t<<" "<<b[i]<<endl;
		}
//		for (int i=0;i<n;++i)	cout<<b[i]<<" "; cout<<endl;
		T.DFT(b),T.DFT(a);
		for (int i=0;i<T.N;++i)	a[i]=a[i]*b[i]%modu;
		T.IDFT(a);
		for (int i=n;i<T.N;++i)	a[i]=0;
//		for (int i=0;i<T.N;++i)	cout<<a[i]<<" "; cout<<endl;
	}
	LL ans=0;
	for (int i=0;i<n;++i)
		ans^=(i+1)*a[i];
	printf("%lld\n",ans);
}

//LL aa[maxn]={1,0,2,0,3,0,4,0,5,0,4,0,3,0,2,0,1},bb[maxn]={1,6,16,34,59,90,123,159};

int main()	{
	for (int i=2;i<maxn;++i)	F[i]=F[i-1]*i%modu;
	for (int i=2;i<maxn;++i)	I[i]=modu-modu/i*I[modu%i]%modu;
	for (int i=2;i<maxn;++i)	I[i]=I[i]*I[i-1]%modu;
	
	int T;
	scanf("%d",&T);
	while (T--)	{
		init();
		solve();
	}
	return 0;
}
