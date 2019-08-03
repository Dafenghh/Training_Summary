#include<bits/stdc++.h>
#define rep(i,l,r) for (int i=l;i<=r;i++)
using namespace std;
typedef long long ll;
const int maxn=58000;
int n,m;
struct node{
    ll a[32];
    void insert(ll x){
        for (int i=31;i>=0;i--) if (x>>i&1){
            if (!a[i]) {a[i]=x; return;}
            else x^=a[i];
        }
    }
    bool ask(ll x){
        for (int i=31;i>=0;i--) if (x>>i&1){
            if (!a[i]) return 0;
            x^=a[i];
        }
        return 1;
    }
    ll& operator [](int x){
        return a[x];
    }   
}t[maxn*4],tmp,v1;
void merge(node &t1,node &t2,node &ans){
    tmp=v1=t1;
    rep(i,0,31) if (t2[i]){
        ll x=t2[i],now=0;
        int gg=0;
        for (int j=31;j>=0;j--) if (x>>j&1){
            if (!tmp[j]) {
                gg=1; tmp[j]=x; v1[j]=now;
                break;
            }
            else {
                x^=tmp[j]; now^=v1[j];              
            }
        }
        if (!gg) ans.insert(now);
    }
}
void build(int i,int l,int r){
    if (l==r){
        int sz; scanf("%d",&sz);
        rep(j,1,sz){
            ll x; scanf("%lld",&x);
            t[i].insert(x);
        }
        return;
    }
    int mid=(l+r)>>1;
    build(i<<1,l,mid); build(i<<1|1,mid+1,r);
    merge(t[i<<1],t[i<<1|1],t[i]);
}
bool ask(int i,int l,int r,int L,int R,ll x){
    if (L<=l&&r<=R) return t[i].ask(x);
    int mid=(l+r)>>1;
    if (L<=mid&&!ask(i<<1,l,mid,L,R,x)) return 0;
    if (R>mid&&!ask(i<<1|1,mid+1,r,L,R,x)) return 0;
    return 1;
}
int main(){
    scanf("%d%d",&n,&m);
    build(1,1,n);
    rep(i,1,m){
        int l,r; ll x;
        scanf("%d%d%lld",&l,&r,&x);
        if (ask(1,1,n,l,r,x)) puts("YES");
        else puts("NO");
    }
    return 0;
}
