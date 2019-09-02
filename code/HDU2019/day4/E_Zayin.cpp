#include<bits/stdc++.h>
#define maxk 61
#define modu 1000000009
using namespace std;
typedef long long LL;


LL pw(LL a,LL k=modu-2) {
    LL ans=1;
    for (;k;k>>=1)  {
        if (k&1)
            ans=ans*a%modu;
        a=a*a%modu;
    }
    return ans;
}

LL add(LL &a,LL b)  {
    a=(a+b)%modu;
}

struct FWT  {
    const int N=6561,I=667885999;
    const LL w1=115381398LL,w2=884618610LL;

    void DFT(LL *A) {
        for (int len=3;len<=N;len*=3)   {
            int m=len/3;
            for (LL *p=A;p!=A+N;p+=len)
                for (int i=0;i<m;++i)   {
                    LL &x=p[i],&y=p[i+m],&z=p[i+m+m];
                    tie(x,y,z)=make_tuple(
                        (x+y+z)%modu,
                        (x+w1*y+w2*z)%modu,
                        (x+w2*y+w1*z)%modu
                    );
                }
        }
    }
    void IDFT(LL *A)    {
        for (int len=3;len<=N;len*=3)   {
            int m=len/3;
            for (LL *p=A;p!=A+N;p+=len)
                for (int i=0;i<m;++i)   {
                    LL &x=p[i],&y=p[i+m],&z=p[i+m+m];
                    tie(x,y,z)=make_tuple(
                        (x+y+z)%modu,
                        (x+w2*y+w1*z)%modu,
                        (x+w1*y+w2*z)%modu
                    );
                }
        }
        for (int i=0;i<N;++i)
            A[i]=A[i]*I%modu;
    }
} T;

const int N=8,S=6561,maxp=8;

LL K,P;
LL pw3[N]={1};

LL dp[maxp][S],t1[maxp][S],t2[maxp][S];

int main()  {
    for (int i=1;i<N;++i)   pw3[i]=pw3[i-1]*3%modu;

    while (~scanf("%lld%lld",&K,&P))    {
        memset(dp,0,sizeof(dp));
        memset(t1,0,sizeof(t1));
        for (int i=0;i<N;++i)   {
            ++t1[i%P][pw3[i]];
            if (i)
                ++dp[i%P][pw3[i]];
        }
        for (int i=0;i<N;++i)
            T.DFT(dp[i]),T.DFT(t1[i]);
        auto copy=[&](LL a[maxp][S])  {
            for (int i=0;i<P;++i)
                for (int s=0;s<S;++s)
                    t2[i][s]=a[i][s],a[i][s]=0;
        };
        int d=8;
        for (--K;K;K>>=1)   {
            if (K&1)    {
                copy(dp);
                for (int i=0;i<P;++i)
                    for (int j=0;j<P;++j)   {
                        int k=(i*d+j)%P;
                        for (int s=0;s<S;++s)
                            add(dp[k][s],t2[i][s]*t1[j][s]);
                    }
            }
            copy(t1);
            for (int i=0;i<P;++i)
                for (int j=0;j<P;++j)   {
                    int k=(i*d+j)%P;
                    for (int s=0;s<S;++s)
                        add(t1[k][s],t2[i][s]*t2[j][s]);
                }
            d=d*d%P;
        }
        T.IDFT(dp[0]);
        printf("%lld\n",dp[0][0]);
    }
    return 0;
}
