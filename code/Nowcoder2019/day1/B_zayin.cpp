#include<bits/stdc++.h>
#define maxn 1050
#define modu 1000000007
using namespace std;
typedef long long LL;
 
int n;
LL a[maxn];
 
LL inv(LL a)    {
    a=(a%modu+modu)%modu;
    LL ans=1;
    for (int k=modu-2;k;k>>=1) {
        if (k&1)
            ans=ans*a%modu;
        a=a*a%modu;
    }
    return ans;
}
 
int main()  {
    while (~scanf("%d",&n)) {
        for (int i=1;i<=n;++i)
            scanf("%lld",a+i);
        LL ans=0;
        for (int i=1;i<=n;++i)   {
            LL res=2*a[i]%modu;
            for (int j=1;j<=n;++j)
                if (i!=j)   {
                    LL t=(a[j]*a[j]-a[i]*a[i])%modu;
                    res=res*(t+modu)%modu;
                }
            ans=(ans+inv(res))%modu;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
