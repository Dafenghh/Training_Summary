#include<bits/stdc++.h>
#define maxn 300050
using namespace std;

int n,m;
int c[maxn];
int N,L[maxn],R[maxn];
vector<int> G[maxn];

int C;
map<int,int> col;
struct cmp  {
    bool operator () (const int& i,const int& j) const   {
        return L[i]<L[j];
    }
};
set<int,cmp> seq[maxn];

int Col(int c)  {
    if (!col.count(c))  
        ++C,seq[C].clear(),col[c]=C;
    return col[c];
}

int fa[maxn];
int len[maxn];
int dep[maxn],sz[maxn];
int son[maxn],tp[maxn];

int dfs1(int i)   {
    len[i]=son[i]=sz[i]=0;
    for (int j:G[i])    {
        if (fa[i]==j)   continue;
        fa[j]=i;
        dep[j]=dep[i]+1;
        sz[i]+=dfs1(j);
        if (sz[son[i]]<sz[j])
            son[i]=j;
    }
    len[i]=len[son[i]]+1;
    return ++sz[i];
}

void dfs2(int i,int top) {
    L[i]=++N,seq[0].insert(i);
    tp[i]=top;
    if (son[i])
        dfs2(son[i],top);
    for (int j:G[i])    {
        if (son[i]==j|fa[i]==j) continue;
        dfs2(j,j);
    }
    R[i]=N;
}

struct node {
    int val,tag;
} T[maxn<<2];
#define val(k)  T[k].val
#define tag(k)  T[k].tag

int LCA(int i,int j)    {
    while (tp[i]!=tp[j])    {
        if (dep[tp[i]]<dep[tp[j]])  swap(i,j);
        i=fa[tp[i]];
    }
    return dep[i]<dep[j]?i:j;
}

void build(int k,int l,int r)   {
    val(k)=1,tag(k)=0;
    if (l==r)   return;
    int mid=(l+r)>>1;
    build(k<<1,l,mid);
    build(k<<1|1,mid+1,r);
}

int renew(int k,int d)  {
    val(k)+=d,tag(k)+=d;
}

void godown(int k)  {
    renew(k<<1,tag(k));
    renew(k<<1|1,tag(k));
    tag(k)=0;
}

void update(int k)  {
    val(k)=min(val(k<<1),val(k<<1|1));
}

void change(int k,int l,int r,int a,int b,int d)    {
    if (a<=l&&b<=r)
        renew(k,d);
    else    {
        godown(k);
        int mid=(l+r)>>1;
        if (a<=mid) change(k<<1,l,mid,a,b,d);
        if (b>mid)  change(k<<1|1,mid+1,r,a,b,d);
        update(k);
    }
}

int query(int k,int l,int r,int a,int b,int d)  {//[a,b] <= d first position
    if (b<l)    return l;
    if (val(d)>d||r<a)   return r+1;
    int mid=(l+r)>>1;
    int t=query(k<<1,l,mid,a,b,d);
    return t>mid?query(k<<1|1,mid+1,r,a,b,d):t;
}

const int B=300;
int cnt[maxn],sum[maxn];

void change_link(int i,int d)    {
    if (!i) return ;
    while (i)   {
        if (len[tp[i]]<B)   {
            for (int t=tp[i];tp[i]==t;i=fa[i])  {
                --sum[cnt[i]];
                ++sum[cnt[i]+=d];
            }
        } else  {
            change(1,1,n,L[tp[i]],L[i],d);
            i=fa[tp[i]];
        }
    }
}

void change_col(int i)    {
    auto ass=[&](int d){
        int c=::c[i];
        auto it=seq[c].find(i);
        assert(it!=seq[c].end());
        auto Max=[&](const int& i,const int& j) {
            return dep[i]>dep[j]?i:j;
        };
        int j=0;
        if (it!=seq[c].begin()) j=Max(j,LCA(i,*--it)),++it;
        if (++it!=seq[c].end()) j=Max(j,LCA(i,*it));
        change_link(i,d);
        change_link(j,-d);
    };
    ass(-1),seq[c[i]].erase(i);
    scanf("%d",c+i),c[i]=Col(c[i]);
    seq[c[i]].insert(i),ass(1);
}

vector<int> sp;
int Query(int k)    {
    if (k>n)    return 0;
    int ans=sum[k];
    for (int i:sp)  {
        ans+=query(1,1,n,L[i],R[i],k-1)-query(1,1,n,L[i],R[i],k);
    }
    return ans;
}

int main()  {
    int T;
    scanf("%d",&T);
    while (T--) {
        scanf("%d%d",&n,&m);
        for (int i=1;i<=n;++i)  G[i].clear();
        for (int k=1;k<n;++k)   {
            int u,v;
            scanf("%d%d",&u,&v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        N=C=0;col.clear();col[0]=0;
        dfs1(1);
        dfs2(1,1);
        build(1,1,n);

        sp.clear();
        for (int i=1;i<=n;++i)
            if (tp[i]==i&&len[i]>=B)
                sp.push_back(i);

        for (int i=1;i<=n;++i)  c[i]=sum[i]=0;
        for (int i=1;i<=n;++i)  cnt[i]=1; sum[1]=n;
        for (int i=1;i<=n;++i)  change_col(i);
        while (m--) {
            int op,i;
            scanf("%d%d",&op,&i);
            if (op==1)  {
                change_col(i);
            } else  {
                printf("%d\n",Query(i));
            }
        }
    }
    return 0;
}
