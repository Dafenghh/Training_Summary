#include<bits/stdc++.h>
#define maxn 505
using namespace std;

int n;
double x[maxn],y[maxn];
int s1[maxn],s2[maxn];

bool occur[maxn];

int f[maxn][maxn],sum[maxn];
vector<int> to;

void init() {
    scanf("%d",&n);
    for (int i=0;i<n;++i)   scanf("%lf%lf",x+i,y+i);
    for (int i=0;i<n;++i)   scanf("%d",s1+i),--s1[i];
    for (int i=0;i<n;++i)   scanf("%d",s2+i),--s2[i];
}

double a[maxn][maxn];
double F[maxn],S[maxn];

double sq(double x) {   return x*x; }

double calc(double x[]) {
    memset(a,0,sizeof(a));
    for (int i=0;i<n;++i)   {
        a[s1[i]][s1[i]]+=4,a[s1[i]][n]+=2*x[i];
        for (int j=0;j<n;++j)   {
            double t=-2.0*f[s2[i]][j]/sum[s2[i]];
            a[s1[i]][j]+=t,a[j][s1[i]]+=t;
        }
    }
    for (int k=0;k<n;++k)   {
        if (!sum[k])    continue;
        to.clear();
        for (int i=0;i<n;++i)
            if (f[k][i])
                to.push_back(i);
        for (int i:to)
            for (int j:to)
                a[i][j]+=2.0*f[k][i]*f[k][j]/sum[k];
    }
    for (int k,i=0;i<n;++i)   {
        if (!occur[i])  continue;
        for (int j=k=i;j<n;++j)
            if (abs(a[j][i])>abs(a[k][i]))
                k=j;
        for (int j=i;j<=n;++j)
            swap(a[i][j],a[k][j]);
        for (int k=i+1;k<n;++k)
            for (int j=n;j>=i;--j)
                a[k][j]-=a[k][i]/a[i][i]*a[i][j];
    }
    for (int i=n-1;~i;--i)  {
        F[i]=a[i][n];
        if (!occur[i])  continue;
        for (int j=i+1;j<n;++j)
            F[i]-=F[j]*a[i][j];
        F[i]/=a[i][i];
    }
    for (int i=0;i<n;++i)   {
        S[i]=0;
        if (!sum[i])    continue;
        for (int j=0;j<n;++j)
            S[i]+=F[j]*f[i][j];
        S[i]/=sum[i];
    }
    double ans=0;
    for (int i=0;i<n;++i)
        ans+=sq(x[i]-F[s1[i]])+sq(F[s1[i]]-S[s2[i]]);
    return ans;
}

void solve()    {
    for (int i=0;i<n;++i)
        occur[s1[i]]=1,
        ++sum[s2[i]],++f[s2[i]][s1[i]];
    printf("%.9lf\n",calc(x)+calc(y));
}

int main()  {
    init();
    solve();
    return 0;
}
