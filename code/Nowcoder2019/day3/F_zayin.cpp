#include<bits/stdc++.h>
#define maxn 505
using namespace std;
typedef long long LL;
 
const int inf=1<<30;
 
int n,m;
int a[maxn][maxn];
 
void init() {
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;++i)
        for (int j=1;j<=n;++j)
            scanf("%d",a[i]+j);
}
 
int a1[maxn],a2[maxn];
 
int q1[maxn],l1,r1; // mn
int q2[maxn],l2,r2; // mx
 
void solve()    {
    int ans=0;
    for (int l=1;l<=n;++l)   {
        for (int i=1;i<=n;++i)   a1[i]=inf,a2[i]=0;
        for (int r=l;r<=n;++r)   {
//          cout<<l<<" "<<r<<":"<<endl;
            for (int i=1;i<=n;++i)
                a1[i]=min(a1[i],a[i][r]),
                a2[i]=max(a2[i],a[i][r]);
             
            l1=l2=1,r1=r2=0;
            for (int i=1,j=1;i<=n;++i)   {
//              cout<<i<<":"<<endl;
                while (l1<=r1&&a1[q1[r1]]>=a1[i]) --r1;
                q1[++r1]=i;
                while (l2<=r2&&a2[q2[r2]]<=a2[i]) --r2;
                q2[++r2]=i;
                 
//              cout<<"q1:"; for (int j=l1;j<=r1;++j)  cout<<q1[i]<<" "; cout<<endl;
//              cout<<"q2:"; for (int j=l2;j<=r2;++j)  cout<<q2[i]<<" "; cout<<endl;
                while (j<=i&&a2[q2[l2]]-a1[q1[l1]]>m) {
                    ++j;
//                  cout<<j<<" "<<l1<<" "<<r1<<" "<<l2<<" "<<r2<<endl;
                    while (l1<=r1&&q1[l1]<j)  ++l1;
                    while (l2<=r2&&q2[l2]<j)  ++l2;
                }
                ans=max(ans,(r-l+1)*(i-j+1));
            }
        }
    }
    printf("%d\n",ans);
}
 
int main()  {
    int T;
    scanf("%d",&T);
    while (T--) {
        init();
        solve();
    }
    return 0;
}
