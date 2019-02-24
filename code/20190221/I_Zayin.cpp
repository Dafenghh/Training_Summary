#include<bits/stdc++.h>
#define maxn 1050
#define modu 3428977
using namespace std;
typedef long long LL;

int n,m;
int T[maxn][maxn];
int X[maxn*maxn],Y[maxn*maxn];

int a[maxn][maxn];

int U[maxn],D[maxn];
int L[maxn],R[maxn];

void init()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;++i)
        for (int j=1;j<=m;++j)
            scanf("%d",&T[i][j]),a[i][j]=0,
            X[T[i][j]]=i,Y[T[i][j]]=j;
    for (int i=1;i<=n;++i)  L[i]=m,R[i]=0;
    for (int j=1;j<=m;++j)  U[j]=n,D[j]=0;
}

int lowbit(int x)   {
    return x&(-x);
}

void change(int x,int y) {
    for (int i=x;i<=n;i+=lowbit(i))
        for (int j=y;j<=m;j+=lowbit(j))
            ++a[i][j];
}

int query(int x,int y)  {
    int ans=0;
    for (int i=x;i;i-=lowbit(i))
        for (int j=y;j;j-=lowbit(j))
            ans+=a[i][j];
    return ans;
}

void solve()
{
    LL pw=1,sum=0,ans=0;
    for (int t=1;t<=n*m;++t)
    {
        int i=X[t],j=Y[t];
        change(i,j);
        U[j]=min(U[j],i),D[j]=max(D[j],i);
        L[i]=min(L[i],j),R[i]=max(R[i],j);

        LL tmp=query(D[j],R[i])-query(D[j],L[i]-1)-query(U[j]-1,R[i])+query(U[j]-1,L[i]-1);
        sum=(sum+tmp)%modu,pw=pw*184903%modu;
        ans=(ans+sum*pw)%modu;
    }
    printf("%lld\n",ans);
}

int main()
{
    int T,icase=0;
    scanf("%d",&T);
    while (T--)
    {
        init();
        printf("Case %d: ",++icase);
        solve();
    }
    return 0;
}
