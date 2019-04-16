#include <bits/stdc++.h>
#define maxn 4050
#define maxl 205
#define maxc 30
#define modu 1000000007
using namespace std;
typedef long long LL;

int n,m;

int tot;
int fa[maxn*maxl],zf[maxn*maxl];
bool leaf[maxn*maxl];
int ch[maxn*maxl][maxc];

char s[maxl];

void insert()   {
    scanf("%s",s);
    int k=0;
    for (int i=0;s[i];++i)  {
        int c=s[i]-'a';
        if (!ch[k][c])  {
            ch[k][c]=++tot;
            zf[tot]=c,fa[tot]=k;
        }
        k=ch[k][c];
    }
    leaf[k]=1;
}

int rt,N;
int mp[maxn];
int val[maxn];
vector<int> G[maxn];

int newnode(int x)   {
//    cout<<"mp:"<<N<<" "<<x<<endl;
    mp[N]=x,val[N]=1;
    return N++;
}

int merge(int i)  {
    if (leaf[i]) return newnode(i);
    vector<int> son;
    for (int c=0,j;c<maxc;++c)    {
        if (!(j=ch[i][c]))  continue;
        son.push_back(merge(j));
    }
    if (son.size()==1&&i)  return ++val[son.back()],son.back();
    int k=newnode(i);
    for (int j:son)
        G[k].push_back(j);
    return k;
}

void init() {
    scanf("%d%d",&n,&m);
    for (int i=0;i<n;++i)
        insert();
    rt=merge(0);
}

int sz[maxn];
LL dp[maxn][maxn];
vector<LL> first[maxn][maxc+1];


void add(LL &x,LL y)   {
    x=(x+y)%modu;
}


int dfs(int i) {
    if (i!=rt)
        dp[i][1]=val[i];
    if (!G[i].size())   return sz[i]=1;
    
    first[i][0].push_back(1);
    for (int k=0;k<G[i].size();++k)    {
        int j=G[i][k];
        sz[i]+=dfs(j);
        first[i][k+1].resize(sz[i]+1);
        for (int p=min(sz[i],m);p;--p)
            for (int q=1;q<=min(sz[j],p);++q)
                if (first[i][k].size()>p-q)
                    add(first[i][k+1][p],first[i][k][p-q]*dp[j][q]);
    }
    for (int p=0;p<first[i][G[i].size()].size();++p)
        add(dp[i][p],first[i][G[i].size()][p]);
    /*cout<<"dp["<<i<<"] ("<<mp[i]<<"):";   
    for (int j=0;j<=m;++j)
        cout<<dp[i][j]<<" ";
    cout<<endl;*/
    return sz[i];
}

void print(int k)   {
    if (!k) return;
    print(fa[k]);
    putchar(zf[k]+'a');
}

void sol(int i,int m) {
    if (mp[i]&&m==1)   {
//        cout<<"print:"<<i<<" "<<mp[i]<<" "<<fa[mp[i]]<<endl;
        print(mp[i]);
        cout<<endl;
        return ;
    } 
    for (int k=G[i].size();k;--k)   {
        int j=G[i][k-1];
        for (int p=1;p<=m;++p)
            if (dp[j][p]&&first[i][k-1].size()>m-p&&first[i][k-1][m-p])   {
                m-=p;
                sol(j,p);
                break;
            }
    }
}

void solve()    {
    dfs(rt);
    printf("%lld\n",dp[rt][m]);
    if (dp[rt][m])
        sol(rt,m);
}

int main() {
    init();
    solve();
}
