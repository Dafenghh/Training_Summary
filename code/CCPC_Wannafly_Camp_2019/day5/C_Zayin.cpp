#include<bits/stdc++.h>
#define ls(k)   T[k].ls
#define rs(k)   T[k].rs
#define sum(k)  T[k].sum
#define cnt(k)  T[k].cnt
#define maxh 30
#define maxn 500050
#define M 1000000000
using namespace std;
typedef long long LL;

int sz,root[maxn];
struct node
{
    int ls,rs;
    LL sum,cnt;
}   T[maxn*maxh];

int n,m;
int a[maxn];

LL val[maxn],sum[maxn];
int cnt[maxn];

LL ans[maxn];
int L[maxn],R[maxn],K[maxn];

void init()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;++i)
        scanf("%d",a+i),sum[i]=sum[i-1]+a[i];
    for (int i=0;i<m;++i)
        scanf("%d%d%d",L+i,R+i,K+i),ans[i]=sum[R[i]]-sum[L[i]-1];
}

void change(int &k,int l,int r,int x)
{
    T[++sz]=T[k]; k=sz;
    ++cnt(k),sum(k)+=x;
    if (l==r)   return ;
    int mid=(l+r)>>1;
    if (x<=mid)
        change(ls(k),l,mid,x);
    else
        change(rs(k),mid+1,r,x);
}

LL query(int k1,int k2,int l,int r,LL c)
{
    if (cnt(k2)-cnt(k1)<=c)  return sum(k2)-sum(k1);
    if (l==r)   return l*c;
    int mid=(l+r)>>1,t=cnt(rs(k2))-cnt(rs(k1));
    if (t>=c)
        return query(rs(k1),rs(k2),mid+1,r,c);
    else
        return query(ls(k1),ls(k2),l,mid,c-t)+(sum(rs(k2))-sum(rs(k1)));
}


void solve()
{
    for (int b=30;~b;--b)
    {
        sz=0;
        for (int i=1;i<=n;++i)
        {
            val[i]=0;
            cnt[i]=cnt[i-1];
            root[i]=root[i-1];
            if (a[i]>=(1<<b))
            {
                ++cnt[i];
                val[i]=a[i]-(a[i]>>1);
                a[i]>>=1;
                change(root[i],1,M,val[i]);
            }
            sum[i]=sum[i-1]+val[i];
        }


        for (int i=0;i<m;++i)
        {
            if (!K[i])  continue;
            if (K[i]>=cnt[R[i]]-cnt[L[i]-1])
            {
                K[i]-=cnt[R[i]]-cnt[L[i]-1];
                ans[i]-=sum[R[i]]-sum[L[i]-1];
            } else
            {
                ans[i]-=query(root[L[i]-1],root[R[i]],1,M,K[i]);
                K[i]=0;
            }
        }

    }
    for (int i=0;i<m;++i)
        printf("%lld\n",ans[i]);
}

int main()
{
    init();
    solve();
    return 0;
}
