#include<bits/stdc++.h>
#define maxn 500050
using namespace std;

int n,N;
int a[maxn];

int pos[maxn],*p;
int nxt[maxn];// same element
int R[maxn];// postion

void init() {
    scanf("%d",&n),N=n*2-1;
    for (int i=1;i<=n;++i)  pos[i]=0;   p=pos+1;
    for (int i=1;i<=N;++i)
        scanf("%d",a+i);
    
    a[1]=a[N]=1;
    for (int i=1;i<=N;++i)
        R[i]=i+1,nxt[i]=N+1;
    for (int i=1;i<=N;++i)  {
        if (!~a[i]) continue;
        if (pos[a[i]])
            nxt[pos[a[i]]]=i;
        pos[a[i]]=i;
    }
}

int no()    {
    while (*p)  ++p;
    return (p++)-pos;
}

int stk[maxn],tp;

void del(int l,int r)   {
    nxt[l]=nxt[r];
    R[l]=R[r];
}

void calc(int l,int r)  {
    for (int i=l;i<=r;i=R[i])
        while (nxt[i]<r)    
            calc(i,nxt[i]);

    int sum=0,cnt=0;
    for (int i=l;i<r;i=R[i]) ++sum,cnt+=-1!=a[i];
    cnt=(sum>>1)+1-cnt;
    for (int i=l;i<r;i=R[i])
        if (!~a[i]&&cnt)
            a[i]=no(),--cnt;
    tp=0;
    for (int i=l;i<r;i=R[i])   {
        while (tp>=2&&(~a[stk[tp]]&&((a[stk[tp-1]]!=-1)^(a[i]!=-1))))
            a[stk[tp-1]]=a[i]=a[stk[tp-1]]&a[i],tp-=2;
        stk[++tp]=i;
    }
    del(l,r);
}

void solve()    {
    calc(1,N);
    for (int i=1;i<=N;++i)
        printf("%d%c",a[i]," \n"[i==N]);
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
