#include<bits/stdc++.h>
#define maxc 26
#define maxn 3050
using namespace std;
typedef __int128 LL;

int N;

struct Bits
{
    static const int w=120;
    
    LL s[55];

    Bits()    {
        // memset(s,0,sizeof(s));
        for (int i=0;i<N;++i)
            s[i]=0;
    }

    void set(int p) {   s[p/w]|=(LL)1<<(p%w); };
    int count() {
        int cnt=0;
        for (int i=0;i<N;++i)
            for (int j=0;j<w;++j)
                if (s[i]>>j&1)
                    ++cnt;
        return cnt;
    }

    Bits operator - (const Bits& A) const   {
        Bits B;
        for (int i=0;i<N;++i)   B.s[i]=s[i]-A.s[i];
        for (int i=0;i+1<N;++i)
            if (B.s[i]<0)
                B.s[i]+=(LL)1<<w,--B.s[i+1];
        return B;
    }

    Bits operator | (const Bits& A) const   {
        Bits B;
        for (int i=0;i<N;++i)
            B.s[i]=s[i]|A.s[i];
        return B;
    }

    Bits operator & (const Bits& A) const   {
        Bits B;
        for (int i=0;i<N;++i)
            B.s[i]=s[i]&A.s[i];
        return B;
    }

    Bits operator ^ (const Bits& A) const   {
        Bits B;
        for (int i=0;i<N;++i)
            B.s[i]=s[i]^A.s[i];
        return B;
    }

    Bits shl()  {
        Bits B=*this;
        for (int i=0,o=1;i<N;++i)   {
            int t=B.s[i]>>(w-1)&1;
            B.s[i]=(B.s[i]<<1|o)&(~((LL)1<<w)),o=t;
        }
        return B;
    }
};

/*ostream& operator << (ostream& os,const Bits& B)    {
    for (int i=0;i<N;++i)
    {
        for (int j=0;j<Bits::w;++j)
            os<<(B.s[i]>>j&1);
        os<<" ";
    }
    return os;
}*/

int n;
char s[maxn];

void init()
{
    scanf("%s",s);
    n=strlen(s);
}

int calc(char *s,int n,char *t,int m)
{
    if (n>m)
        swap(s,t),swap(n,m);
    N=(m+Bits::w-1)/Bits::w;

    Bits cur[maxc],x;
    for (int i=0;i<m;++i)
        cur[t[i]-'a'].set(i);

    for (int i=0;i<n;++i)
    {
        Bits t=x|cur[s[i]-'a'];
        x=t&((t-x.shl())^t);
    }
    return x.count();
}

int dp[maxn][maxn],prt[maxn][maxn];

const int d[3][2]={{-1,-1},{0,-1},{-1,0}};

int len;
char str[maxn];

void print(const char* s,int n,const char* t,int m)
{
    // cout<<"print:"<<n<<" "<<m<<endl;
    // memset(dp,0,sizeof(dp));
    for (int i=0;i<=m;++i)  dp[0][i]=0;
    for (int i=0;i<=n;++i)  dp[i][0]=0;
    for (int i=1;i<=n;++i)
        for (int j=1;j<=m;++j)
            if (s[i]==t[j])
                dp[i][j]=dp[i-1][j-1]+1,prt[i][j]=0;
            else
            {
                if (dp[i][j-1]>dp[i-1][j])
                    dp[i][j]=dp[i][j-1],prt[i][j]=1;
                else
                    dp[i][j]=dp[i-1][j],prt[i][j]=2;
            }
    
    len=0;
    int x=n,y=m;
    while (x&&y)
    {
        int t=prt[x][y];
        if (dp[x][y]!=dp[x+d[t][0]][y+d[t][1]])
            str[++len]=s[x];
        x+=d[t][0],y+=d[t][1];
    }
    for (int i=len;i;--i)   putchar(str[i]);
    for (int i=len;i;--i)   putchar(str[i]);
    puts("");
}

void solve()
{
    int ans=0,pos=-1;
    for (int p=n/2;p;--p)
    {
        if (p*2<=ans)  continue;
        int t=calc(s,p,s+p,n-p)<<1;
        // cout<<p<<" "<<t<<endl;
        if (ans>t)  continue;
        ans=t,pos=p;
    }
    for (int p=n/2+1;p<n;++p)
    {
        if ((n-p)*2<=ans)  continue;
        int t=calc(s,p,s+p,n-p)<<1;
        // cout<<p<<" "<<t<<endl;
        if (ans>t)  continue;
        ans=t,pos=p;
    }
    printf("%d\n",ans);
    if (!ans)   return ;
    print(s-1,pos,s+pos-1,n-pos);
}

int main()
{
    int T,icase=0;
    scanf("%d",&T);
    while (T--)
    {
        init();
        printf("Case #%d: ",++icase);
        solve();
    }
    // cout<<clock()<<endl;
    return 0;
}
