#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 LL;

struct Data	{
	LL f,g,h;
	Data (LL _f=0,LL _g=0,LL _h=0)	{
		f=_f,g=_g,h=_h;
	}
};

LL S0(LL n)	{	return n+1;	}
LL S1(LL n)	{	return n*(n+1)/2;	}
LL S2(LL n)	{	return n*(n+1)*(2*n+1)/6;	}
LL sq(LL n)	{	return n*n;	}
Data eucilid(LL a,LL b,LL c,LL n)	{
	if (!a)	return Data(b/c*S0(n),b/c*S1(n),sq(b/c)*S0(n));
	if (a>=c||b>=c)	{
		Data t=eucilid(a%c,b%c,c,n);
		a/=c,b/=c;
		return Data(t.f + a*S1(n) + b*S0(n),
					t.g + a*S2(n) + b*S1(n),
					t.h + 2*a*t.g + 2*b*t.f + 2*a*b*S1(n) + sq(a)*S2(n) + sq(b)*S0(n));
	} else	{
		LL m=(a*n+b)/c;
		Data t=eucilid(c,c-b-1,a,m-1);
		return Data(n*m-t.f,
					(m*n*(n+1)-t.f-t.h)/2,
					n*m*m-t.f-2*t.g);
	}
}

ll a,b,c,d,n,m;

LL query(LL p)	{
	return (p/d)*(d-c)+max(p%d-c+1,(LL)0);
}
LL calc(ll a)	{
	Data L=eucilid(b,a+d-c,d,m),R=eucilid(b,a,d,m);
	LL sum=(L.g-R.g)*b-((L.h-R.h)-(L.f-R.f))/2*d+(a-c+1)*(L.f-R.f)+R.f*(d-c);
	if (b*m+a>n)	sum+=query(n)-query(b*m+a);
	return sum;
}

int main()	{
	int T;
	scanf("%d",&T);
	while (T--)	{
		scanf("%lld%lld%lld%lld%lld",&a,&b,&c,&d,&n);
		m=--n/b;
		printf("%lld\n",(ll)(calc(b-1)-calc(a-1)));
	}
	return 0;
}
