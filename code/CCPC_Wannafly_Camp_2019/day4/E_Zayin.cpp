#include<bits/stdc++.h>
#define maxn 16
#define maxm 305
#define maxs (1<<maxn)
#define eps 1e-9
using namespace std;

const double PI=acos(-1),inf=1e9;
int sgn(double x)   {
    if (x>eps)  return 1; else if (x<-eps)  return -1;  return 0;
}

struct point    {
    double x,y;
    point(){}
    point(double _x,double _y)  {   x=_x,y=_y;  }
    void read() {   scanf("%lf%lf",&x,&y);  }
    double angle() const {   return atan2(y,x);    }
    double len() const  {   return sqrt(x*x+y*y);   }
    point operator - (const point& P)   const   {   return point(x-P.x,y-P.y); }
    point operator + (const point& P)   const   {   return point(x+P.x,y+P.y); }
    point operator * (const double& l)   const   {   return point(x*l,y*l); }
    double operator * (const point& P)  const   {   return x*P.x+y*P.y; }
    double operator ^ (const point& P)  const   {   return x*P.y-y*P.x; }
} P[maxn][maxm];

int n;
double A,B;
struct seg  {
    point p,q;
    seg(){}
    seg(point _p,point _q)  {
        p=_p,q=_q;
        if (sgn(p.angle()-q.angle())>0)
            swap(p,q);
    }
    double dis(double a)    {   
        point I(cos(a),sin(a)),v=q-p;
        return sgn(I^v)?(p^v)/(I^v):min(p.len(),q.len());
    }
    double time(double a)   {   return A*(a+PI)+B*dis(a);   }
} L[maxn][maxm];
ostream& operator << (ostream& os,const point& P)   {
    os<<"("<<P.x<<","<<P.y<<")";
    return os;
}
ostream& operator << (ostream& os,const seg& L)   {
    os<<L.p<<" -> "<<L.q;
    return os;
}

int cnt[maxn],val[maxn];

vector<double> Ag;

double T[maxm][maxn],D[maxm][maxs];
double lim,dp[maxs],f[maxs][maxn];
int low[maxs],sum[maxs];

void init() {
    scanf("%d%lf%lf",&n,&A,&B);
    for (int i=0;i<n;++i)   {
        scanf("%d%d",cnt+i,val+i);
        for (int j=0;j<cnt[i];++j)  
            P[i][j].read(),Ag.push_back(P[i][j].angle());
        for (int j=0;j<cnt[i];++j)
            L[i][j]=seg(P[i][j],P[i][(j+1)%cnt[i]]);
    }
    scanf("%lf",&lim);
    sort(Ag.begin(),Ag.end());
}

void solve()    {
    for (int i=0;i<maxm;++i)    for (int j=0;j<maxn;++j)    T[i][j]=inf;
    for (int i=0;i<maxm;++i)    for (int j=0;j<maxs;++j)    D[i][j]=inf;
    for (int i=0;i<maxs;++i)    for (int j=0;j<maxn;++j)    f[i][j]=inf;
    for (int i=1;i<maxs;++i)    dp[i]=inf;

    for (int i=0;i<n;++i)
        for (int j=0;j<cnt[i];++j)  {
            const point &p=L[i][j].p,&q=L[i][j].q;
            for (int k=0;k<Ag.size()-1;++k)
                if (sgn(Ag[k]-p.angle())>=0&&sgn(q.angle()-Ag[k+1])>=0) {
                    double l=Ag[k],r=Ag[k+1];
                    D[k][1<<i]=min(D[k][1<<i],L[i][j].dis((l+r)/2));
                    for (int c=0;c<100;++c) {
                        double m1=(l*2+r)/3,m2=(l+r*2)/3;
                        if (sgn(L[i][j].time(m1)-L[i][j].time(m2))<0)
                            r=m2;
                        else
                            l=m1;
                    }
                    T[k][i]=min(T[k][i],L[i][j].time(l));
                }
        }
    int ALL=(1<<n)-1;
    for (int i=0;i<n;++i)   low[1<<i]=i;
    for (int k=0;k<Ag.size()-1;++k) {  
        for (int s=1;s<(1<<n);++s)
            D[k][s]=min(D[k][s^(s&-s)],D[k][s&-s]);
        for (int s=1;s<(1<<n);++s)  
            for (int i=0;i<n;++i)
                if ((s>>i&1)&&sgn(D[k][1<<i]-D[k][~s&ALL])<0)
                    f[s][i]=min(f[s][i],T[k][i]);
    }

    int ans=0;
    for (int s=1;s<(1<<n);++s)  {
        sum[s]=sum[s^(s&-s)]+val[low[s&-s]];
        for (int i=0;i<n;++i)
            if (s>>i&1)
                dp[s]=min(dp[s],dp[s^1<<i]+f[s][i]);
        if (sgn(lim-dp[s])>=0)
            ans=max(ans,sum[s]);
    }
    printf("%d\n",ans);
}
int main(){
    init();
    solve();
    return 0;
}
