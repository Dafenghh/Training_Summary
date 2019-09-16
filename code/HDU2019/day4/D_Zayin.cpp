#include<bits/stdc++.h>
#define maxn 300050
using namespace std;

const double eps=1e-10;
inline int sgn(double x)   {
    if (x>eps)  return 1;
    if (x<-eps) return -1;
    return 0;
}

int n,m;
struct node {
    double x,y;
    node(double _x=0,double _y=0)   {
        x=_x,y=_y;
    }
    node operator + (const node& N) const   {
        return node(x+N.x,y+N.y);
    }
    node operator - (const node& N) const   {
        return node(x-N.x,y-N.y);
    }
    node operator * (const double& l)   const   {
        return node(x*l,y*l);
    }
    node operator / (const double& l)   const   {
        return node(x/l,y/l);
    }
    double operator * (const node& N)   const   {
        return x*N.y-y*N.x;
    }
    double len2()    {
        return x*x+y*y;
    }
    double angle()  {
        return atan2(y,x);
    }
    bool operator < (const node& N) const   {
        return x<N.x||(x==N.x&&y<N.y);
    }
} P[maxn],Q[maxn],tmp[maxn]; 
ostream& operator << (ostream& os,const node& N)    {
    os<<"("<<N.x<<","<<N.y<<")";
    return os;
}

struct line {
    node p,q;
    double a;
    line(node _p=0,node _q=0) { p=_p,q=_q,a=(q-p).angle();    }
    bool onleft(const node& v)  const  {  return sgn((q-p)*(v-p))>0;    }
    bool operator < (const line& L) const   {   return a<L.a||(!sgn(a-L.a)&&L.onleft(p));    }
} L[maxn];
ostream& operator << (ostream& os,const line& L)    {
    os<<L.p<<" -> "<<L.q;
    return os;
}

int pos[maxn];
double ag[maxn];

void Convex(node P[],int& n)   {
    for (int i=0;i<n;++i)   
        if (P[i]<*P)
            swap(P[i],*P);
    for (int i=1;i<n;++i)   
        pos[i]=i,ag[i]=(P[i]-*P).angle();
    sort(pos+1,pos+n,[&](const int& i,const int& j){
        return sgn(ag[i]-ag[j])<0||(!sgn(ag[i]-ag[j])&&sgn((P[j]-*P).len2()-(P[i]-*P).len2())>0);
    });
    for (int i=1;i<n;++i)   tmp[i]=P[i];
    int m=1;
    for (int i=1;i<n;++i)   {
        node p=tmp[pos[i]];
        while (m>1&&sgn((p-P[m-2])*(P[m-1]-P[m-2]))>=0) --m;
        P[m++]=p;
    }
    n=m;
}

double ans;
int g[maxn];

int l,r;
line q[maxn];


node line_inter(const line& l1,const line& l2) {
    double a=(l1.q-l1.p)*(l2.p-l1.p);
    double b=(l1.q-l1.p)*(l1.p-l2.q);
    return (l2.p*b+l2.q*a)/(a+b);
}

bool halfplane()    {
    sort(L,L+n);
    q[l=r=1]=*L;
    for (int i=1;i<n;++i)   {
        if (!sgn(L[i-1].a-L[i].a))  continue;
        while (l<r&&!L[i].onleft(line_inter(q[r],q[r-1]))) --r;
        while (l<r&&!L[i].onleft(line_inter(q[l],q[l+1]))) ++l;
        q[++r]=L[i];
    }
    while (l<r&&!q[l].onleft(line_inter(q[r],q[r-1]))) --r;
    while (l<r&&!q[r].onleft(line_inter(q[l],q[l+1]))) ++l;
    if (r-l<=1) return 0;
    return 1;
}

node p[maxn];

bool judge(double mid)  {
    for (int i=0;i<n;++i)   
        L[i]=line(P[i]*mid-Q[g[i]],P[(i+1)%n]*mid-Q[g[i]]);
    return halfplane();
}

void solve()    {
    for (int i=0,j=0;i<n;++i)   {
        node u=P[(i+1)%n]-P[i];
        while (1)   {
            node p=Q[(j+1)%m]-Q[j],q=Q[(j+m-1)%m]-Q[j];
            if (u*p>=0&&u*q>=0) break;
            j=(j+1)%m;
        }
        g[i]=j;
    }
    double l=0,r=1e9;
    for (int t=0;t<60;++t)  {
        double mid=(l+r)/2;
        if (judge(mid))
            r=mid;
        else
            l=mid;
    }
    ans=min(ans,l);
}

int main()  {
    int T;
    scanf("%d",&T);
    while (T--) {
        scanf("%d",&n);
        for (int i=0;i<n;++i)
            scanf("%lf%lf",&P[i].x,&P[i].y);
        Convex(P,n);
        scanf("%d",&m);
        for (int i=0;i<m;++i)
            scanf("%lf%lf",&Q[i].x,&Q[i].y);
        Convex(Q,m);
        if (m==1)
            puts("0.000000");
        else    {
            ans=1e9;
            solve();
            for (int i=0;i<n;++i)
                P[i]=P[i]*-1.0;
            solve();
            printf("%.5lf\n",ans);
        }
    }
    return 0;
}
