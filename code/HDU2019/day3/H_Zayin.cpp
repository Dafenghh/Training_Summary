#include<bits/stdc++.h>
#define maxn 100050
#define maxm 2000050
using namespace std;
typedef long long LL;


int n,m,B;
int a[maxn],s[maxn];

LL ans[maxn];
LL sum[maxm],cnt;

int np;
struct OP    {
    int pos,t;
} P[maxn];

int nq;
struct Qry    {
    int l,r,t;
} Q[maxn];

int pos[maxn];

void ins(int x)    {
    cnt+=sum[x]++;
//    cout<<"ins:"<<x<<" "<<cnt<<endl;
}
void del(int x)    {
    cnt-=--sum[x];
//    cout<<"del:"<<x<<" "<<cnt<<endl;
}

int l,r,t;

void change(int i)    {
//    cout<<"change:"<<i<<endl;
    if (l<=i&&i<=r)
        del(s[i]);
    swap(a[i],a[i+1]);
    s[i]=s[i-1]^a[i];
    if (l<=i&&i<=r)
        ins(s[i]);
}

LL C2(LL len)    {
    return len*(len-1)/2;
}

int bl[maxn];

int main()    {
    while (~scanf("%d%d",&n,&m))    {
        for (int i=1;i<=n;++i)    
            scanf("%d",a+i),s[i]=s[i-1]^a[i];
//        for (int i=1;i<=n;++i)
//            cout<<s[i]<<" "; cout<<endl;
        B=max(100,(int)pow(n,2.0/3));
        np=nq=0;
        for (int i=1;i<=m;++i)    {
            int opt;
            scanf("%d",&opt); 
            if (opt==1)
                ++nq,scanf("%d%d",&Q[nq].l,&Q[nq].r),Q[nq].t=np,--Q[nq].l;
            else
                ++np,scanf("%d",&P[np].pos),P[np].t=i;
        }
        for (int i=1;i<=n;++i)    bl[i]=i/B;
        P[++np].t=m+1;
        for (int i=1;i<=nq;++i)
            pos[i]=i;
        sort(pos+1,pos+nq+1,[&](const int& i,const int& j)    {
            return bl[Q[i].l]<bl[Q[j].l]||(bl[Q[i].l]==bl[Q[j].l]&&bl[Q[i].r]<bl[Q[j].r])||(bl[Q[i].l]==bl[Q[j].l]&&bl[Q[i].r]==bl[Q[j].r]&&Q[i].t<Q[j].t);
        });
//        cout<<np<<" "<<nq<<endl;
        l=1,r=0,t=0;    
        for (int k=1;k<=nq;++k)    {
            int L=Q[pos[k]].l,R=Q[pos[k]].r,T=Q[pos[k]].t;
//            cout<<pos[k]<<":"<<L<<" "<<R<<" "<<T<<endl;
            while (r<R)    ins(s[++r]);
            while (r>R)    del(s[r--]);
            while (l<L)    del(s[l++]);
            while (l>L)    ins(s[--l]);
            while (t<T) change(P[++t].pos);
            while (t>T) change(P[t--].pos);
//            cout<<l<<" "<<r<<" "<<P[t].t<<endl;
            ans[pos[k]]=C2(r-l+1)-cnt;
        }
        cnt=0;
        for (int i=1;i<=n;++i)    sum[s[i]]=0;
        for (int i=1;i<=nq;++i)
            printf("%lld\n",ans[i]);
    }
//    cerr<<clock()<<endl;
    return 0;
}
