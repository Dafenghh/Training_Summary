#include<bits/stdc++.h>
#define maxn 2050
#define maxm 8050
#define modu 1000000007
using namespace std;
typedef long long LL;

// const int P[]={2,3,5,7,9,11,13,17,19,23,29,31,37,41,43,47,53};
LL P[maxn],Q[maxn];
struct Tree {
    static const int N=12;
    int n,fa[N];
    LL hash;
    LL calc()   {
        vector<LL> val(n),sz(n);
        for (int i=n-1;i;--i)   {
            sz[fa[i]]+=++sz[i];
            val[fa[i]]+=P[sz[i]]^(val[i]+=Q[sz[i]]);
        } 
        return hash=val[0]+Q[++sz[0]];
    }
    Tree() :n(1) { calc(); }
    Tree add(int i) {
        Tree T=*this;
        T.fa[T.n++]=i;
        T.calc();
        return T;
    }
    void print()    {
        cout<<n<<":"<<hash<<endl;
        for (int i=1;i<n;++i)
            cout<<i<<" "<<fa[i]<<endl;
        cout<<"-----------"<<endl;
    }
};

int m;
map<LL,int> Ht;
vector<Tree> T;
vector<pair<int,int>> trans[maxm];

LL R()    {
    static uniform_int_distribution<LL> u(1e7,1e10);
    static default_random_engine e(rand());
    return u(e);
}

void predo()    {
    srand(time(0));
    for (int i=0;i<maxn;++i) P[i]=R(),Q[i]=R();

    T.push_back(Tree()),Ht[T.front().hash]=0;
    int last=0;
    for (int i=1;i<Tree::N;++i)    {
        int sz=T.size();
        for (;last<sz;++last)   {
            Tree now=T[last];
            for (int j=0;j<i;++j)   {
                Tree nxt=now.add(j);
                if (Ht.count(nxt.hash)) continue;
                Ht[nxt.hash]=T.size();
                T.push_back(nxt);
            }
        }
    }
    m=T.size();
    int cnt=0;
    for (int i=0;i<m;++i)   {
        for (int j=0;j<m;++j)   {
            if (T[i].n+T[j].n>Tree::N)  continue;
            ++cnt;
            LL hash=T[i].hash-Q[T[i].n]+(T[j].hash^P[T[j].n])+Q[T[i].n+T[j].n];
            assert(Ht.count(hash));
            trans[i].emplace_back(j,Ht[hash]);
        }
    }
    assert(m==7813&&cnt==13689);
}

int n;
vector<int> G[maxn];

LL dp[maxn][maxm];
LL con[maxm];

void add(LL &x,LL y)   {
    x=(x+y)%modu;
}

void dfs(int u,int fa=0)    {
    dp[u][0]=1;
    for (int v:G[u])    {
        if (fa==v)  continue;
        dfs(v,u);
        for (int i=m-1;~i;--i)
            if (dp[u][i])
                for (pair<int,int> p:trans[i])
                    if (dp[v][p.first]) 
                        add(dp[u][p.second],dp[u][i]*dp[v][p.first]);
    }
    for (int i=0;i<m;++i)
        add(con[i],dp[u][i]);
}

void init() {
    scanf("%d",&n);
    for (int k=1;k<n;++k)   {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1);
}

int sz[maxn];
LL calc(int i,int fa=0) {
    LL hash=0;sz[i]=1;
    for (int j:G[i])    {
        if (fa==j)  continue;
        LL hj=calc(j,i);
        hash+=P[sz[j]]^hj;
        sz[i]+=sz[j];
    }
    hash+=Q[sz[i]];
    assert(Ht.count(hash));
    return hash;
}

void solve()    {
    int q;
    scanf("%d",&q);
    for (int t=1;t<=q;++t)  {
        scanf("%d",&n);
        for (int i=1;i<=n;++i)  G[i].clear();
        for (int k=1;k<n;++k)   {
            int u,v;
            scanf("%d%d",&u,&v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        LL ans=0;
        set<LL> hash;
        for (int i=1;i<=n;++i)  {
            LL h=calc(i);
            if (hash.count(h))  continue;
            hash.insert(h);
            add(ans,con[Ht[h]]);
        }
        printf("%lld\n",ans);
    }
}

int main()  {
    predo();
    init();
    solve();
    return 0;
}
