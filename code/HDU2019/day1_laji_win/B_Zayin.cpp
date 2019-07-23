#include<bits/stdc++.h>
#define maxn 1000050
#define maxb 30
#define bit(i)  B[i].bit
#define pos(i)  B[i].pos
using namespace std;

int n,m;
int a[maxn];

struct Base {
    int bit[maxb],pos[maxb];
    void copy(const Base& B)  {
        for (int i=0;i<maxb;++i)
            bit[i]=B.bit[i],pos[i]=B.pos[i];
    }
} B[maxn];

void add(int p,int x)   {
    B[p].copy(B[p-1]);
    int j=p;
    for (int i=maxb-1;~i;--i)   {
        if (~x>>i&1)    continue;
        if (bit(p)[i])  {
            if (pos(p)[i]<j)
                swap(bit(p)[i],x),swap(pos(p)[i],j);
            x^=bit(p)[i];
        }
        else    {
            bit(p)[i]=x,pos(p)[i]=j;
            break;
        }
    }
    // cout<<"base "<<p<<":"<<endl;
    // for (int i=maxb-1;~i;--i)
    //     cout<<i<<":"<<bit(p)[i]<<" "<<pos(p)[i]<<endl;
}

void init() {
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;++i)  
        scanf("%d",a+i),add(i,a[i]);
}

void solve()    {
    int ans=0;
    while (m--) {
        int op,l,r,x;
        scanf("%d",&op);
        if (!op)    {
            scanf("%d%d",&l,&r);
            l=(l^ans)%n+1,r=(r^ans)%n+1;
            if (l>r)    swap(l,r);
            ans=0;
            for (int i=maxb-1;~i;--i)   {
                if (pos(r)[i]<l)    continue;
                ans=max(ans,ans^bit(r)[i]);
            }
            printf("%d\n",ans);
        } else  {
            scanf("%d",&a[++n]);
            add(n,a[n]^=ans);
        }
    }
}

int main()  {
    int T;
    scanf("%d",&T);
    while (T--) {
        init();
        solve();
    }
    return 0;
}
