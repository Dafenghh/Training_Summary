#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
 
struct node {
    LL x,y;
    node(LL _x=0,LL _y=0)   {
        x=_x,y=_y;
    }
    node operator - (const node& N) const {
        return node(x-N.x,y-N.y);
    }
    LL operator * (const node &N)   const   {
        return x*N.y-y*N.x;
    }
} ;
 
 
int main()  {
    LL x1,y1,x2,y2,x3,y3;
    while (~scanf("%lld%lld%lld%lld%lld%lld",&x1,&y1,&x2,&y2,&x3,&y3))  {
        node A(x1,y1),B(x2,y2),C(x3,y3);
        LL ans=abs((B-A)*(C-A))*11;
        printf("%lld\n",ans);
    }
    return 0;
}
