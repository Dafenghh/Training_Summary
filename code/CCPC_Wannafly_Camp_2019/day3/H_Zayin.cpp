#include<bits/stdc++.h>
#define cnt(k)  T[k].cnt
#define R(k)    T[k].R
#define S(k)    T[k].S
#define maxn 200050
#define modu 998244353
#define I2 499122177
#define I6 166374059
using namespace std;
typedef long long LL;

struct VAL
{
    LL a,b,c;
    VAL(LL _a=0,LL _b=0,LL _c=0) {
        a=(modu+_a)%modu,b=(modu+_b)%modu,c=(modu+_c)%modu;
    }
    VAL operator * (const LL& f)   const   {
        return VAL(f*a,f*b,f*c);
    }
    VAL operator + (const VAL& N) const   {
        return VAL(a+N.a,b+N.b,c+N.c);
    }
};

struct node
{
    LL cnt;
    VAL R,S;
}   T[maxn<<2];

struct I    {
    int x,f,l,r;
    I(int _x=0,int _f=0,int _l=0,int _r=-1)  {
        x=_x,f=_f,l=_l,r=_r;
    }
    bool operator < (const I& I)    const   {
        return x<I.x;
    }
}   ;
vector<I> P;

int n,m;
VAL val[maxn];

LL inv(LL a)
{
    LL ans=1;
    for (int k=modu-2;k;k>>=1)
    {
        if (k&1)
            ans=ans*a%modu;
        a=a*a%modu;
    }
    return ans;
}

LL S1(LL x) {   return x*(x+1)%modu*I2%modu;  }
LL S2(LL x) {   return x*(x+1)%modu*(2*x+1)%modu*I6%modu;  }

void init()
{
    scanf("%d%*d%d",&n,&m);
    for (int i=1;i<=n;++i)
    {
        int l,r;
        scanf("%d%d",&l,&r);

        LL t=inv(S1(r-l+1));
        val[i]=VAL(-t,(l+r)*t,1LL*(l-1)*(r+1)%modu*(modu-t));
        P.push_back(I(l,1,i)),P.push_back(I(++r,-1,i));
    }
    for (int i=1;i<=m;++i)
    {
        int l,r,u,d;
        scanf("%d%d%d%d",&u,&l,&d,&r);
        P.push_back(I(l,1,u,d)),P.push_back(I(++r,-1,u,d));
    }
    sort(P.begin(),P.end());
}

void update(int k,bool f)
{
    if (cnt(k))
        S(k)=VAL();
    else
    {
        if (f)
            S(k)=R(k);
        else
            S(k)=S(k<<1)+S(k<<1|1);
    }
}

void change_val(int k,int l,int r,int p,const VAL& N)
{
    R(k)=R(k)+N;
    if (l<r)
    {
        int mid=(l+r)>>1;
        if (p<=mid)
            change_val(k<<1,l,mid,p,N);
        else
            change_val(k<<1|1,mid+1,r,p,N);
    }
    update(k,l==r);
}

void change_cnt(int k,int l,int r,int a,int b,int d)
{
    if (a<=l&&r<=b)
        cnt(k)+=d;
    else
    {
        int mid=(l+r)>>1;
        if (a<=mid)
            change_cnt(k<<1,l,mid,a,b,d);
        if (b>mid)
            change_cnt(k<<1|1,mid+1,r,a,b,d);
    }
    update(k,l==r);
}

void solve()
{
    LL ans=0;
    for (int i=0,j=0;i<P.size();i=j)
    {
        for (;j<P.size()&&P[i].x==P[j].x;++j)
            if (~P[j].r)
                change_cnt(1,1,n,P[j].l,P[j].r,P[j].f);
            else
                change_val(1,1,n,P[j].l,val[P[j].l]*P[j].f);

        if (j==P.size())    break;

        LL l=P[i].x-1,r=P[j].x-1;
        ans+=S(1).a*(S2(r)-S2(l)+modu)+S(1).b*(S1(r)-S1(l)+modu)+S(1).c*(r-l+modu);
        ans%=modu;
    }
    printf("%lld\n",ans);
}

int main()
{
    init();
    solve();
    return 0;
}
