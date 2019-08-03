#include<bits/stdc++.h>
#define maxn 2050
using namespace std;
 
int n;
int mp[maxn];
int a[maxn][maxn];
int b[maxn][maxn];
 
int to[]={2,0,3,1};
 
void draw(int n,int a,int b)  {
    for (int i=0;i<n;++i)
        for (int j=0;j<n;++j)
            if (i%4==a&&j%4==b&&i!=j)
                ::a[i][j]=::a[j][i]=1;
}
 
bool judge()    {
    for (int i=0;i<n;++i)
        for (int j=0;j<n;++j)
            b[mp[i]][mp[j]]=a[i][j];
    // for (int i=0;i<n;++i)  {
    //     for (int j=0;j<n;++j)
    //         printf("%d",b[i][j]);
    //     puts("");
    // }
    for (int i=0;i<n;++i)
        for (int j=0;j<n;++j)
            if (i!=j&&a[i][j]==b[i][j])
                return 0;
    return 1;
}
 
int main()  {
    int T,icase=0;
    scanf("%d",&T);
    while (T--) {
        scanf("%d",&n);
        if (n%4&&(n-1)%4)
            printf("Case #%d: No\n",++icase);
        else    {
            printf("Case #%d: Yes\n",++icase);
            for (int i=0;i<n;++i)
                for (int j=0;j<n;++j)
                    a[i][j]=0;
            int N=n-n%4;
            draw(N,1,1);
            draw(N,2,2);
            draw(N,0,1);
            draw(N,1,2);
            draw(N,2,3);
            if (n%4)
                for (int i=0;i<N;++i)
                    if (i%4==1||i%4==2)
                        a[N][i]=a[i][N]=1;
            for (int i=0;i<n;++i)  {
                for (int j=0;j<n;++j)
                    printf("%d",a[i][j]);
                puts("");
            }
            mp[N]=N;
            for (int i=0;i<N;i+=4)
                for (int j=0;j<4;++j)
                    mp[i+j]=i+to[j];
            for (int i=0;i<n;++i)
                printf("%d%c",mp[i]+1," \n"[i==n-1]);
            assert(judge());
        }
    }
    return 0;
}
