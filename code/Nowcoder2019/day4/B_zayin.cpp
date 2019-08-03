#include<bits/stdc++.h>
#define maxn 50050
#define maxb 33
using namespace std;
typedef long long LL;
 
int n,m;
 
LL bit[maxb],st[maxb];
LL Bit[maxn<<2][maxb];
 
void insert(LL *bit,LL x)   {
    for (int i=maxb-1;~i;--i)   {
        if (~x>>i&1)    continue;
        if (bit[i])
            x^=bit[i];
        else    {
            bit[i]=x;
            break;
        }
    }
}
 
void merge(LL *b1,LL *b2,LL *B)   {
    memcpy(bit,b1,sizeof(bit));
    memcpy(st,b1,sizeof(st));
    for (int i=0;i<maxb;++i)   {
        LL x=b2[i],s=0;
        bool flag=1;
        for (int j=maxb-1;~j;--j)   {
            if (~x>>j&1)    continue;
            if (bit[j])
                x^=bit[j],s^=st[j];
            else    {
                bit[j]=x,st[j]=s,flag=0;
                break;
            }
        }
        if (flag)   insert(B,s);
    }
}
 
void build(int k,int l,int r)   {
    if (l==r)   {
        int sz;
        scanf("%d",&sz);
        while (sz--)    {
            LL x;
            scanf("%lld",&x);
            insert(Bit[k],x);
        }
    } else  {
        int mid=(l+r)>>1;
        build(k<<1,l,mid);
        build(k<<1|1,mid+1,r);
        merge(Bit[k<<1],Bit[k<<1|1],Bit[k]);
    }
}
 
void init() {
    scanf("%d%d",&n,&m);
    build(1,1,n);
}
 
bool exist(LL *bit,LL x)    {
    for (int i=maxb-1;~i;--i)   {
        if (~x>>i&1)    continue;
        if (bit[i])
            x^=bit[i];
        else
            return 0;
    }
    return 1;
}
 
bool query(int k,int l,int r,int a,int b,LL x)  {
    if (l>b||a>r)   return 1;
    if (a<=l&&r<=b) return exist(Bit[k],x);
    int mid=(l+r)>>1;
    return query(k<<1,l,mid,a,b,x)&&query(k<<1|1,mid+1,r,a,b,x);
}
 
void solve()    {
    while (m--) {
        int l,r;
        LL x;
        scanf("%d%d%lld",&l,&r,&x);
        puts(query(1,1,n,l,r,x)?"YES":"NO");
    }
}
 
int main()  {
    init();
    solve();
    return 0;
}
