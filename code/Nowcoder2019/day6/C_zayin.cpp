#include<bits/stdc++.h>
#define maxc 26
#define maxh 20
#define maxn 100050
using namespace std;
typedef long long LL;
 
int all,last,sz;
int text[maxn];
int son[maxn][maxc],fail[maxn],len[maxn];
 
int F[maxn][maxc];
 
char s[maxn];
 
int newnode(int l)  {
    for (int i=0;i<maxc;++i)    son[sz][i]=0;
    len[sz]=l;
    return sz++;
}
 
void init() {
    last=sz=all=0;
    newnode(0),newnode(-1);
    text[0]=-1,fail[0]=1;
}
 
int getfail(int x)  {
    while (text[all-len[x]-1]!=text[all])   x=fail[x];
    return x;
}
 
void add(int w) {
    // cout<<"add:"<<w<<endl;
    text[++all]=w;
    int x=getfail(last);
    if (!son[x][w]) {
        int y=newnode(len[x]+2);
        fail[y]=son[getfail(fail[x])][w];
        son[x][w]=y;
    }
    last=son[x][w];
}
 
void travel(int k,string s="")  {
    cout<<k<<":"<<s<<endl;
    for (int c=0;c<maxc;++c)
        if (son[k][c])  {
            string t(1,(char)(c+'a'));
            travel(son[k][c],t+s+t);
        }
}
 
int cnt=0;
int vis[maxn];
 
void ins(int k) {
    if (!vis[k])    ++cnt;
    ++vis[k];
}
 
void del(int k) {
    assert(vis[k]);
    --vis[k];
    if (!vis[k])    --cnt;
}
 
LL ans=0;
 
void dfs(int i) {
    ins(fail[i]);
    ans+=cnt;
    // cout<<i<<":"<<cnt<<endl;
    ins(i);
    for (int c=0;c<maxc;++c)
        if (son[i][c])
            dfs(son[i][c]);
    del(fail[i]);
    del(i);
}
 
int main()  {
    int T,icase=0;
    scanf("%d",&T);
    while (T--) {
        init();
        scanf("%s",s+1);
        for (int i=1;s[i];++i)
            add(s[i]-'a');
        for (int i=0;i<sz;++i)  vis[i]=0;
        vis[0]=vis[1]=1;
        ans=cnt=0;
        dfs(0);
        dfs(1);
        printf("Case #%d: %lld\n",++icase,ans);
    }
    return 0;
}
