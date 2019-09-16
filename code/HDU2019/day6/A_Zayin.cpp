#include<bits/stdc++.h>
#define maxn 300050
using namespace std;
typedef long long LL;

int n,m;
int a[maxn];

vector<pair<int,LL> > C[maxn];
vector<int> G[maxn];

int son[maxn],len[maxn]={-1};

LL ans;
map<int,LL> dp[maxn];

void dfs1(int i)    {
    son[i]=0;
    for (int j:G[i])    {
        dfs1(j);
        if (len[son[i]]<len[j])
            son[i]=j;
    }
    len[i]=len[son[i]]+1;
}

void dfs2(int i)    {
    dp[i].clear();
    if (son[i]) {
        dfs2(son[i]);
        swap(dp[i],dp[son[i]]);
    }
    for (int j:G[i])    {
        if (son[i]==j)  continue;
        dfs2(j);
        for (auto &p:dp[j]) {
            int t=len[i]+p.first-len[j]-1;
            dp[i][t]+=p.second;
        }
    }
    // cout<<"dfs2:"<<i<<endl;
    dp[i][len[i]]+=a[i];
    sort(C[i].rbegin(),C[i].rend());
    for (auto q:C[i])  {
        while (q.second)    {
            auto it=dp[i].lower_bound(len[i]-q.first);
            if (it==dp[i].end())  break;
            LL t=min(it->second,q.second);
            it->second-=t,q.second-=t;
            ans-=t;
            if (!it->second)   dp[i].erase(it);
        }
        if (!dp[i].size())  break;
    }
}

int main()  {
    int T;
    scanf("%d",&T);
    while (T--) {
        scanf("%d%d",&n,&m);
        ans=0;
        for (int i=1;i<=n;++i)  
            G[i].clear(),C[i].clear();
        for (int f,i=2;i<=n;++i)  {
            scanf("%d",&f);
            G[f].push_back(i);
        }
        for (int i=1;i<=n;++i)  
            scanf("%d",a+i),ans+=a[i];
        while (m--) {
            int x,k,c;
            scanf("%d%d%d",&x,&k,&c);
            C[x].emplace_back(k,c);
        }
        dfs1(1);
        // cout<<"???"<<endl;
        dfs2(1);
        printf("%lld\n",ans);
    }
    return 0;
}
