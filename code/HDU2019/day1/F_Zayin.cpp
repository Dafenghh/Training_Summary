#include<bits/stdc++.h>
#define maxn 400050
#define maxc 26
using namespace std;
typedef long long LL;

int n,p,q;
char s[maxn];

int sz,last;
int len[maxn];
int fa[maxn];
int ch[maxn][maxc];

int newnode(int _len=0) {
    len[sz]=_len;
    fa[sz]=0;
    memset(ch[sz],0,sizeof(ch[sz]));
    return sz++;
}

void extend(int c)  {
    // cout<<"extend:"<<c<<endl;
    int k=last,leaf=newnode(len[k]+1);
    for (;~k&&!ch[k][c];k=fa[k])
        ch[k][c]=leaf;
    if (!~k)
        fa[leaf]=0;
    else    {
        int p=ch[k][c];
        if (len[p]==len[k]+1)
            fa[leaf]=p;
        else    {
            int np=newnode(len[k]+1);
            memcpy(ch[np],ch[p],sizeof(ch[p]));
            fa[np]=fa[p];
            fa[p]=fa[leaf]=np;
            for (;~k&&ch[k][c]==p;k=fa[k])
                ch[k][c]=np;
        }
    }
    last=leaf;
}

LL dp[maxn];

int main()  {
    while (~scanf("%s%d%d",s+1,&p,&q))  {
        sz=0,fa[last=newnode()]=-1;
        n=strlen(s+1);

        int j=1,k=0;
        for (int i=1;i<=n;++i)  {
            int c=s[i]-'a';
            for (;!ch[k][c]&&j<=i;)    {
                extend(s[j++]-'a');
                while (k&&len[fa[k]]>=i-j)
                    k=fa[k];
            }
            dp[i]=dp[i-1]+p;
            if (j<=i)
                dp[i]=min(dp[i],dp[j-1]+q),k=ch[k][c];
        }
        printf("%d\n",dp[n]);
    }
    return 0;
}
