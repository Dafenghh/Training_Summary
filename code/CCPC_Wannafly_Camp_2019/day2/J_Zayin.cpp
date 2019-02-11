#include<bits/stdc++.h>
#define fi first
#define se second
#define len(i)  (Q[i].se-Q[i].fi)
#define maxh 20
#define maxn 1000500
#define _w(i)   (n-(i)+1)
#define mkp(x,y)    make_pair(x,y)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;

int n,m;
char s[maxn];

LL sum[maxn];
int ts[2][maxn];

int Log2[maxn];

LL ans[maxn];
struct Q {
    int i,f,id;
    Q(int _i=0,int _f=0,int _id=0)    {
        i=_i,f=_f,id=_id;
    }
} ;
vector<Q> QL[maxn],QR[maxn];

int read()  {
    int x=0;
    char c=getchar();
    while (c<'0'||c>'9')    c=getchar();
    while ('0'<=c&&c<='9')  x=(x<<3)+(x<<1)+c-'0',c=getchar();
    return x;
}

struct SA
{
    int sa[maxn],rk[maxn];
    int ST[maxh][maxn],* const h=ST[0];

    void build(const char* s) {
        int *x=ts[0],*y=ts[1],m=256;
        for (int i=1;i<=m;++i)  sum[i]=0;
        for (int i=1;i<=n;++i)  ++sum[x[i]=s[i]];
        for (int i=1;i<=m;++i)  sum[i]+=sum[i-1];
        for (int i=n;i;--i) sa[sum[x[i]]--]=i;
        for (int k=1;k<=n;k<<=1)    {
            int p=0;
            for (int i=n;i>n-k;--i) y[++p]=i;
            for (int i=1;i<=n;++i)
                if (sa[i]>k)
                    y[++p]=sa[i]-k;
            for (int i=1;i<=m;++i)  sum[i]=0;
            for (int i=1;i<=n;++i)  ++sum[x[y[i]]];
            for (int i=1;i<=m;++i)  sum[i]+=sum[i-1];
            for (int i=n;i;--i) sa[sum[x[y[i]]]--]=y[i];

            swap(x,y);
            x[sa[1]]=m=1;
            for (int i=2;i<=n;++i)
                x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k]?m:++m);
            if (m>=n)   break;
        }

        for (int i=1;i<=n;++i)  rk[sa[i]]=i;
        for (int i=1,k=0;i<=n;++i)    {
            if (k)  --k;
            int j=sa[rk[i]-1];
            while (s[i+k]==s[j+k])  ++k;
            h[rk[i]]=k;
        }

        for (int j=1;(1<<j)<=n;++j)
            for (int i=1;i+(1<<j)-1<=n;++i)
                ST[j][i]=min(ST[j-1][i],ST[j-1][i+(1<<(j-1))]);
    }

    int LCP(int i,int j)    {
        int l=rk[i],r=rk[j];
        if (l>r)    swap(l,r);
        int t=Log2[r-l++];
        return min(ST[t][l],ST[t][r-(1<<t)+1]);
    }
} W,_W;

struct BIT
{
    LL T[maxn],S,C[maxn];

    void clear()  {
        S=0;
        for (int i=1;i<=n;++i)
            T[i]=C[i]=0;
    }

    int lowbit(int i)   {
        return i&(-i);
    }

    void change(int x,int d)    {
        if (!x) return ;
        S+=d;
        for (int i=x;i<=n;i+=lowbit(i))
            T[i]+=x*d,C[i]+=d;
    }

    LL calc(int x)  {
        LL ans=0,cnt=0;
        for (int i=x;i;i-=lowbit(i))
            ans+=T[i],cnt+=C[i];
        return ans+(S-cnt)*x;
    }

}   L,R;

vector<pii> runs[maxn];

void init()
{
    scanf("%d%d%s",&n,&m,s+1);

    Log2[0]=-1;
    for (int i=1;i<=n;++i)
        Log2[i]=Log2[i>>1]+1;

    W.build(s);
    reverse(s+1,s+n+1);
    _W.build(s);

    L.clear(),R.clear();
    for (int i=1;i<=n;++i)  sum[i]=0;
    for (int D=1;D<=n;++D)
    {
        runs[D].clear();
        if (D&1)    continue;
        int d=D>>1,last_l=-1,last_r=-1;
        for (int i=1;i+d<=n;i+=d)
        {
            int l=i-_W.LCP(_w(i),_w(i+d)),r=i+d+W.LCP(i,i+d)-1;
            if (r-l<D||(last_l==l&&last_r==r)) continue;

            runs[D].push_back(mkp(l,r));
            ++sum[l+D],--sum[r+1];

            last_l=l,last_r=r;
        }
    }
    for (int i=1;i<=n;++i)  sum[i]+=sum[i-1];
    for (int i=1;i<=n;++i)  sum[i]+=sum[i-1];
}


void solve()
{
    for (int i=1;i<=n;++i)
        QL[i].clear(),QR[i].clear();
    for (int i=0;i<m;++i)
    {
        int l=read(),r=read(),d=r-(--l)+1;
        ans[i]=sum[r];

        if (!l) continue;
        QL[d].push_back(Q(l,-1,i));
        QR[r].push_back(Q(r,-1,i)),QR[d].push_back(Q(r,1,i));
    }

    for (int d=1;d<=n;++d)
    {
        for (auto s:runs[d])
        {
            int l=s.fi,r=s.se;
            L.change(l,-1),L.change(r-d+1,1);
            R.change(l+d-1,-1),R.change(r,1);
        }
        for (auto Q:QL[d]) ans[Q.id]+=Q.f*L.calc(Q.i);
        for (auto Q:QR[d]) ans[Q.id]+=Q.f*R.calc(Q.i);
    }

    for (int i=0;i<m;++i)
        printf("%lld\n",ans[i]);
}

int main()
{
    int T,icase=0;
    scanf("%d",&T);
    while (T--)
    {
        init();
        printf("Case #%d:\n",++icase);
        solve();
    }
    return 0;
}
