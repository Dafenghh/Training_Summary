#include<bits/stdc++.h>
using namespace std;
typedef __int128 LL;


LL S0(LL x) {
    return x;
}

LL S1(LL x) {
    return x*(x+1)/2;
}

LL S2(LL x) {
    return x*(x+1)*(2*x+1)/6;
}

LL S3(LL x) {
    return S1(x)*S1(x);
}

int main()
{
    int T,icase=0;
    scanf("%d",&T);
    while (T--)
    {
        int l,r;
        LL ans=0;
        scanf("%d%d",&l,&r);
        // ans=C4(r+2)-C4(l+1);

        LL q=r-l+1,m=min((LL)l-1,q);

        ans+=(-S3(m)+S2(m)*(2*q+l+1)-S1(m)*(q*(q+1)+(2*q+1)*l)+S0(m)*q*(q+1)*l)/2;
        // for (LL a=1;a<l;++a)
        // {
        //     LL t=0;
        //     for (int b=a;b<=r-l+1;++b)
        //         t+=(b-a);
        //     ans+=t*(l-a);
        // }  

        ans+=(S3(r-l)-S2(r-l)*(2*r+1)+S1(r-l)*(l+r)*(r-l+1))/2;
        // for (LL a=1;a<=r-l;++a)
        //     ans+=a*(l+r-a)*(r-a-l+1)/2;
        printf("Case #%d: %lld\n",++icase,(long long)ans);
    }
    return 0;
}
