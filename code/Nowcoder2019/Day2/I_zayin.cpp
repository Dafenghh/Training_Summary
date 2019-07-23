#include<bits/stdc++.h>
#define maxn 55
using namespace std;
  
const int inf=1LL<<30;
  
int n,m;
int a[maxn][maxn];
int sum[maxn][maxn];
  
int Lm[maxn],Rm[maxn];
int Um[maxn],Dm[maxn];
  
int A[maxn][maxn][maxn][maxn];
int U[maxn][maxn][maxn],D[maxn][maxn][maxn],L[maxn][maxn][maxn],R[maxn][maxn][maxn];
  
int S(int u,int d,int l,int r)  {
    return sum[d][r]-sum[d][l-1]-sum[u-1][r]+sum[u-1][l-1];
}
 
void Max(int &a,int b)  {
    a=max(a,b);
}
  
int main()  {
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;++i)
        for (int j=1;j<=m;++j)   {
            scanf("%d",a[i]+j);
            sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a[i][j];
        }
    // for (int i=1;i<=n;++i)   Um[i]=Dm[i]=-inf;
    // for (int i=1;i<=m;++i)   Lm[i]=Rm[i]=-inf;
    // memset(L,0x80,sizeof(L));
    // memset(R,0x80,sizeof(R));
    // memset(U,0x80,sizeof(U));
    // memset(D,0x80,sizeof(D));
      
    for (int u=1;u<=n;++u)
        for (int d=u;d<=n;++d)
            for (int l=1;l<=m;++l)
                for (int r=l;r<=m;++r)  {
                    int a=S(u,d,l,r);
                    A[u][d][l][r]=a;
                    Max(L[r][u][d],a);
                    Max(R[l][u][d],a);
                    Max(U[d][l][r],a);
                    Max(D[u][l][r],a);
                    Max(Lm[r],a);
                    Max(Rm[l],a);
                    Max(Um[d],a);
                    Max(Dm[u],a);
                }
    // for (int l=1;l<=m;++l)
    //     for (int r=l;r<=m;++r)
    //         for (int i=1;i<=n;++i)
    //             cout<<i<<" "<<l<<" "<<r<<":"<<U[i][l][r]<<endl;
 
    int ans=0;
    for (int u=1;u<=n;++u)
        for (int d=u;d<=n;++d)
            for (int l=1;l<=m;++l)
                for (int r=l;r<=m;++r)   {
                    int a=S(u,d,l,r);
                      
                    // cout<<u<<" "<<d<<" "<<l<<" "<<r<<":"<<endl;
                    //part1 up-left + down-right
                    {
                        int ans1=-inf,ans2=-inf;
                        for (int i=1;i<=l;++i)   ans1=max(ans1,S(u,d,i,l-1)+U[u-1][i][r]);
                        for (int i=r;i<=m;++i)   ans2=max(ans2,S(u,d,r+1,i)+D[d+1][l][i]);
                        ans=max(ans,ans1+ans2);
                        // cout<<"part1:"<<ans1<<" "<<ans2<<endl;
                    }
                      
                    //part2 down-left + up-right
                    {
                        int ans1=-inf,ans2=-inf;
                        for (int i=1;i<=l;++i)   ans1=max(ans1,S(u,d,i,l-1)+D[d+1][i][r]);
                        for (int i=r;i<=m;++i)   ans2=max(ans2,S(u,d,r+1,i)+U[u-1][l][i]);
                        ans=max(ans,ans1+ans2);
//                      cout<<"part2:"<<ans1<<" "<<ans2<<endl;
                    }
 
                    //part3 edge-contain
                   {
                        //left
                        {
                            int ans1=L[l-1][u][d],ans2=-inf;
                            for (int i=r;i<=m;++i)  ans2=max(ans2,S(u,d,r+1,i)+U[u-1][l][i]+D[d+1][l][i]);
                            ans=max(ans,ans1+ans2);
                            // cout<<ans1<<"+"<<ans2<<endl;
                        }
                        //right
                        {
                            int ans1=R[r+1][u][d],ans2=-inf;
                            for (int i=1;i<=l;++i)  ans2=max(ans2,S(u,d,i,l-1)+U[u-1][i][r]+D[d+1][i][r]);
                            ans=max(ans,ans1+ans2);
                        }
                        //up
                        {
                            int ans1=U[u-1][l][r],ans2=-inf;
                            for (int i=d;i<=n;++i)  ans2=max(ans2,S(d+1,i,l,r)+L[l-1][u][i]+R[r+1][u][i]);
                            ans=max(ans,ans1+ans2);
                        }
                        //down
                        {
                            int ans1=D[d+1][l][r],ans2=-inf;
                            for (int i=1;i<=u;++i)  ans2=max(ans2,S(i,u-1,l,r)+L[l-1][i][d]+R[r+1][i][d]);
                            ans=max(ans,ans1+ans2);
                        }
                   }
 
                   //part3 cross
                   {
                       ans=max(ans,U[u-1][l][r]+D[d+1][l][r]+L[l-1][u][d]+R[r+1][u][d]);
                   }
                }
     
    // cout<<"ans:"<<ans<<endl;
   for (int u=1;u<=n;++u)
        for (int d=u;d<=n;++d)
            for (int l=1;l<=m;++l)
                for (int r=l;r<=m;++r)   {
                    for (int i=u;i<=d;++i)
                        A[u][d][l][r]=min(A[u][d][l][r],A[i][d][l][r]);
                }
    for (int u=1;u<=n;++u)
        for (int d=u;d<=n;++d)
            for (int l=1;l<=m;++l)
                for (int r=l;r<=m;++r)   {
                    for (int i=u;i<=d;++i)
                        A[u][d][l][r]=min(A[u][d][l][r],A[u][i][l][r]);
                }
    for (int u=1;u<=n;++u)
        for (int d=u;d<=n;++d)
            for (int l=1;l<=m;++l)
                for (int r=l;r<=m;++r)   {
                    for (int i=l;i<=r;++i)
                        A[u][d][l][r]=min(A[u][d][l][r],A[u][d][i][r]);
                }
    for (int u=1;u<=n;++u)
        for (int d=u;d<=n;++d)
            for (int l=1;l<=m;++l)
                for (int r=l;r<=m;++r)   {
                    for (int i=l;i<=r;++i)
                        A[u][d][l][r]=min(A[u][d][l][r],A[u][d][l][i]);
                }
                  
    for (int u=1;u<=n;++u)
        for (int d=u;d<=n;++d)
            for (int l=1;l<=m;++l)
                for (int r=l;r<=m;++r)
                    ans=max(ans,S(u,d,l,r)-A[u][d][l][r]);
      
      
    for (int i=1;i<=n;++i)   Um[i]=max(Um[i-1],Um[i]);
    for (int i=n;i;--i)     Dm[i]=max(Dm[i+1],Dm[i]);
    for (int i=1;i<=n;++i)   ans=max(ans,Um[i-1]+Dm[i]);
      
    for (int i=1;i<=m;++i)   Lm[i]=max(Lm[i-1],Lm[i]);
    for (int i=m;i;--i)     Rm[i]=max(Rm[i+1],Rm[i]);
    for (int i=1;i<=m;++i)   ans=max(ans,Lm[i-1]+Rm[i]);
    printf("%d\n",ans);
    return 0;
}
