#include<bits/stdc++.h>
#define maxn 1000050
#define A 13
#define maxb 4
#define modu 998244353
using namespace std;
typedef long long LL;

int n;
char s[maxn];

int F3[A+1]={1};
int pre[maxn][A+1][maxb];

int chr(char c) {   return c-'A';  };
void init()
{
    scanf("%d%s",&n,s+1);
    for (int i=1;i<=n;++i)
    {
        memcpy(pre[i][0],pre[i-1][0],sizeof(pre[i][0]));
        pre[i][0][chr(s[i])]=i;
    }
    
    for (int i=1;i<=A;++i)    F3[i]=F3[i-1]*3;
    for (int b=0;b<maxb;++b)
        for (int j=1;F3[j]<=n;++j)
            for (int i=F3[j];i<=n;++i)
                if (pre[i][j-1][b]&&pre[pre[i][j-1][b]-1][j-1][b])
                    pre[i][j][b]=pre[pre[pre[i][j-1][b]-1][j-1][b]-1][j-1][b];
}

LL dp[maxn][A+1][2];
LL ls[maxn][A+1],rs[maxn][A+1],sum[maxn];

LL add(LL &a,LL b)  {   a=(a+b+modu)%modu;   }

void solve()
{
    dp[0][0][0]=sum[0]=rs[0][0]=1;
    for (int a=0;a<=A;++a)
        ls[0][0]=1;

    for (int i=1;i<=n;++i)
    {
        int b=chr(s[i]);
        for (int a=0,k,j;~(k=pre[i][a][b]-1);++a)
        {
            add(dp[i][a][0],sum[k]);

            if (!(j=pre[k][0][b])) continue;
            add(dp[i][a][0],rs[j][a+1]-sum[j]);
            add(dp[i][a][1],dp[j][a][0]);

            if (!a) continue;
            if (s[j+1]!=s[i])
            {
                add(dp[i][a][0],ls[j][a-1]);
                if (s[j-1]==s[i])
                    add(dp[i][a][0],ls[j-1][a-1]);
            }
        }

        ls[i][0]=dp[i][0][0]+dp[i][0][1];
        for (int a=1;a<=A;++a)
            add(ls[i][a],ls[i][a-1]+dp[i][a][0]+dp[i][a][1]);
        rs[i][A]=dp[i][A][0]+dp[i][A][1];
        for (int a=A-1;~a;--a)
            add(rs[i][a],rs[i][a+1]+dp[i][a][0]+dp[i][a][1]);
        add(sum[i],sum[i-1]+rs[i][0]);
    }

    printf("%lld\n",sum[n]-1);
}

int main()
{
    init();
    solve();
    return 0;
}

/*
10
DAABCDDBDD
9
DAABDDBDD
10
CADADDBADD
7
AACAADA 
*/
