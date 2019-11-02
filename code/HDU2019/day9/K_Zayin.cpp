#include<bits/stdc++.h>
#define modu 998244353
using namespace std;
typedef long long LL;

map<LL,LL> D,F,G;

const LL inv2=(modu+1)/2;
const LL inv3=(modu+1)/3;
LL S1(LL n) {
    n%=modu;
    return n*(n+1)/2%modu;
}
LL S2(LL n) {
    n%=modu;
    return S1(n)*(2*n+1)%modu*inv3%modu;
}
LL S1_1(LL n)   {
    return (S1(n)-1+modu)%modu;
}
LL S2_1(LL n)   {
    return (S2(n)-1+modu)%modu;
}

LL calc_D(LL n)  {
    if (n<=1)   return n;
    if (D.count(n)) return D[n];
    LL m=n/2;
    if (n&1)
        return D[n]=(calc_D(m)*3+calc_D(m+1)+S1_1(n))%modu;
    else
        return D[n]=(calc_D(m)*3+calc_D(m-1)+S1_1(n))%modu;
}
LL calc_F(LL n)  {
    if (n<=1)   return n;
    if (F.count(n)) return F[n];
    LL m=n/2;
    if (n&1)
        return F[n]=(calc_F(m)*6+calc_F(m+1)*2+calc_D(m)-calc_D(m+1)+modu+S2_1(n))%modu;
    else
        return F[n]=(calc_F(m)*6+calc_F(m-1)*2+calc_D(m-1)-calc_D(m)+modu+S2_1(n))%modu;
}
LL calc_G(LL n)  {
    if (n<=1)   return n;
    if (G.count(n)) return G[n];
    LL m=n/2;
    if (n&1)
        return G[n]=(calc_G(m)*3+calc_G(m+1)+calc_F(m)+calc_F(m)+calc_D(m)+(S1_1(n)+S2_1(n))*inv2)%modu;
    else
        return G[n]=(calc_G(m)*3+calc_G(m-1)+calc_F(m)+calc_F(m-1)+calc_D(m-1)+(S1_1(n)+S2_1(n))*inv2)%modu;
}

int main()  {
    int T;
    scanf("%d",&T);
    while (T--) {
        LL L,R;
        scanf("%lld%lld",&L,&R);
        printf("%lld\n",(calc_G(R)-calc_G(L-1)+modu)%modu);
    }
    return 0;
}
