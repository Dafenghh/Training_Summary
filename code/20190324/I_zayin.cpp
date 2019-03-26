#include<bits/stdc++.h>
#define maxn 100050
#define x(i)	P[i].x
#define y(i)	P[i].y
using namespace std;
typedef long long LL;

struct point	{
	LL x,y;
	point(LL _x=0,LL _y=0)	{	x=_x,y=_y;	}
	point operator - (const point& P) const	{	return point(x-P.x,y-P.y);	}
	LL operator * (const point& P) const	{	return x*P.y-y*P.x;	}
}	P[maxn];

struct ration	{
	LL p,q;
	ration(LL _p=0,LL _q=1)	{	p=_p,q=_q;	}
	bool operator < (const ration& R) const {	return p*R.q-q*R.p<0;	}
	bool operator > (const ration& R) const {	return p*R.q-q*R.p>0;	}
	bool operator <= (const ration& R) const {	return p*R.q-q*R.p<=0;	}
	bool operator == (const ration& R) const {	return p*R.q==q*R.p;	}
}	L[maxn],R[maxn];

ostream& operator << (ostream& os,const ration& R)	{
//	os<<R.p<<"/"<<R.q;
	os<<1.0*R.p/R.q;
	return os;
}
ostream& operator << (ostream& os,const point& P)	{
	os<<"("<<P.x<<","<<P.y<<")";
	return os;
}

int n,H;
int t[maxn];

void init()	{
	scanf("%d%d",&n,&H);
	for (int i=1;i<=n;++i)
		scanf("%d%d%d",&x(i),&y(i),t+i);
}

int stk[maxn],tp;
ration deal(int i,int j)	{
	point t1=P[j]-P[i],t2=point(-x(i),H-y(i));
//	cout<<i<<" "<<j<<" "<<t1<<" "<<t2<<" "<<t1*t2<<endl;
	return ration(t1*t2,t1.y);
}
void predo()	{
	for (int i=1;i<=n;++i)	L[i]=0,R[i]=x(n);
	tp=0;
	for (int i=1;i<=n;++i)	{
		while (tp>1&&(P[stk[tp-1]]-P[i])*(P[stk[tp]]-P[i])>=0)	--tp;
		stk[++tp]=i;
		if (!t[i]) continue;
		if (tp>1&&y(stk[tp-1])>y(i))
			L[i]=deal(i,stk[tp-1]);
	}
	tp=0;
	for (int i=n;i;--i)	{
		while (tp>1&&(P[stk[tp]]-P[i])*(P[stk[tp-1]]-P[i])>=0)	--tp;
		stk[++tp]=i;
		if (!t[i]) continue;
		if (tp>1&&y(stk[tp-1])>y(i))
			R[i]=deal(i,stk[tp-1]);
	}
}

int pos[maxn];
bool cmp(int i,int j)	{	return R[i]<R[j]||(R[i]==R[j]&&L[i]<L[j]);	}
void solve()	{
	for (int i=1;i<=n;++i)	pos[i]=i;
	sort(pos+1,pos+n+1,cmp);
//	for (int i=1;i<=n;++i)	cout<<pos[i]<<": ["<<L[pos[i]]<<","<<R[pos[i]]<<"]"<<endl;
	ration last=-(1LL<<40);
	int ans=0;
	for (int i=1;i<=n;++i)	{
		if (L[pos[i]]<=last&&last<=R[pos[i]])	continue;
		++ans;
		last=R[pos[i]];
	}
	printf("%d\n",ans);
}

int main()	{
	init();
	predo();
	solve();
	return 0;
}

