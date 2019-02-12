#include<bits/stdc++.h>
#define maxn 300050
#define g 3
#define modu 998244353
using namespace std;
typedef long long LL;

LL pw(LL a,LL k=modu-2)
{
    LL ans=1;
    for (;k;k>>=1) {
        if (k&1)
            ans=ans*a%modu;
        a=a*a%modu;
    }
    return ans;
}

struct NTT
{
    LL t[maxn];

    void DFT(LL *A,int n)
    {
        for (int i=1,j=0;i<n;++i) {
            for (int s=n>>1;j^=s,j<s;s>>=1) ;
            if (i<j)
                swap(A[i],A[j]);
        }

        for (int len=2;len<=n;len<<=1)
        {
            int m=len>>1,_w=pw(g,(modu-1)/len);
            for (int i=0,w=1;i<m;++i,w=(LL)w*_w%modu)
                for (LL *p=A;p!=A+n;p+=len)
                {
                    LL u=p[i],v=p[i+m]*w%modu;
                    p[i]=(u+v)%modu;
                    p[i+m]=(u-v+modu)%modu;
                }
        }
    }

    void IDFT(LL *A,int n)
    {
        DFT(A,n);
        reverse(A+1,A+n);
        for (int i=0,I=pw(n);i<n;++i)
            A[i]=A[i]*I%modu;
    }

    void Inv(LL *A,LL *B,int n)
    {
        if (n==1) {
            *B=pw(*A);
            return ;
        }
        
        Inv(A,B,n>>1);
        int N=n<<1;
        for (int i=0;i<n;++i)   t[i]=A[i];
        for (int i=n;i<N;++i)   t[i]=B[i]=0;
        DFT(t,N),DFT(B,N);
        for (int i=0;i<N;++i)
            B[i]=B[i]*(2-t[i]*B[i]%modu+modu)%modu;
        IDFT(B,N);
        for (int i=n;i<N;++i)   B[i]=0;
    }
} T;

const int N=131072;
LL S[maxn],C[maxn],F[maxn],I[maxn];
LL ans[maxn];

LL sgn(int n)   {
    return n&1?modu-1:1;
}

void predo()
{
    for (int i=F[0]=1;i<=N;++i)  F[i]=F[i-1]*i%modu;
    for (int i=0;2*i+1<=N;++i)    S[2*i+1]=sgn(i)*pw(F[2*i+1])%modu;
    for (int i=0;2*i<=N;++i)    C[2*i]=sgn(i)*pw(F[2*i])%modu;
    T.Inv(C,I,N);
    T.DFT(I,N<<1),T.DFT(S,N<<1);
    for (int i=0;i<(N<<1);++i)
        ans[i]=S[i]*I[i]%modu;
    T.IDFT(ans,N<<1);
    for (int i=0;i<=N;++i)
        ans[i]=ans[i]*F[i]%modu;
}

int main()
{
    predo();
    int T,n;
    scanf("%d",&T);
    while (T--)
    {
        scanf("%d",&n);
        printf("%lld\n",ans[n]);
    }
    return 0;
}
