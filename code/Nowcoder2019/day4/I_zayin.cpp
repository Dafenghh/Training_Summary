#include<bits/stdc++.h>
#define maxn 800050
#define maxc 26
using namespace std;
typedef long long LL;
 
int n;
char s[maxn];
 
namespace SAM   {
    int sz,last;
    int len[maxn];
    int fa[maxn];
    int ch[maxn][maxc];
 
    int newnode(int _len=0) {
        len[sz]=_len;
        return sz++;
    }
 
    void extend(int c)  {
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
 
    void travel(int k,string s) {
        cout<<k<<":"<<s<<endl;
        for (int c=0;c<maxc;++c)
            if (ch[k][c])
                travel(ch[k][c],s+(char)(c+'a'));
    }
 
    void buildsam() {
        fa[last=newnode()]=-1;
        for (int i=1;i<=n;++i)
            extend(s[i]-'a');
        last=0;
        for (int i=n;i;--i) {
            int c=s[i]-'a';
            if (ch[last][c]&&len[ch[last][c]]==len[last]+1)
                last=ch[last][c];
            else
                extend(c);
        }
        // travel(0,"");
    }
};
 
namespace PAM   {
    int all,son[maxn][maxc],fail[maxn],len[maxn],text[maxn],last,tot;
    int newnode(int l) {
        len[tot]=l;
        return tot++;
    }
    int getfail(int x)  {
        while (text[all-len[x]-1]!=text[all])   x=fail[x];
        return x;
    }
    void add(int w) {
        text[++all]=w;
        int x=getfail(last);
        if (!son[x][w]) {
            int y=newnode(len[x]+2);
            fail[y]=son[getfail(fail[x])][w];
            son[x][w]=y;
        }
        last=son[x][w];
    }
    void buildpam() {
        last=tot=all=0;
        newnode(0),newnode(-1);
        text[0]=-1,fail[0]=1;
        for (int i=1;i<=n;++i)
            add(s[i]-'a');
    }
};
 
int main()  {
    scanf("%s",s+1),n=strlen(s+1);
    SAM::buildsam();
    PAM::buildpam();
    LL ans=PAM::tot-2;
    // cout<<"Pam:"<<ans<<endl;
    for (int i=1;i<SAM::sz;++i)
        ans+=SAM::len[i]-SAM::len[SAM::fa[i]];
    printf("%lld\n",ans>>1);
    return 0;
}
