#include<bits/stdc++.h>
#define maxn 6005
#define maxl 70050
using namespace std;
typedef long long LL;

struct HP   {
    static const int w=4;
    static const LL Base=10000;
    vector<LL> A;
    HP(LL x=0) {
        A.clear();
        for (;x;x/=Base)
            A.push_back(x%Base);
    }

    HP(const char *s,int n) {
        A.clear();
        for (int i=n-1,w=1,x=0;~i;--i)    {
            x=x+(s[i]-'0')*w,w*=10;
            if (w==10000||!i)
                A.push_back(x),w=1,x=0;
        }
    }

    HP operator * (const LL& x) const   {
        HP Ans;
        for (LL i=0,g=0;;++i)   {
            if (i>=A.size()&&!g)    break;
            if (i<A.size()) g+=A[i]*x;
            Ans.A.push_back(g%Base);
            g/=Base;
        }
        return Ans;
    }
    HP operator + (const HP& x) const   {
        HP Ans;
        for (LL i=0,g=0;;++i)   {
            if (i>=A.size()&&i>=x.A.size()&&!g)    break;
            if (i<A.size()) g+=A[i];
            if (i<x.A.size())   g+=x.A[i];
            Ans.A.push_back(g%Base);
            g/=Base;
        }
        return Ans;
    }
}   ans;

ostream& operator << (ostream& os,const HP& x)   {
    os<<x.A.back();
    for (int i=x.A.size()-2;~i;--i)
        os<<setw(HP::w)<<setfill('0')<<x.A[i]<<setfill(' ');
    return os;
}

int n;

int len[maxn];
LL num[maxn],pw[maxn]={1};
char a[maxn][20];

int N,mp[maxl];
char s[maxl];

void init()
{
    scanf("%d",&n);
    for (int i=0;i<n;++i)   {
        scanf("%s",a[i]),len[i]=strlen(a[i]);
        for (int j=num[i]=0;j<len[i];++j)
            num[i]=num[i]*10+a[i][j]-'0';
    }
    for (int i=1;i<20;++i)  pw[i]=pw[i-1]*10;
}

bool vis[maxn];
int f[maxl];

void solve()
{
    ans=0;
    memset(vis,0,sizeof(vis));
    memset(mp,-1,sizeof(mp));
    for (int t=1;t<=n;++t)  {
        int mn=maxl;
        for (int i=N=0;i<n;++i)  {
            if (vis[i]) continue;
            mp[N]=i,mn=min(mn,len[i]);
            memcpy(s+N,a[i],len[i]*sizeof(char));
            N+=len[i];
        }
        s[N]='\0';
        if (t>1)    //cout<<HP(s,N)<<endl,
            ans=ans+HP(s,N);

        if (t==n)   continue;

        for (int i=0;i<=N;++i)  f[i]=0;
        for (int i=N-mn-1;~i;--i)
            if (s[i]==s[i+mn])
                f[i]=f[i+1]+1;
        
        int p=-1;
        for (int i=0;i<N;++i)   {
            if (!~mp[i]||len[mp[i]]!=mn) continue;
            // if (~p)
            //     cout<<f[p]<<" "<<p<<" "<<i<<" "<<s[p+f[p]]<<" "<<s[p+f[p]+mn]<<endl;
            if (!~p||(f[p]<i-p&&s[p+f[p]]>s[p+f[p]+mn]))
                p=i;
        }
        vis[mp[p]]=1;

        /*cout<<s<<endl;
        for (int i=0;i<N;++i)
            cout<<f[i]<<" ";
        cout<<endl;
        

        cout<<mn<<"("<<mp[p]<<"):";
        for (int i=0;i<n;++i)
            if (!vis[i])
                printf("%s ",a[i]);
        cout<<endl;*/

        for (int i=0;i<=N;++i)
            mp[i]=-1;
    }
    cout<<ans<<endl;
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
    return 0;
}
