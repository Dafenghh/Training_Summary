#include<bits/stdc++.h>
#define ls(k)   T[k].ls
#define rs(k)   T[k].rs
#define cnt(k)  T[k].cnt
#define sum(k)  T[k].sum
#define maxh 40
#define maxn 100050
#define inf 1000000000
using namespace std;
typedef long long LL;

int rt,sz;
struct node
{
    int ls,rs;
    LL cnt,sum;
}   T[maxn*maxh];

int n,m;
vector<int> jewel[maxn],row[maxn];

LL ans=1LL<<60;
LL cnt,sum;

bool cmp(int i,int j)   {
    return i>j;
}

void init()
{
    scanf("%d%d",&n,&m);
    cnt=m;
    for (int k=0;k<m;++k)
    {
        int a,c;
        scanf("%d%d",&c,&a);
        jewel[a].push_back(c);
        sum+=c;
    }
    for (int i=1;i<=n;++i)
    {
        sort(jewel[i].begin(),jewel[i].end(),cmp);
        for (int j=0;j<jewel[i].size();++j)
            row[j+1].push_back(jewel[i][j]);
    }
}

void insert(int &k,int l,int r,int w)
{
    if (!k) k=++sz;
    ++cnt(k),sum(k)+=w;
    if (l==r)   return ;
    int mid=(l+r)>>1;
    if (w<=mid)
        insert(ls(k),l,mid,w);
    else
        insert(rs(k),mid+1,r,w);
}

LL query(int k,int l,int r,int c)
{
    if (c<=0)   return 0;
    if (l==r)   return 1LL*l*c;
    int mid=(l+r)>>1;
    if (cnt(ls(k))>=c)
        return query(ls(k),l,mid,c);
    else    
        return query(rs(k),mid+1,r,c-cnt(ls(k)))+sum(ls(k));
}

void solve()
{
    for (int i=1;i<=m;++i)
    {
        for (auto w:row[i])
        {
            sum-=w,--cnt;
            insert(rt,1,inf,w);
        }
        ans=min(ans,sum+query(rt,1,inf,i-cnt+1));
        // cout<<i<<" "<<sum+query(rt,1,inf,i-cnt+1)<<endl;
    }
    printf("%lld\n",ans);
}

int main()
{
    init();
    solve();
    return 0;
}