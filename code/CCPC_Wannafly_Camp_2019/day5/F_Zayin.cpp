#include<bits/stdc++.h>
#define maxl 50
#define maxn 300050
#define modu 1000000007
using namespace std;
typedef long long LL;

int n;
char s[maxl];

int sz;
int val[maxn],last[maxn],cnt[maxn];
map<int,int> G[maxn];

vector<int> nxt[maxn];

vector<int> A;

LL f[maxn],g[maxn],h[maxn];

int split(int s,int x,int c)
{
    int rt=sz++;
    last[rt]=x,val[rt]=s,cnt[rt]=c;
    for (int i=n-s;i&&i>=x;--i)
        G[rt][i]=split(s+i,i,c+1);
    return rt;
}

int build(int rt,int f,int k)
{
    if (f)
        nxt[k].push_back(rt);
    for (auto p:G[rt])
    {
        int w=p.first;
        if (G[k].count(w))
            build(G[rt][w],f,G[k][w]);
        if (!f&&last[rt]!=w)
            build(G[rt][w],1,rt);
    }
}

void init()
{
    scanf("%d%s",&n,s+1);
    s[n]='0';

    split(0,0,0);
    build(0,0,0);
}

void calc(const char* s,LL *dp)
{
    dp[0]=1;
    for (int i=0;i<sz;++i)
    {
        dp[i]%=modu;
        if (val[i]&&s[val[i]]=='1') continue;
        int last=val[i]+1;
        while (last<n&&s[last]!='2')    ++last;
        for (auto j:nxt[i])
            if (val[j]<=last&&s[val[j]]!='1')
                dp[j]+=dp[i];
    }
    // cout<<endl;
}

bool vis[maxn];

int sgn(int x)  {
    return x&1?modu-1:1;
}

void solve()
{
    int C=1;
    for (int i=1;i<n;++i)   C+=s[i]=='0';
    calc(s,f);

    for (int i=1,last=0,len=0;i<=n;++i)
        if (i&1)
            for (int j=(s[len++]='2',i<<1);j<=n;j<<=1)
                s[len++]='0';
    calc(s,g);

    LL ans=0;
    h[0]=1;
    for (int i=0;i<sz;++i)
    {
        for (auto j:nxt[i])
        {
            if (last[j]==last[i]) continue;
            LL s=h[i],c=1,w=(last[j]==1?1:2);
            for (int k=j;;k=G[k][last[j]])
            {
                h[k]=((s*=w*c++)%=modu);
                if (!G[k].count(last[j])) break;
            }
        }
        if (val[i]<n)   continue;
        ans+=sgn(C-cnt[i])*f[i]%modu*g[i]%modu*h[i],ans%=modu;
        // cout<<i<<" "<<C-cnt[i]<<" "<<sgn(C-cnt[i])<<" "<<f[i]<<" "<<g[i]<<" "<<h[i]<<endl;
    }
    printf("%lld\n",ans);
}

int main()
{
    init();
    solve();
    return 0;
}
