#include<bits/stdc++.h>
#define mn(k)	T[k].mn
#define se(k)	T[k].se
#define cnt(k)	T[k].cnt
#define sum(k)	T[k].sum
#define tag(k)	T[k].tag
#define maxn 100050
#define inf 0x3f3f3f3f
using namespace std;
typedef long long LL;

int n,m;

struct node	{
	LL mn,se,cnt,sum,tag;
}	T[maxn<<2];

LL gcd(LL a,LL b)	{	return !b?a:gcd(b,a%b);	}

void build(int k,int l,int r)	{
	mn(k)=sum(k)=0,cnt(k)=r-l+1,se(k)=inf,tag(k)=0;
	if (l==r)	return ;
	int mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
}

bool renew(int k,LL x)	{
	if (mn(k)>=x)	return 1;
	if (se(k)>=x)	{
		sum(k)+=(x-mn(k))*cnt(k);
		tag(k)=mn(k)=x;
		return 1;
	}
	return 0;
}

void godown(int k)	{
	if (!tag(k))	return;
	renew(k<<1,tag(k)),renew(k<<1|1,tag(k));
	tag(k)=0;
}

void update(int k)	{
	int ls=k<<1,rs=k<<1|1;
	sum(k)=sum(ls)+sum(rs);
	if (mn(ls)>mn(rs))	swap(ls,rs);
	mn(k)=mn(ls),cnt(k)=cnt(ls);
	if (mn(ls)==mn(rs))	{
		cnt(k)+=cnt(rs);
		se(k)=min(se(ls),se(rs));
	}	else	{
		se(k)=min(se(ls),mn(rs));
	}
}

void change(int k,int l,int r,int a,int b,LL x)	{
	if (a<=l&&r<=b)
		if (renew(k,x))	{
			return ;
		}
	godown(k);
	int mid=(l+r)>>1;
	if (a<=mid)	change(k<<1,l,mid,a,b,x);
	if (b>mid)	change(k<<1|1,mid+1,r,a,b,x);
	update(k);
}

LL query(int k,int l,int r,int a,int b)	{
	if (a>r||l>b)	return 0;
	if (a<=l&&r<=b)	return sum(k);
	godown(k);
	int mid=(l+r)>>1;
	return query(k<<1,l,mid,a,b)+query(k<<1|1,mid+1,r,a,b);
}

int main()	{
	while (scanf("%d%d",&n,&m),n||m)	{
		build(1,1,n);
		char op[5];
		int l,r,x;
		while (m--)	{
			scanf("%s%d%d",op,&l,&r);
			if (*op=='?')	{
				LL p=query(1,1,n,l,r),q=r-l+1,g=gcd(p,q);
				if (q==g)
					printf("%lld\n",p/g);
				else
					printf("%lld/%lld\n",p/g,q/g);
			}	else	{
				scanf("%d",&x);
				change(1,1,n,l,r,x);
			}
		}
	}
	return 0;
}
