#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=l;i<=r;i++)
using namespace std;
typedef long long ll;
const int maxn=100500;
ll ans;
ll fac[maxn],a[maxn],va[maxn],vb[maxn],tmp[maxn];
vector<ll> vec1,vec2;
const ll mm=1e9+7;
int n,sz;
int jud(ll a[],ll x){
    for (int i=60;i>=0;i--) if (x&(1ll<<i)){
        if (a[i]) x^=a[i];
        else {a[i]=x; return 1;}
    }
    return 0;
}
int main(){
    fac[0]=1;
    rep(i,1,100000) fac[i]=fac[i-1]*2%mm;
    while (~scanf("%d",&n)){
        rep(i,0,60) va[i]=vb[i]=0;
        ans=0;
        vec1.clear(); vec2.clear();
        rep(i,1,n) scanf("%lld",&a[i]);
        rep(i,1,n) {
            if (jud(va,a[i])) vec1.push_back(a[i]);
            else vec2.push_back(a[i]);
        }
        int sz=0;
        for (auto x:vec2) sz+=jud(vb,x);
        ans=1ll*(n-vec1.size())*fac[vec2.size()-1]%mm;
        for (int i=0;i<(int)vec1.size();i++){
            rep(j,0,60) tmp[j]=vb[j];
            int now=sz;
            for (int j=0;j<(int)vec1.size();j++) if (i!=j){
                now+=jud(tmp,vec1[j]);
            }
            if (!jud(tmp,vec1[i])) (ans+=fac[n-now-1])%=mm;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
