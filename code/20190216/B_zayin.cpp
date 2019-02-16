#include<bits/stdc++.h>
#define maxn 800050
using namespace std;
typedef long long LL;

int n,m,a[maxn];

int N,s[maxn],t[maxn];

LL st,sum[maxn];

void init()
{
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;++i)
		scanf("%d",a+i);
	sort(a,a+n);
	
	for (int i=0,j;i<n;i=j+1)
	{
		for (j=i;j<n&&a[j]+1==a[j+1];)	++j;
//		cout<<"black:"<<i<<" "<<j<<endl;
		s[N++]=a[j]-a[i]+1;
		if (j<n-1)
			s[N++]=-(a[j+1]-a[j]-1);
	}
	
	if (a[0]!=0||a[n-1]!=m-1)
		s[N++]=-((a[0]+m)-a[n-1]-1),st=a[0];
	else
	{
		st=a[n-1]-s[N-1]+1;
		s[0]+=s[--N];
	}
	
	for (int i=0;i<N;++i)
		t[i]=s[i];
	reverse(t,t+N);
	for (int i=0;i<N-1;++i)
		t[i+N]=t[i];
	
	sum[0]=abs(s[0]);
	for (int i=1;i<N;++i)
		sum[i]=sum[i-1]+abs(s[i]);
	
/*	cout<<"st:"<<st<<endl;
	for (int i=0;i<N;++i)	cout<<s[i]<<" "; cout<<endl;
	for (int i=0;i<(2*N-1);++i)	cout<<t[i]<<" "; cout<<endl;*/
	
}

vector<int> A;

int nxt[maxn];

void solve()
{
	int i,j;
	for (nxt[0]=j=-1,i=1;i<N;nxt[i++]=j)	{
		while (~j&&s[j+1]!=s[i])	j=nxt[j];
		if (s[j+1]==s[i])	++j;
	}
	
	for (j=-1,i=0;i<(2*N-1);++i)	{
		while (~j&&s[j+1]!=t[i])	j=nxt[j];
		if (s[j+1]==t[i])	++j;
		if (j==N-1)
		{
			int p=N-1-(i-N+1);
//			printf("find:%d %d %lld %lld\n",i,p,sum[p],(sum[p]+st-1+st)%m);
			A.push_back((sum[p]+st-1+st)%m);
			j=nxt[j];
		}
	}
	
	sort(A.begin(),A.end());
	printf("%d\n",A.size());
	for (int i:A)
		printf("%d ",i);
}

int main()
{
	init();
	solve();
	return 0;
}
