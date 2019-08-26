#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

LL m,p,a,b;

LL multi(LL a,LL b,LL p)    {
    LL ans=0;
    for (a%=p;b;b>>=1)  {
        if (b&1)
            ans=(ans+a)%p;
        a=(a+a)%p;
    }
    return ans;
}
LL pw(LL a,LL k,LL p)   {
    LL ans=1;
    for (a%=p;k;k>>=1)  {
        if (k&1)
            ans=multi(ans,a,p);
        a=multi(a,a,p);
    }
    return ans;
}

int main()  {
    int T;
    scanf("%d",&T);
    while (T--) {
        scanf("%lld%lld%lld",&p,&a,&b),m=p-1;
        for (int c=2;c<=3;++c)
            for (;m%c==0;m/=c)
                if (pw(a,m/c,p)!=1)
                    break;
        auto calc=[&]() {
            LL Ia=pw(a,p-2,p);
            LL ans=0,base=1;
            for (int c=2;c<=3;++c)  {
                int cnt=0;
                for (;m%c==0;m/=c,base*=c)  {
                    LL t1=pw(a,m*base/c,p),t2=pw(multi(b,pw(Ia,ans,p),p),m/c,p);
                    bool flag=0;
                    for (int i=0;i<c;++i)
                        if (pw(t1,i,p)==t2) {
                            ans+=base*i;
                            flag=1;
                            break;
                        }
                    if (!flag)  return -1LL;
                }
            }
            return ans;
        };
        printf("%lld\n",calc());
    }
    return 0;
}
