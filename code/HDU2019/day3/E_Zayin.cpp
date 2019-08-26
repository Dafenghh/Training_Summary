#include<bits/stdc++.h>
#define maxn 500050
#define modu 1000000007
using namespace std;
typedef long long LL;

const LL inv2=(modu+1)/2;
const LL inv3=(modu+1)/3;

LL cf[maxn];

LL n,K;

bool noprime[maxn];
LL p[maxn],pnum;
LL phi[maxn];

LL Dj[maxn],DJ[maxn];

void predo()    {
    pnum=1; 
    phi[1]=1;
    for (int i=2;i<maxn;++i)    {
        if (!noprime[i])
            phi[p[pnum++]=i]=i-1;
        for (int j=1;j<pnum&&i*p[j]<maxn;++j)    {
            noprime[i*p[j]]=1;
            if (i%p[j])
                phi[i*p[j]]=phi[i]*(p[j]-1);
            else    {
                phi[i*p[j]]=phi[i]*p[j];
                break;
            }
        }
    }
    for (int i=1;i<maxn;++i)    
        Dj[i]=(Dj[i-1]+(LL)i*i%modu*phi[i])%modu;
}

LL S1(LL n)    {    n%=modu; return n*(n+1)%modu*inv2%modu;    }
LL S2(LL n)    {    n%=modu; return S1(n)*(2*n+1)%modu*inv3%modu;    }
LL S3(LL n)    {    n%=modu; return S1(n)*S1(n)%modu;    }

LL dj_calc(LL n)    {
    if (n<maxn)    return Dj[n];
    if (~DJ[::n/n]) return DJ[::n/n];
    LL ans=S3(n);
    for (LL i=2,j,t;i<=n;i=j+1)    {
        j=n/(t=n/i);
        LL res=(S2(j)-S2(i-1)+modu)*dj_calc(t)%modu;
        ans=(ans-res+modu)%modu;
    }
    return DJ[::n/n]=ans;
}

LL bf_calc(LL n)    {
    LL ans=0;
    for (int i=1;i<=n;++i)
        ans=(ans+(LL)i*i%modu*phi[i])%modu;
    return ans;
}

int m,sz;
int id1[maxn],id2[maxn];
LL w[maxn],g[maxn],sp[maxn];

int id(LL x)    {
    return x<maxn?id1[x]:id2[n/x];
}

LL pw(LL a,LL k=modu-2)    {
    LL ans=1;
    for (;k;k>>=1)    {
        if (k&1)
            ans=ans*a%modu;
        a=a*a%modu;
    }
    return ans;
}

LL L[maxn],R[maxn];
LL Q[maxn];

LL cz(LL x)    {
    x%=modu;
    
    L[0]=R[K+4]=1;
    for (int i=1;i<=K+3;++i)    L[i]=L[i-1]*(x-i+modu)%modu;
    for (int i=K+3;i>=1;--i)    R[i]=R[i+1]*(x-i+modu)%modu;
    LL ans=0; 
    for (int i=1;i<=K+3;++i)    {
        ans=(ans+L[i-1]*R[i+1]%modu*Q[i]%modu*cf[i])%modu; 
    }
    return ans; 
}

LL bf_psum(LL n)    {
    LL ans=0;
    for (int i=1;p[i]<=n;++i)
        ans=(ans+pw(p[i],K+1))%modu;
    return ans;
}

LL bf() {
    LL ans=0;
    for (int i=1;p[i]<=n;++i)   {
        LL m=n/p[i],res=0;
        // res=bf_calc(m);
        for (int j=1;j<=m;++j)
            for (int k=1;k<j;++k)
                if (__gcd(j,k)==1)
                    res=(res+k*j)%modu;
        res=(res*2+1)%modu;
        // cout<<m<<" "<<res<<" "<<bf_calc(n/p[i])<<endl;
        assert(res==bf_calc(n/p[i]));
        ans=(ans+pw(p[i],K+1)*res)%modu;
    }
    return ans;
}

int main()    {
    predo();
    int T;
    scanf("%d",&T);
    while (T--)    {
        scanf("%lld%d",&n,&K);
        for (sz=1;p[sz]*p[sz]<=n;++sz)    ;
        for (int i=1;i<=K+3;++i)
            cf[i]=(cf[i-1]+pw(i,K+1))%modu;
        for (int i=1;i<=K+3;++i)    {
            for (int j=Q[i]=1;j<=K+3;++j)
                if (i!=j)
                    Q[i]=Q[i]*(i-j+modu)%modu;
            assert(Q[i]);
            Q[i]=pw(Q[i]);
        }

        for (int i=1;i<=sz;++i)    sp[i]=(sp[i-1]+pw(p[i],K+1))%modu; 
        
        m=0;
        for(LL i=1,j,t;i<=n;i=j+1)    {
            j=n/(t=n/i); w[++m]=n/i;
            g[m]=(cz(w[m])-1)%modu; 
            if(w[m]<maxn)
                id1[w[m]]=m;
            else 
                id2[j]=m;
        }
        for(int j=1;j<sz;++j)
            for(int i=1;i<=m&&p[j]*p[j]<=w[i];++i)    {
                int k=id(w[i]/p[j]);
                g[i]=(g[i]-pw(p[j],K+1)*(g[k]-sp[j-1])%modu+modu)%modu;
            }
        for (int i=1;i<=m;++i)  DJ[i]=-1;

        #define check_limit 100000
        // for (int i=1;i<=m;++i)  
        //     if (w[i]<check_limit)
        //         assert(g[i]==bf_psum(w[i]));

        LL ans=0;
        for (LL i=2,j,t;i<=n;i=j+1)    {
            j=n/(t=n/i);
            // if (t<check_limit)
            //     assert(dj_calc(t)==bf_calc(t));
            LL res=dj_calc(t)*(g[id(j)]-g[id(i-1)]+modu)%modu;
            ans=(ans+res)%modu;
        }
        // printf("bf:%lld\n",bf());
        printf("%lld\n",ans);
    }
    return 0;
}
