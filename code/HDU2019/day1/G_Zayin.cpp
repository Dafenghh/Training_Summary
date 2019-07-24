#include<bits/stdc++.h>
#define maxn 1000050
using namespace std;
typedef long long LL;

LL n,k;

struct Frac {
    LL p,q;
    Frac(LL _p=0,LL _q=1)   {
        LL g=__gcd(_p,_q);
        p=_p/g,q=_q/g;
    }
    Frac operator + (const Frac& f) const   {
        LL t=__gcd(q,f.q);
        return Frac(f.q/t*p+q/t*f.p,q/t*f.q);
    }
    Frac operator / (const LL& x)   const   {
        return Frac(p,x*q);
    }
}; 

ostream& operator << (ostream& os,Frac f)   {
    os<<f.p<<"/"<<f.q;
    return os;
}

bool noprime[maxn];
int p[maxn],pnum;

int mu[maxn],sum[maxn];

void predo()    {
    mu[1]=1;
    for (int i=2;i<maxn;++i)    {
        if (!noprime[i])
            mu[p[pnum++]=i]=-1;
        for (int j=0;j<pnum&&i*p[j]<maxn;++j)   {
            noprime[i*p[j]]=1;
            if (i%p[j])
                mu[i*p[j]]=-mu[i];
            else
                break;
        }
    }
    for (int i=1;i<maxn;++i)
        sum[i]=sum[i-1]+mu[i];
}

void init() {
    scanf("%lld%lld",&n,&k);
}

LL S0(LL n)	{	return n+1;	}
LL S1(LL n)	{	return n*(n+1)/2;	}

LL f(LL a,LL b,LL c,LL n)   {
	if (!a)	return b/c*S0(n);
	if (a>=c||b>=c)	{
		LL t=f(a%c,b%c,c,n);
		a/=c,b/=c;
		return t + a*S1(n) + b*S0(n);
	} else	{
		LL m=(a*n+b)/c;
		LL t=f(c,c-b-1,a,m-1);
		return n*m-t;
	}
}

LL calc(Frac a) {
    LL ans=0;
    for (int i=1,j;i<=n;i=j+1)  {
        j=n/(n/i);
        ans+=(sum[j]-sum[i-1])*f(a.p,0,a.q,n/i);
    }
    return ans;
}

void print(Frac a)  {
    Frac l(0,1),r(1,0),ans;
    LL x=a.p,y=a.q;
    while (x!=y)    {
        Frac mid(l.p+r.p,l.q+r.q);
        if (mid.p>n||mid.q>n) break;
        if (x<y)    {
            y-=x;
            r=mid;
            ans=mid;
        } else  {
            x-=y;
            l=mid;
        }
    }
    printf("%lld/%lld\n",ans.p,ans.q);
}

void solve()    {
    Frac l(0,1),r=(1,1);
    for (int t=0;t<40;++t)  {
        Frac mid=(l+r)/2;
        if (calc(mid)<k)
            l=mid;
        else
            r=mid;
    }
    print(l);
}

int main()  {
    predo();

    int T;
    scanf("%d",&T);
    while (T--) {
        init();
        solve();
    }
    return 0;
}
