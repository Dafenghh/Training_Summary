#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N=61;
LL k,a[N],b[N],pw[N];

LL m,mn,mx;

void update(LL pre,LL sum,int len) {
    LL x=pre*pw[len]+pw[len]-1,s=sum+k*len-2;
    if (s<m)  return ;
    if (s>m)
        m=s,mn=1LL<<60,mx=0;
    mn=min(mn,x),mx=max(mx,x);
}

void get(LL *a)  {
    LL m;
    scanf("%lld",&m);
    for (int i=0;i<N;++i)
        a[i]=m%k,m/=k;
}


void solve()    {
    scanf("%lld",&k);
    pw[0]=1;
    for (int i=1;i<N;++i)
        pw[i]=pw[i-1]*k;
    get(a),get(b);

    LL pa=0,pb=0,sa=0,sb=0;
    bool flag=1,fa=0,fb=0;
    for (int i=N-1;~i;--i)   {
        pa=pa*k+a[i],pb=pb*k+b[i];
        if (sa||a[i]) sa+=a[i]+1,fa=1;
        if (sb||b[i]) sb+=b[i]+1,fb=1;

        if (flag)
        {
            if (b[i]-a[i]>1)    {
                update(pa-a[i]+b[i]-1,sa-a[i]+b[i]-1+!fa,i);
                update(pb-1,sb-1,i);
            }
            if (a[i]!=b[i])
                flag=0;
        } else
        {
            if (b[i])   update(pb-1,sb-1,i);
            if (a[i]!=k-1)  update(pa-a[i]+k-1,sa-a[i]+k-1+!fa,i);
        }
    }
    update(pa,sa,0);
    update(pb,sb,0);
    printf("%lld %lld %lld\n",m,mn,mx);
}

int main()  {
    int T,icase=0;
    scanf("%d",&T);
    while (T--) {
        m=0,mn=1LL<<60,mx=0;
        printf("Case #%d: ",++icase);
        solve();
    }
    return 0;
}
