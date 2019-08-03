#include <bits/stdc++.h>
#define maxn 105
using namespace std;
typedef long long LL;
 
int n,m;
LL w[maxn],val[maxn];
int a[maxn][maxn];
 
struct Bitset   {
    static const int len=50;
    static const LL all=(1LL<<50)-1;
    LL s1,s2;
    Bitset(LL _s1=0,LL _s2=0)   {
        s1=_s1,s2=_s2;
    }
    void set(int i) {
        if (i<len)
            s1|=1LL<<i;
        else
            s2|=1LL<<(i-50);
    }
    void reset(int i)   {
        if (i<len)
            s1&=all^(1LL<<i);
        else
            s2&=all^(1LL<<(i-50));
    }
    LL at(int i) const  {
        if (i<len)
            return s1>>i&1;
        else
            return s2>>(i-50)&1;
    }
    Bitset operator & (const Bitset& B) const   {
        return Bitset(s1&B.s1,s2&B.s2);
    }
    bool operator < (const Bitset& B)    const   {
        return s1<B.s1||(s1==B.s1&&s2<B.s2);
    }
} nei[maxn];
 
struct node {
    int j;
    Bitset s;
    LL val;
    node(int u=0)   {
        s.set(j=u),val=w[u];
    }
    void set(int j) {
        s.set(j),val+=w[j];
    }
    void reset(int j)   {
        s.reset(j),val-=w[j];
    }
    bool operator < (const node& N)  const   {
        return val>N.val||(val==N.val&&j<N.j)||(val==N.val&&j==N.j&&s<N.s);       
    }
};
 
 
priority_queue<node> q;
 
bool ok(const node& N)  {
//  cout<<"ok:"<<N.s.s1<<" "<<N.s.s2<<endl;
    for (int i=0;i<N.j;++i)
        if (N.s.at(i)&&!a[i][N.j])  {
//          cout<<i<<" "<<N.j<<endl;
            return 0;
        }
    return 1;
}
 
void getnxt(node N) {
//  cout<<"get:"<<N.s.s1<<" "<<N.s.s2<<endl;
    Bitset all(Bitset::all,Bitset::all);
    for (int i=0;i<n;++i)
        if (N.s.at(i))
            all=all&nei[i];
    for (int i=N.j+1;i<n;++i)
        if (all.at(i))  {
            N.j=i;
            N.set(i);
            q.push(N);
            break;
        }
}
 
int pos[maxn],rk[maxn];
 
int main()  {
    scanf("%d%d",&n,&m);
    if (m==1)   return puts("0"),0;
    for (int i=0;i<n;++i)
        scanf("%lld",val+i);
    for (int i=0;i<n;++i)    pos[i]=i;
    sort(pos,pos+n,[&](const int& i,const int& j)   {
        return val[i]<val[j];
    });
    for (int i=0;i<n;++i)    w[i]=val[pos[i]];
    for (int i=0;i<n;++i)    rk[pos[i]]=i;
    for (int i=0;i<n;++i)
        for (int j=0;j<n;++j)    {
            int u=rk[i],v=rk[j];
            scanf("%1d",a[u]+v);
            if (a[u][v])
                nei[u].set(v);
        }
    q.push(node(0));
    while (!q.empty()&&--m) {
        node now=q.top();   q.pop();
//      printf("%d:%lld+%lld %lld\n",m,now.s.s1,now.s.s2,now.j,now.val);
        if (m==1)   return printf("%lld\n",now.val),0;
        if (now.j==n-1) continue;
        getnxt(now);
        now.reset(now.j);
        getnxt(now);
    }
    puts("-1");
    return 0;
}
