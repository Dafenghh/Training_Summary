#include<bits/stdc++.h>
#define cnt(k)  T[k].cnt
#define tag(k)  T[k].tag
#define sum(k)  T[k].sum
#define maxn 100050
#define modu 1000000007
using namespace std;
typedef long long LL;

struct node
{
    LL cnt,tag,sum;
}   T[maxn<<2];

int n;
int a[maxn],pos[maxn];

bool cmp(int i,int j)   {
    return a[i]>a[j]||(a[i]==a[j]&&i<j);
}

void build(int k,int l,int r)
{
    cnt(k)=r-l+1;
    if (l==r)   return ;
    int mid=(l+r)>>1;
    build(k<<1,l,mid);
    build(k<<1|1,mid+1,r);
}

void init()
{
    scanf("%d",&n);
    for (int i=1;i<=n;++i)
        scanf("%d",a+i),pos[i]=i;
    sort(pos+1,pos+n+1,cmp);
    build(1,1,n);
}

void renew(int k,LL d)  {
    tag(k)=(tag(k)+d)%modu;
    sum(k)=(sum(k)+cnt(k)*d)%modu;
}

void godown(int k)  {
    if (!tag(k))    return ;
    renew(k<<1,tag(k));
    renew(k<<1|1,tag(k));
    tag(k)=0;
}

void update(int k)  {
    sum(k)=sum(k<<1)+sum(k<<1|1);
    cnt(k)=cnt(k<<1)+cnt(k<<1|1);
}

LL query(int k,int l,int r,int p)
{
    if (r<=p)   return sum(k);
    godown(k);
    int mid=(l+r)>>1;
    if (p>mid)
        return (query(k<<1|1,mid+1,r,p)+sum(k<<1))%modu;
    else
        return query(k<<1,l,mid,p);
}

void change_sum(int k,int l,int r,int p,LL d)
{
    if (p>r)    return ;
    if (p<=l)
        renew(k,d);
    else
    {
        godown(k);
        int mid=(l+r)>>1;
        change_sum(k<<1,l,mid,p,d);
        change_sum(k<<1|1,mid+1,r,p,d);
        update(k);
    }
}

void change_cnt(int k,int l,int r,int p)
{
    if (l==r)
        sum(k)=tag(k)=cnt(k)=0;
    else
    {
        godown(k);
        int mid=(l+r)>>1;
        if (p<=mid)
            change_cnt(k<<1,l,mid,p);
        else
            change_cnt(k<<1|1,mid+1,r,p);
        update(k);
    }
}

LL dp[maxn];

void solve()
{
    LL ans=0;
    for (int k=1,j=1;k<=n;k=j)
    {
        while (j<=n&&a[pos[k]]==a[pos[j]])  ++j;
        for (int i=k;i<j;++i)
        {
            if (pos[i]>1)
                dp[pos[i]]=query(1,1,n,pos[i]-1);
            change_cnt(1,1,n,pos[i]);
            ans=(ans+dp[pos[i]])%modu;
        }
        for (int i=k;i<j;++i)
            change_sum(1,1,n,pos[i]+1,dp[pos[i]]+1);
    }
    printf("%lld\n",ans);
}

int main()
{
    init();
    solve();
    return 0;
}
