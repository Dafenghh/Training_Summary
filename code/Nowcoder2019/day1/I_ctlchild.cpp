#include<bits/stdc++.h>
#define rep(i,l,r) for (int i=l;i<=r;i++)
using namespace std;
typedef long long ll;
const int maxn=200500;
const ll inf=1e18;
int cx,cy,n;
ll ans;
int vecx[maxn],vecy[maxn];
struct node{int x,y;ll a;}a[maxn];
ll t[maxn*4],tag[maxn*4];
bool cmp(node a,node b){
    return a.x<b.x||(a.x==b.x&&a.y>b.y);
}
void build(int i,int l,int r){
    t[i]=tag[i]=0;
    if (l==r) return;
    int mid=(l+r)/2;
    build(i*2,l,mid); build(i*2+1,mid+1,r);
}
void down(int i){
    if (tag[i]){
        t[i*2]+=tag[i]; tag[i*2]+=tag[i];
        t[i*2+1]+=tag[i]; tag[i*2+1]+=tag[i];
    }
    tag[i]=0;
}
ll ask(int i,int l,int r,int L,int R){
    if (L<=l&&r<=R) return t[i];
    down(i);
    int mid=(l+r)/2;
    ll ans=-inf;
    if (L<=mid) ans=max(ans,ask(i*2,l,mid,L,R));
    if (R>mid) ans=max(ans,ask(i*2+1,mid+1,r,L,R));
    return ans;
}
void cg(int i,int l,int r,int L,int R,ll x){
    if (L<=l&&r<=R) {
        t[i]+=x; tag[i]+=x; return;
    }
    down(i);
    int mid=(l+r)/2;
    if (L<=mid) cg(i*2,l,mid,L,R,x);
    if (R>mid) cg(i*2+1,mid+1,r,L,R,x);
    t[i]=max(t[i*2],t[i*2+1]);
}
void dfs(int i,int l,int r){
    printf("%d %d %d %lld %lld\n",i,l,r,t[i],tag[i]);
    if (l==r) return;
    int mid=(l+r)/2;
    dfs(i*2,l,mid); dfs(i*2+1,mid+1,r);
}
int main(){
    while (~scanf("%d",&n)){
        ans=0; cx=cy=0;
        rep(i,1,n){
            ll aa,bb;
            scanf("%d%d%lld%lld",&a[i].x,&a[i].y,&aa,&bb);
            ans+=bb;
            a[i].a=aa-bb;
            vecx[++cx]=a[i].x;
            vecy[++cy]=a[i].y;
        }
        sort(vecx+1,vecx+1+cx); cx=unique(vecx+1,vecx+1+cx)-vecx-1;
        sort(vecy+1,vecy+1+cy); cy=unique(vecy+1,vecy+1+cy)-vecy-1;
        sort(a+1,a+1+n,cmp);
        int sz=cy+1;
        build(1,1,sz);
        rep(i,1,n){
            int y=lower_bound(vecy+1,vecy+1+cy,a[i].y)-vecy+1;
            ll last=ask(1,1,sz,1,y),now=ask(1,1,sz,y,y);
            cg(1,1,sz,1,y-1,a[i].a);
            cg(1,1,sz,y,y,last-now);
        //    dfs(1,1,cy);
        }
//        printf("%lld\n",ans);
        printf("%lld\n",ans+ask(1,1,sz,1,sz));
    }
    return 0;
}
