#include<bits/stdc++.h>
#define maxn 3005
#define modu 1000000009
using namespace std;
typedef long long LL;

int n;
char s[maxn];

int LCP[maxn][maxn];
LL dp[maxn][maxn];

void add(LL &x,LL y)	{
	x=(x+y)%modu;
}

int main()	{
	int icase=0;
	while (scanf("%s",s+1),s[1]!='-')	{
		n=strlen(s+1);
		for (int i=0;i<=n+1;++i)	LCP[i][n+1]=0;
		for (int i=n;i;--i)
			for (int j=i;j<=n;++j)
				if (s[i]==s[j])
					LCP[i][j]=LCP[i+1][j+1]+1;
				else
					LCP[i][j]=0;
					
		for (int i=1;i<=n;++i)
			for (int j=1;j<=n;++j)
				dp[i][j]=0;
		
		dp[1][1]=1;
		for (int i=1;i<=n;++i)
			for (int j=i;j<=n;++j)	{
				dp[i][j]+=dp[i][j-1];
				int k=min(LCP[i][j+1],min(j-i+1,n-j));
				if (j+k+1>n||(i+k<=j&&s[i+k]>s[j+1+k]))	continue;
				add(dp[j+1][j+1+k],dp[i][j]);
			}
		LL ans=0;
		for (int i=1;i<=n;++i)
			add(ans,dp[i][n]);
		printf("Case #%d: There are %lld ways.\n",++icase,ans);
	}
	return 0;
}