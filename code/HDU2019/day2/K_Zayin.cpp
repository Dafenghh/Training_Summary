#include<bits/stdc++.h>
#define maxl 47
#define maxn 100050
using namespace std;
typedef long long LL;

int n,m;
int a[maxn];

struct node	{
	int len,a[maxl];
} T[maxn<<2];
#define a(k) T[k].a
#define len(k)	T[k].len

const int t1=0,t2=(maxn<<2)-2;

void merge(int k,int ls,int rs)	{
	len(k)=min(len(ls)+len(rs),maxl);
	int pl=0,pr=0;
	for (int t=0;t<len(k);++t)	{
		if (pl==len(ls)||(pr<len(rs)&&a(ls)[pl]<a(rs)[pr]))
			a(k)[t]=a(rs)[pr++];
		else
			a(k)[t]=a(ls)[pl++];
	}
}

void build(int k,int l,int r)	{
	len(k)=0;
	if (l==r)	{
		a(k)[len(k)++]=a[l];
	} else	{
		int mid=(l+r)>>1;
		build(k<<1,l,mid);
		build(k<<1|1,mid+1,r);
		merge(k,k<<1,k<<1|1);
	}
}

void query(int k,int l,int r,int a,int b)	{
	if (a<=l&&r<=b)	{
		T[t2]=T[t1];
		merge(t1,t2,k);
	} else	{
		int mid=(l+r)>>1;
		if (a<=mid)	query(k<<1,l,mid,a,b);
		if (b>mid)	query(k<<1|1,mid+1,r,a,b);
	}
}

int main()	{
	while (~scanf("%d%d",&n,&m))	{
		for (int i=1;i<=n;++i)
			scanf("%d",a+i);
		build(1,1,n);
		while (m--)	{
			int l,r,t;
			scanf("%d%d",&l,&r);
			len(t1)=0;
			query(1,1,n,l,r);
			LL ans=-1;
			for (int i=2;i<len(t1);++i)	{
				if (a(t1)[i-2]<a(t1)[i]+a(t1)[i-1])
					ans=max(ans,(LL)a(t1)[i-2]+a(t1)[i-1]+a(t1)[i]);
			}
			printf("%lld\n",ans);
		}
	}
	return 0;
}
