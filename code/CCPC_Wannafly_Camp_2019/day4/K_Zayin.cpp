#include<bits/stdc++.h>
#define val(k) T[k].val
#define ls(k)   T[k].ls
#define rs(k)   T[k].rs
#define maxn 150050
#define modu 998244353
using namespace std;
typedef long long LL;
const int N=131072,C=2,K=18,P=4;

int sz;
struct node {
    int ls,rs,val;
    node(int _val=0,int _ls=0,int _rs=0) {
        val=_val,ls=_ls,rs=_rs;
    }
}   T[N*K*K];

int subs[C][K];
int Log2[maxn];
int pw[maxn],ALL[C][maxn];

int sgn(int x)  {   return x>0?0:1; }
struct HP   {
    int rt,sgn;
    #define mid ((l+r)>>1)
    HP(int _rt=0,int _sgn=0)    {   rt=_rt,sgn=_sgn;    }
    bool comp(int k1,int k2,int l,int r) const {
        if (l==r)   return val(k1)<val(k2);
        return val(rs(k1))==val(rs(k2))?comp(ls(k1),ls(k2),l,mid):comp(rs(k1),rs(k2),mid+1,r);
    }
    bool operator < (const HP& x)  const {   return (sgn||x.sgn)^comp(rt,x.rt,1,N);  }
    int change(int &k,int l,int r,int p,int c)    {
        if (l>=p)
            if (val(k)==ALL[c^1][r-l+1])
                return k=subs[c][Log2[r-l+1]],1;
        if (l==r)   return k=subs[c^1][0],0;
        T[++sz]=T[k],k=sz;
        int w=0;
        if (p>mid||change(ls(k),l,mid,p,c))
            w=change(rs(k),mid+1,r,p,c);
        val(k)=(val(ls(k))+(LL)pw[mid-l+1]*val(rs(k)))%modu;
        return w;
    }
    inline void plus(int x) {  if (x) sgn^=change(rt,1,N,abs(x),::sgn(x)); }
    void add(int k,int l=1,int r=N) {
        if (!val(k))    return;
        if (l==r)   plus(l);
        else    add(ls(k),l,mid),add(rs(k),mid+1,r);
    }
    int travel(int k,int l,int r,int f,int pres) const {
        if (l==r)
            return (f||pres!=val(k))?putchar((val(k)^pres)+'0'),1:0;
        return travel(ls(k),l,mid,travel(rs(k),mid+1,r,f,pres),pres);
    }
}   U[maxn],D[maxn],mx[P],tmp[maxn];

ostream& operator << (ostream& os,HP x)  {
    int pres=x.sgn;
    if (x.sgn)    x.plus(-1),os<<"-";
    if (!x.travel(x.rt,1,N,0,pres)) os<<'0';
    return os;
}

int n,m;
int val[maxn];

int fa[maxn];
vector<int> G[maxn];
int l,r,Q[maxn];

void predo()    {
    Log2[0]=-1,pw[0]=1;
    for (int i=1;i<maxn;++i)    Log2[i]=Log2[i>>1]+1;
    for (int i=1;i<maxn;++i)    pw[i]=pw[i-1]*2%modu,ALL[1][i]=(ALL[1][i-1]+pw[i-1])%modu;
    for (int i=0;i<K;++i)
        T[sz+1]=node(ALL[1][1<<i],sz,sz),subs[1][i]=++sz;
    
    for (int i=Q[l=r=1]=1;l<=r;++l)
        for (int j:G[i=Q[l]])
            if (fa[i]!=j)
                fa[Q[++r]=j]=i;
    for (int k=n;k;--k)    {
        int i=Q[k];
        D[i]=U[fa[i]],U[i].plus(val[i]);
        if (U[fa[i]]<U[i])  U[fa[i]]=U[i];
    }
    for (int k=1;k<=n;++k)  {
        int i=Q[k];
        if (D[i]<tmp[fa[i]])    D[i]=tmp[fa[i]];
        D[i].plus(val[fa[i]]),tmp[i]=D[i];
        if (tmp[fa[i]]<U[i]) tmp[fa[i]]=U[i];
    }
}
void init() {
    scanf("%d",&n);
    for (int i=1;i<=n;++i)  scanf("%d",&val[i]);
    for (int k=1;k<n;++k)   {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v),G[v].push_back(u);
    }
}

void solve()    {
    scanf("%d",&m);
    while (m--) {
        int rt;
        scanf("%d",&rt);
        for (int i=0;i<P;++i)   mx[i]=0;
        for (int j:G[rt])   {
            HP t=(j==fa[rt]?D[rt]:U[j]);
            for (int i=0;i<P;++i)
                if (mx[i]<t)
                    swap(mx[i],t);
        }
        HP ans;
        ans.plus(val[rt]);
        for (int i=0;i<P;++i) ans.add(mx[i].rt);
        cout<<ans<<endl;
    }
}

int main()  {
    init();
    predo();
    solve();
    return 0;
}
