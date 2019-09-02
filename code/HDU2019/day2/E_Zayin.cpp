#include<bits/stdc++.h>
#define maxn 3050
#define modu 998244353
using namespace std;
typedef long long LL;

LL f[maxn];

LL pw2[maxn];
LL C[maxn][maxn];

LL inv(LL a)	{
	LL ans=1;
	for (int k=modu-2;k;k>>=1)	{
		if (k&1)
			ans=ans*a%modu;
		a=a*a%modu;
	}
	return ans;
}

LL g(int n)	{
	return n*(n-1)*inv(4)%modu;
}

int main()	{
	for (int i=pw2[0]=1;i<maxn;++i)	pw2[i]=pw2[i-1]*2%modu;
	for (int i=C[0][0]=1;i<maxn;++i)
		for (int j=C[i][0]=1;j<=i;++j)
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%modu;
	for (int i=2;i<maxn;++i)	{
		f[i]=pw2[i]*g(i)%modu;
		for (int j=0;j<i;++j)
			f[i]=(f[i]+f[j]*C[i][j])%modu;
//		cout<<i<<" "<<f[i]<<endl;
		f[i]=f[i]*inv(pw2[i]-1)%modu;
	}
	
	int n;
	while (~scanf("%d",&n))	{
		LL ans=0;
		for (int i=1;i<=n;++i)
			ans=(ans+f[i])%modu;
		printf("%lld\n",ans*inv(n)%modu);
	}
	return 0;
}
