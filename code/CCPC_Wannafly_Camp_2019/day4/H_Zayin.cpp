#include<bits/stdc++.h>
#define M 505
using namespace std;

const int N=6,C=6,T=500;
int m;
double p[N][C+1];

void init()
{
    scanf("%d",&m);
    for (int i=0;i<N;++i)
        for (int j=1;j<=C;++j)
            scanf("%lf",&p[i][j]);
}

double dp[N][T+1][M],pos[N][T+1][M][C+1];

void solve()
{
    for (int i=0;i<N;++i)
    {
        for (int j=0;j<=C;++j)
        {
            pos[i][0][0][j]=1;
            for (int t=0;t<T;++t)
                for (int k=0;k<m;++k)
                {
                    for (int c=1;c<=C;++c)
                    {
                        int ed=(k+c)%m;
                        if (ed!=j)
                            pos[i][t+1][ed][j]+=p[i][c]*pos[i][t][k][j];
                    }
                }
            for (int t=0;t<=T;++t)
                for (int k=0;k<m;++k)
                    // cout<<"pos["<<i<<"]["<<k<<"]["<<k<<"]["<<j<<"]="<<pos[i][t][k][j]<<endl,
                    dp[i][t][j]+=pos[i][t][k][j];
        }

        for (int j=C+1;j<m;++j)
        {
            dp[i][0][j]=1;
            for (int t=1;t<=T;++t)
                for (int c=1;c<=C;++c)
                    dp[i][t][j]+=p[i][c]*dp[i][t-1][j-c];
        }
        
        // for (int t=0;t<=T;++t)
        //     for (int j=0;j<m;++j)
        //         printf("dp[%d][%d][%d]=%lf\n",i,t,j,dp[i][t][j]);
        // cout<<"-------------------------"<<endl;
    }
    
    for (int i=0;i<N;++i)
    {
        double ans=0;
        for (int t=1;t<=T;++t)
            for (int j=0;j<m;++j)
            {
                double p=(dp[i][t-1][j]-dp[i][t][j]);
                for (int k=0;k<i;++k)   p*=dp[k][t][j];
                for (int k=i+1;k<N;++k) p*=dp[k][t-1][j];
                ans+=p;
            }
        printf("%.3lf\n",ans);
    }
}

int main()
{
    init();
    solve();
    return 0;
}
