#include<bits/stdc++.h>
#define maxb 61
#define maxn 100050
#define modu 1000000007
using namespace std;
typedef long long LL;
 
int n;
LL a[maxn];
 
LL bit[maxb];
LL cs[maxb];
bool uni[maxb];
 
LL pw[maxn]={1};
 
int main()  {
    for (int i=1;i<maxn;++i)    pw[i]=pw[i-1]*2%modu;
    while (~scanf("%d",&n)) {
        for (int i=0;i<maxb;++i)    bit[i]=cs[i]=uni[i]=0;
        int free=0;
        for (int i=1;i<=n;++i)  {
            scanf("%lld",a+i);
            bool flag=1;
            LL s=0;
            for (int b=maxb-1;flag&&~b;--b)   {
                if (~a[i]>>b&1) continue;
                s^=cs[b];
                if (bit[b])
                    a[i]^=bit[b];
                else {
                    bit[b]=a[i],cs[b]=s^1LL<<b;
                    flag=0;
                }
            }
            if (flag)   {
                // cout<<"free:"<<i<<endl;
                ++free;
                for (int i=0;i<maxb;++i)
                    if (s>>i&1)
                        // cout<<"f:"<<i<<endl,
                        uni[i]=1;
            }
        }
        int cnt=free;
        for (int i=0;i<maxb;++i)
            if (uni[i])
                ++cnt;
        printf("%lld\n",pw[free-1]*cnt%modu);
    }
    return 0;
}
