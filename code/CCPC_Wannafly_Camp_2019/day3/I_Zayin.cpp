#include<bits/stdc++.h>
#define maxn 200050
#define modu 998244353
using namespace std;
typedef long long LL;

const LL W2=665496236,I2=499122177;

int n,m;
int fa[maxn];
LL w[maxn],val[maxn];

LL pw(LL a,int k=modu-2)    {
    LL ans=1;
    for (;k;k>>=1)  {
        if (k&1)
            ans=ans*a%modu;
        a=a*a%modu;
    }
    return ans;
}

int find(int i) {
    if (fa[i]==i)   return i;
    int j=find(fa[i]);
    val[i]=val[i]*val[fa[i]]%modu;
    return fa[i]=j;
}

int main()  {
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;++i)
        fa[i]=i,w[i]=val[i]=1;
    while (m--) {
        int op,x,y;
        scanf("%d%d",&op,&x);
        if (op==1)  {
            scanf("%d",&y);
            fa[y]=x;
            val[y]=(w[y]=w[y]*I2%modu*pw(w[x])%modu);
            w[x]=w[x]*W2%modu;
        } else  {
            y=find(x);
            printf("%lld\n",w[y]*val[x]%modu*pw(3,n)%modu);
        }
    }
    return 0;
}
