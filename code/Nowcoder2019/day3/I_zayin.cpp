#include<bits/stdc++.h>
#define mkp make_pair
#define maxn 100050
using namespace std;
 
int n,A[maxn];
 
vector<int> a[maxn];
 
void init() {
    scanf("%d",&n);
    for (int i=1;i<=n;++i)   a[i].clear();
    for (int i=2;i<n;++i)    {
        scanf("%d",A+i);
        for (int j=i-1;j<=i+1;++j)
            a[j].push_back(A[i]);
    }
}
 
bool dp[maxn][3][3];
int prt[maxn][3][3];
 
int mid(vector<int> a)    {
    assert(a.size()==3);
    sort(a.begin(),a.end());
    return a[1];
}
 
void print(int i,int x,int y)   {
    if (i==2)
        printf("%d %d ",a[i-1][x],a[i][y]);
    else    {
        print(i-1,prt[i][x][y],x);
        printf("%d ",a[i][y]);
    }
}
 
void solve()    {
    memset(dp[2],0,sizeof(dp[2]));
    for (int i=0;i<a[1].size();++i)
        for (int j=0;j<a[2].size();++j)
            dp[2][i][j]=1;
             
    for (int i=3;i<=n;++i)   {
        memset(dp[i],0,sizeof(dp[i]));
        for (int c=0;c<a[i].size();++c)  {
            for (int x=0;x<3;++x)
                for (int y=0;y<3;++y)    {
                    if (!dp[i-1][x][y]) continue;
                    if (mid(vector<int>{a[i-2][x],a[i-1][y],a[i][c]})==A[i-1])    {
                        dp[i][y][c]=1,prt[i][y][c]=x;
                    }
                }
        }
    }
    for (int x=0;x<3;++x)
        for (int y=0;y<3;++y)
            if (dp[n][x][y])    {
                print(n,x,y),puts("");
                return ;
            }
    puts("-1");
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
