#include<bits/stdc++.h>
#define rep(i,l,r) for (int i=l;i<=r;i++)
using namespace std;
typedef long long ll;
const int maxn=10050;
struct node{int x,y;double c;
    friend node operator +(node a,node b){
        return (node){a.x+b.x,a.y+b.y,0};
    }
}a[maxn],o,b[maxn];
int tt,N=3e8,n;
int getrand(){
    static uniform_int_distribution<int> u(1e8,3e8);
    static default_random_engine e(rand());
    return u(e);
    // ll x=rand(),y=rand();
    // return 1ll*x*y%N;
}
bool cmp(node a,node b){
    return a.c<b.c;
}
ll cross(node a,node b){
    return 1ll*a.x*b.y-a.y*b.x;
}
int main(){
    srand(time(0));
    scanf("%d",&tt);
    while (tt--){
        scanf("%d",&n);
        rep(i,1,n) scanf("%d%d",&a[i].x,&a[i].y);
        int cnt=30;
        while (cnt--){
            o.x=-getrand(),o.y=-getrand();
            rep(i,1,n) b[i]={a[i].x-o.x,a[i].y-o.y,0},b[i].c=atan2(b[i].y,b[i].x);
            sort(b+1,b+1+n,cmp);
            node p1=b[n/2],p2=b[n/2+1];
            if (cross(p1,p2)==0) continue;
            node oo=(p1+p2)+o;
            printf("%d %d %d %d\n",o.x,o.y,oo.x,oo.y);
            break;
        }
    }
    return 0;
}
