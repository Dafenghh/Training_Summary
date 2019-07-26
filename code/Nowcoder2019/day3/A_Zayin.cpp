#include<bits/stdc++.h>
#define maxn 100050
#define maxm 200050
#define maxb 550
using namespace std;
typedef unsigned long long ULL;

ULL val[maxn];

ULL R()    {
    static uniform_int_distribution<ULL> u(0,~0);
    static default_random_engine e(rand());
    return u(e);
}

int n,m,q,B,sz;

struct Edge {
    int u,v;
} E[maxm];

int bel[maxm];

int cnt[maxb];
int pos[maxn][maxb];
ULL con[maxb<<1][maxb];

ULL st[maxn];

int Time=0;

char pool[maxn],*head=pool,*tail=pool;
#define getc() (head==tail&&(tail=(head=pool)+fread(pool,1,maxn,stdin),head==tail)?0:*head++)
#define isd(c) (c>='0'&&c<='9')
int read(){
    int x=0; char ch=getc();
    while (!isd(ch)) ch=getc();
    while (isd(ch)) {x=x*10+ch-'0'; ch=getc();}
    return x;
}
// int read()  {
//     int x=0;
//     char c=getchar();
//     while (c<'0'||c>'9')    c=getchar();
//     while ('0'<=c&&c<='9')  x=(x<<3)+(x<<1)+c-'0',c=getchar();
//     return x;
// }

void init() {
    n=read(),m=read(),B=sqrt(m)+3,sz=(m-1)/B+1;
    for (int i=1;i<=n;++i)
        st[i]=0,val[i]=R();
    for (int i=0;i<m;++i)  {
        E[i].u=read(),E[i].v=read();
        st[E[i].u]^=val[E[i].v];
        st[E[i].v]^=val[E[i].u];
    }

    for (int i=0;i<m;++i)  bel[i]=i/B;
    for (int k=0;k<sz;++k) {
        cnt[k]=0;
        int tot=0;
        for (int i=1;i<=n;++i)  pos[i][k]=0;
        for (int j=k*B;j<(k+1)*B&&j<m;++j)  {
            int u=E[j].u,v=E[j].v;
            if (!pos[u][k]) pos[u][k]=++tot;
            if (!pos[v][k]) pos[v][k]=++tot;
        }
        for (int i=1;i<=tot;++i) con[i][k]=0;
        for (int j=k*B;j<(k+1)*B&&j<m;++j)    {
            int u=E[j].u,v=E[j].v;
            con[pos[u][k]][k]^=val[v];
            con[pos[v][k]][k]^=val[u];
        }
    }
}

inline void rev(int i) {
    st[E[i].u]^=val[E[i].v];
    st[E[i].v]^=val[E[i].u];
}

inline ULL S(int u)    {
    ULL s=st[u];
    for (int i=0;i<sz;++i)
        if (pos[u][i])
            if (cnt[i])
                s^=con[pos[u][i]][i];
    return s;
}

void solve()    {
    // cout<<"B:"<<B<<endl;
    // for (int i=0;i<m;++i)
    //     cout<<"bel:"<<i<<" "<<bel[i]<<endl;
    // for (int i=1;i<=n;++i)
    //     cout<<i<<":"<<val[i]<<" "<<st[i]<<endl;
    q=read();
    while (q--) {
        int op=read();
        if (op==1)  {
            int l=read()-1,r=read()-1;
            if (bel[l]==bel[r]) {
                for (int i=l;i<=r;++i) {
                    // cout<<"rev:"<<i<<endl;
                    st[E[i].u]^=val[E[i].v];
                    st[E[i].v]^=val[E[i].u];
                }
            } else  {
                // cout<<l<<" "<<r<<" "<<bel[l]<<" "<<bel[r]<<endl;
                for (int i=bel[l]+1;i<bel[r];++i)   cnt[i]^=1;
                for (int i=(bel[l]+1)*B-1;i>=l;--i) {
                    // cout<<"rev:"<<i<<endl;
                    st[E[i].u]^=val[E[i].v];
                    st[E[i].v]^=val[E[i].u];
                }
                for (int i=bel[r]*B;i<=r;++i) {
                    // cout<<"rev:"<<i<<endl;
                    st[E[i].u]^=val[E[i].v];
                    st[E[i].v]^=val[E[i].u];
                }
            }
        } else  {
            int u=read(),v=read();
            // cout<<S(u)<<"("<<st[u]<<") "<<S(v)<<"("<<st[v]<<")"<<endl;
            putchar((S(u)==S(v))+'0');
        }
        // for (int i=1;i<=n;++i)
        //     cout<<i<<":"<<val[i]<<" "<<st[i]<<endl;
    }
    puts("");
}

int main()  {
    srand(time(0));
    int T;
    scanf("%d",&T);
    while (T--) {
        init();
        solve();
    }
    // cerr<<Time<<"/"<<clock()<<endl;
    return 0;
}
