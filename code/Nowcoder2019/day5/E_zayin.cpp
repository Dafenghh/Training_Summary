#include<bits/stdc++.h>
#define maxn 26
#define maxs 67500000
using namespace std;
 
int n,m,all;
 
char dp[maxs];
int adj[maxn];
 
int cnt(int s) {
    return __builtin_popcount(s);
}
int low(int s)  {
    return cnt((s&-s)-1);
}
 
char Max(char a,char b) {
    return a>b?a:b;
}
 
int main()  {
    scanf("%d%d",&n,&m),all=1<<n;
    while (m--) {
        int u,v;
        scanf("%d%d",&u,&v);
        adj[u]|=1<<v;
        adj[v]|=1<<u;
    }
    int ans=0;
    char one=1;
    for (int s=1;s<all;++s) {
        int i=low(s),t=s^1<<i;
        // ok[s]=ok[s^(1<<i)]||ok[s&~adj[i]];
        dp[s]=Max(dp[t],dp[t&~adj[i]]+one);
        ans+=dp[s];
    }
    printf("%d\n",ans);
    return 0;
}
