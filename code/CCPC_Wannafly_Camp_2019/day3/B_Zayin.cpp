#include<bits/stdc++.h>
#define eps 1e-9
using namespace std;

int sgn(double x)   {
    if (x>eps)  return 1; else if (x<-eps)  return -1; return 0;
}
struct point    {
    double x,y;
    point(double _x=0,double _y=0)  {
        x=_x,y=_y;
    }
    void read() {   scanf("%lf%lf",&x,&y);  }
    double len()    {   return sqrt(x*x+y*y);   }
    point operator - (const point& P) const {   return point(x-P.x,y-P.y);  }
    point operator + (const point& P) const {   return point(x+P.x,y+P.y);  }
    point operator * (const double& l) const    {   return point(x*l,y*l);  }
    double operator * (const point& P) const    {   return x*P.x+y*P.y; }
    double operator ^ (const point& P) const    {   return x*P.y-y*P.x; }
    point unit()    {   double l=len(); return point(x/l,y/l);  }
    point trunc(double l)   {   return unit()*l;    }
} s,t,o;
double R;
ostream& operator << (ostream& os,const point& P)   {
    os<<"("<<P.x<<","<<P.y<<")";
    return os;
}
double deal(double x)   {   return max(-1.0,min(1.0,x));    }
double angle(point p,point q)   {   return acos(deal(p*q/p.len()/q.len())); }

int main()  {
    int T;
    scanf("%d",&T);
    while (T--) {
        s.read(),t.read(),o.read(),scanf("%lf",&R);
        s=s-o,t=t-o;
        point v=s-t;
        double a=v*v,b=t*v*2,c=t*t-R*R;
        double d=b*b-4*a*c;
        if (sgn(d)>0&&sgn(2*a+sqrt(d)+b)>0&&sgn(-b+sqrt(d))>0)    {
            double as=acos(R/s.len()),at=acos(R/t.len()),a=angle(s,t)-as-at;
            printf("%.3lf\n",a*R+R*tan(as)+R*tan(at));
        } else  {
            double l=0,r=1,ans=1e9;
            for (int c=0;c<100;++c) {
                double mid=(l+r)/2;
                point p=(t+v*mid).trunc(R);
                ans=min(ans,(s-p).len()+(t-p).len());
                if (sgn(angle(s-p,p)-angle(t-p,p))>0)
                    l=mid;
                else
                    r=mid;
            }
            printf("%.3lf\n",ans);
        }
    }
    return 0;
}
