#include<bits/stdc++.h>
#define maxn 1050
using namespace std;
 
int n,m;
char s[maxn];
 
int h[maxn];
 
int stk[maxn],tp;
int L[maxn],R[maxn];
 
int cnt[maxn][maxn];
 
int main()  {
    scanf("%d%d",&n,&m);
    int ans=0;
    for (int i=1;i<=n;++i)   {
        scanf("%s",s+1);
        for (int j=1;j<=m;++j)
            if (s[j]=='1')
                ++h[j];
            else
                h[j]=0;
        stk[tp=0]=0;
        for (int j=1;j<=m;++j)   {
            while (tp&&h[j]<h[stk[tp]])  --tp;
            L[j]=stk[tp];
            stk[++tp]=j;
        }
        stk[tp=0]=m+1;
        for (int j=m;j;--j) {
            while (tp&&h[j]<=h[stk[tp]]) --tp;
            R[j]=stk[tp];
            stk[++tp]=j;
        }
        for (int j=1;j<=m;++j)
//          cout<<i<<" "<<j<<":"<<h[j]<<"*"<<R[j]-L[j]-1<<" "<<L[j]<<" "<<R[j]<<endl,
            ans=max(ans,h[j]*(R[j]-L[j]-1)),
            ++cnt[h[j]][R[j]-L[j]-1];
    }
    int c=0;
    for (int i=1;i<=n;++i)
        for (int j=1;j<=m;++j)
            if (cnt[i][j]&&i*j==ans)
                c+=cnt[i][j];
//  cout<<c<<endl;
    if (c>1)
        printf("%d\n",ans);
    else    {
        int res=0;
        for (int i=1;i<=n;++i)
            for (int j=1;j<=m;++j)   {
                if (!cnt[i][j]) continue;
                if (i*j==ans)
//                  cout<<(i-1)*j<<endl,cout<<i*(j-1)<<endl,
                    res=max(res,(i-1)*j),res=max(res,i*(j-1));
                else
//                  cout<<i*j<<endl,
                    res=max(res,i*j);
            }
        printf("%d\n",res);
    }
    return 0;
}
