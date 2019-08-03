#include<bits/stdc++.h>
#define maxh 20
#define maxn 100050
using namespace std;
 
int n,Log2[maxn]={-1};
int stk[maxn],tp;
struct Array    {
    int a[maxn];
    int L[maxn];
    void init(int n)    {
        for (int i=1;i<=n;++i)   scanf("%d",a+i);
        tp=0;
        for (int i=1;i<=n;++i)   {
            while (tp&&a[stk[tp]]>a[i])  --tp;
            L[i]=stk[tp];
            stk[++tp]=i;
        }
    }
} A,B;
 
void init() {
    A.init(n);
    B.init(n);
}
 
void solve()    {
    int i;
    for (i=1;i<=n;++i)   {
        if (A.L[i]!=B.L[i])
            break;
    }
    printf("%d\n",i-1);
}
 
int main()  {
    for (int i=1;i<=n;++i)   Log2[i]=Log2[i>>1]+1;
    while (~scanf("%d",&n)) {
        init();
        solve();
    }
    return 0;
}
