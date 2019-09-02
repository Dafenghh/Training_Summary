#include<bits/stdc++.h>
#define maxh 30
#define maxn 100050
using namespace std;

const int inf=2e6;

struct node	{
	int cnt,ls,rs;
} T[maxn*maxh];
int rt[maxn],sz;
#define cnt(k)	T[k].cnt
#define ls(k)	T[k].ls
#define rs(k)	T[k].rs

int n,m;
int a[maxn];

void insert(int &k,int l,int r,int x)	{
	T[++sz]=T[k]; k=sz;
	++cnt(k);
	if (l==r)	return ;
	int mid=(l+r)>>1;
	if (x<=mid)
		insert(ls(k),l,mid,x);
	else
		insert(rs(k),mid+1,r,x);
}

int query(int k1,int k2,int l,int r,int a,int b)	{
	if (l>b||a>r)	return 0;
	if (a<=l&&r<=b)	return cnt(k2)-cnt(k1);
	int mid=(l+r)>>1;
	return query(ls(k1),ls(k2),l,mid,a,b)+query(rs(k1),rs(k2),mid+1,r,a,b);
}

int main()	{
	int T;
	scanf("%d",&T);
	while (T--)	{
		scanf("%d%d",&n,&m);
		sz=0;
		for (int i=1;i<=n;++i)	{
			scanf("%d",a+i);
			insert(rt[i]=rt[i-1],1,inf,a[i]);
		}
		int ans=0;
		while (m--)	{
			int i,j,x,k;
			scanf("%d%d%d%d",&i,&j,&x,&k);
			i^=ans,j^=ans,x^=ans,k^=ans;
			int l=0,r=1e6;
			while (l<r)	{
				int mid=(l+r)>>1;
				int L=max(1,x-mid),R=min(inf,x+mid);
				if (query(rt[i-1],rt[j],1,inf,L,R)>=k)
					r=mid;
				else
					l=mid+1;
			}
			printf("%d\n",ans=l);
		}
	}
	return 0;
}
