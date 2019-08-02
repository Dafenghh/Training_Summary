#include<bits/stdc++.h>
#define maxn 1500500
using namespace std;
typedef long long LL;

const LL BS=1500050,GS=750;

LL n,a,b,x0,p,Iv;
LL B[maxn]={1},G[maxn]={1};
LL Ig[maxn]={1};

// vector<pair<LL,int> > I;
// unordered_map<LL,int> I;
pair<LL,int> d[maxn];
int m;
LL val[maxn],pos[maxn];

LL pw(LL a,LL k)    {
    LL ans=1;
    for (a%=p;k;k>>=1)  {
        if (k&1)
            ans=ans*a%p;
        a=a*a%p;
    }
    return ans;
}

LL inv(LL a)    {
    return pw(a,p-2);
}

LL T1=0;

void init() {
    scanf("%lld%lld%lld%lld%lld",&n,&x0,&a,&b,&p);
    for (int i=1;i<=BS;++i)    B[i]=B[i-1]*a%p;
    for (int i=1;i<GS;++i)    G[i]=G[i-1]*B[BS]%p;
    for (int i=BS-1;~i;--i)
        d[i]={B[i],i};
    sort(d,d+BS);
    for (int i=m=0,j=0;i<BS;i=j)    {
        while (j<BS&&d[i].first==d[j].first)    ++j;
        val[m]=d[i].first,pos[m]=d[i].second,++m;
        // cout<<d[i].first<<" "<<d[i].second<<" "<<B[d[i].second]<<endl;
    }
    Iv=inv(a*x0-x0+b);
    for (int i=0;i<GS;++i)
        Ig[i]=inv(G[i]);
}


void solve()    {
    int q;
    scanf("%d",&q);
    while (q--) {
        LL v,ans=1LL<<60;
        scanf("%lld",&v);
        if (!a) {
            if (x0==v)
                ans=0;
            else
            if (b==v)
                ans=1;
        } else  
        if (a==1)   {
            if (b)
                ans=(v-x0+p)*inv(b)%p;
            else
            if (v==x0)
                ans=0;
        } else {
            // cout<<pw(67,113497383)<<" "<<v*inv(x0)%p<<" "<<Iv*(a-1)%p*v%p<<endl;
            v=(v*(a-1)+b)%p*Iv%p;
    int t1=clock();
            // cout<<"v:"<<v<<endl;
            for (int i=0;i<GS;++i)   {
                LL x=v*Ig[i]%p;
                int j=lower_bound(val,val+m,x)-val;

                if (j<m&&val[j]==x) {
                    // cout<<j<<":"<<pos[j]<<" "<<val[j]<<endl;
                    ans=i*BS+pos[j];
                    break;
                }
            }
    T1+=clock()-t1;
        }
        if (ans<n)
            printf("%lld\n",ans);
        else
            puts("-1");
    }
}

int main()  {
    int T;
    scanf("%d",&T);
    while (T--) {
        init();
        solve();
    }
    cerr<<T1<<"/"<<clock()<<endl;
    return 0;
}
