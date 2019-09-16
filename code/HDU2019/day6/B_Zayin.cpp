#include<bits/stdc++.h>
#define maxn 50050
using namespace std;

int n;
int a[maxn],p[maxn];

int T[maxn];
int dp[maxn],prt[maxn];

int Max(int i,int j)	{
	return dp[i]>dp[j]?i:j;
}

int lowbit(int i)	{
	return i&-i;
}

void change(int x)	{
	for (int i=a[x];i<=n;i+=lowbit(i))
		T[i]=Max(T[i],x);
}

int query(int i)	{
	int p=0;
	for (;i;i-=lowbit(i))
		p=Max(p,T[i]);
	return p;
}

int Lis[maxn];

int calc()	{
	int pos=0;
	for (int i=0;i<=n;++i)	
		T[i]=0,Lis[i]=0;
	for (int i=1;i<=n;++i)	{
		if (!a[i])	continue;
		dp[i]=dp[prt[i]=query(a[i])]+1;
		change(i);
		if (dp[pos]<dp[i])
			pos=i;
	}
	for (int i=pos;i;i=prt[i])
		Lis[i]=1;
	return dp[pos];
}

int ans[maxn];

int main()	{
	int T;
	scanf("%d",&T);
	while (T--)	{
		scanf("%d",&n);
		for (int i=1;i<=n;++i)	scanf("%d",a+i);
		for (int i=1;i<=n;++i)	scanf("%d",p+i);
		int lis=calc();
		for (int k=n;k;--k)	{
			ans[k]=lis;
			a[p[k]]=0;
			if (Lis[p[k]])
				lis=calc();
		}
		for (int i=1;i<=n;++i)
			printf("%d%c",ans[i]," \n"[i==n]);
	}
	return 0;
}
