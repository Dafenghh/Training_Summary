#include<bits/stdc++.h>
#define rep(i,l,r) for (int i=l;i<=r;i++)
using namespace std;
const double pi=acos(-1.0);
const double eps=1e-7;
double a[4],b[4],w,h;
int tt;
typedef complex<double> pt;
pt ans[4];
int cmp(double x){
    if (fabs(x)<eps) return 0;
    if (x>0) return 1;
    return -1;
}
inline double sqr(double x){
    return x*x;
}
int gg=0;
void out(){
    gg=1;
    int p[3]={0,1,2};
    do{
        if (cmp(fabs(ans[p[0]]-ans[p[1]])-b[0])) continue;
        if (cmp(fabs(ans[p[0]]-ans[p[2]])-b[1])) continue;
        if (cmp(fabs(ans[p[1]]-ans[p[2]])-b[2])) continue;
        rep(i,0,2) printf("%.10lf %.10lf ",ans[p[i]].real(),ans[p[i]].imag());
        puts("");
        break;
    }while (next_permutation(p,p+3));
}
bool ok(pt a){
    if (cmp(a.real())>=0&&cmp(w-a.real())>=0&&cmp(a.imag())>=0&&cmp(h-a.imag())>=0) return 1;
    return 0;
}
bool calc(){
    double alpha=acos((sqr(a[0])+sqr(a[1])-sqr(a[2]))/(2.0*a[0]*a[1]));
    double theta=0;
    if (cmp(a[0]-w)>0) theta=acos(1.0*w/a[0]);
    ans[0]=0;
    ans[1]=polar(a[0],theta);
    ans[2]=polar(a[1],alpha+theta);
    if (!ok(ans[0])) return 0;
    if (!ok(ans[1])) return 0;
    if (!ok(ans[2])) return 0;
    out();
    return 1;
}
int main(){
    scanf("%d",&tt);
    while (tt--){
        scanf("%lf%lf%lf%lf%lf",&w,&h,&b[0],&b[1],&b[2]);
        rep(i,0,2) a[i]=b[i];
        sort(a,a+3);
        do{
            if (calc()) break;
        } while (next_permutation(a,a+3));
    }
    return 0;
}
