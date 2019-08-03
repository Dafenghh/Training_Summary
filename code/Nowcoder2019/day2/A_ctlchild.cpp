#include<bits/stdc++.h>
#define rep(i,l,r) for (int i=l;i<=r;i++)
using namespace std;
typedef long long ll;
const ll mm=1e9+7;
int tt,n,m;
ll Pow(ll x,ll y){
    ll ans=1;
    while (y){
        if (y&1) ans=ans*x%mm;
        x=x*x%mm;
        y/=2;
    }
    return ans;
}
ll ans=1;
int main(){
    scanf("%d",&tt);
    while (tt--){
        scanf("%d%d",&n,&m);
        if (n==1) ans*=1;
        else{
            if (m==0) ans=ans*0;
            else ans=ans*Pow(n-1,mm-2)%mm;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
