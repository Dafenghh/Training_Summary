#include<bits/stdc++.h>
#define maxn 50
#define modu 1000000007
using namespace std;
typedef long long LL;

struct Matrix	{
	static const int N=4;
	LL A[maxn][maxn];
	Matrix(LL x=0)	{
		memset(A,0,sizeof(A));
		for (int i=0;i<N;++i)
			A[i][i]=x;
	}
	Matrix operator * (const Matrix& M)	const	{
		Matrix ans;
		for (int i=0;i<N;++i)
			for (int j=0;j<N;++j)
				for (int k=0;k<N;++k)
					ans.A[i][j]=(ans.A[i][j]+A[i][k]*M.A[k][j])%modu;
		return ans;
	}
} ;

ostream& operator << (ostream& os,const Matrix& M)	{
	for (int i=0;i<Matrix::N;++i)	{
		for (int j=0;j<Matrix::N;++j)
			os<<M.A[i][j]<<" ";
		cout<<endl;
	}
	return os;
}

LL n;
LL sum[maxn];

LL calc(LL a,LL s,LL n)	{
	s-=a;
	Matrix Ans(1),A(1);
	for (int i=0;i+1<Matrix::N;++i)
		A.A[i][i+1]=1;
	for (;n;n>>=1)	{
		if (n&1)
			Ans=Ans*A;
		A=A*A;
	}
	LL ans=(a*Ans.A[0][1]+s*Ans.A[0][2]+50*Ans.A[0][3])%modu;
	return ans;
}

int main()	{
	for (int i=0;i<maxn;++i)
		sum[i]=i/2+1;
	for (int i=1;i<maxn;++i)
		sum[i]+=sum[i-1];
	cin>>n;n/=5;
	LL a=n%5;
	LL ans=calc(sum[a],sum[a+10],(n-a+10)/10)+calc(sum[a+5],sum[a+15],(n-a+5)/10);
	printf("%lld\n",ans%modu);
	return 0;
}
