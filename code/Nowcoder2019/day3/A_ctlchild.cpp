#include<bits/stdc++.h>
#define rep(i,l,r) for (int i=l;i<=r;i++)
typedef long long ll;
using namespace std;
const int maxn=200500;
struct node{int x,y;}e[maxn];
int n,m,block,q,szblock;
ll val[maxn];
int d[maxn],segflag[maxn];
int pos[100005][450];
ll segB[450][1000],ptB[maxn];
char ch,B[1<<15],*S=B,*T=B;
#define getc() (S==T&&(T=(S=B)+fread(B,1,1<<15,stdin),S==T)?0:*S++)
#define isd(c) (c>='0'&&c<='9')
int read(){
    int x=0; char ch=getc();
    while (!isd(ch)) ch=getc();
    while (isd(ch)) {x=x*10+ch-'0'; ch=getc();}
    return x;
}
ll getrand(){
    static uniform_int_distribution<ll> u(1,1e18);
    static default_random_engine e(rand());
    return u(e);
}
void getpos(){
    int tot=0;
    rep(i,1,m){
        if (i==1||i/block!=(i-1)/block) tot=0;
        int id=i/block;
        if (!pos[e[i].x][id]) pos[e[i].x][id]=++tot;
        if (!pos[e[i].y][id]) pos[e[i].y][id]=++tot;
    }
}
ll getres(int x){
    ll res=ptB[x];
    rep(i,0,szblock) if (pos[x][i]){
        if (segflag[i]) res^=segB[i][pos[x][i]];
    }
    return res;
}
void pre(){
    rep(i,0,szblock) rep(j,0,2*block) segB[i][j]=0;
    rep(i,1,n) rep(j,0,szblock) pos[i][j]=0;
    rep(i,1,n) ptB[i]=0;
}
int main(){
//    freopen("in.txt","r",stdin);
//    freopen("1.txt","w",stdout);
    int tt=read();
    while (tt--){
        n=read(); m=read();
        rep(i,1,n) val[i]=getrand();
        block=sqrt(m)+1; szblock=m/block;
        pre();
        rep(i,1,m) e[i].x=read(),e[i].y=read();
        getpos();
        rep(i,1,m){
            int x=e[i].x,y=e[i].y,id=i/block;
            segB[id][pos[x][id]]^=val[y];
            segB[id][pos[y][id]]^=val[x];
        }
        rep(i,0,szblock) segflag[i]=1;
        int q=read();
        rep(qi,1,q){
            int op=read(),x=read(),y=read();
            if (op==1){
                int lid=x/block,rid=y/block;
                rep(id,lid+1,rid-1) segflag[id]^=1;
                if (lid==rid){
                    rep(i,x,y) {
                        ptB[e[i].x]^=val[e[i].y];
                        ptB[e[i].y]^=val[e[i].x];
                    }
                }
                else {
                    rep(i,x,(lid+1)*block-1) {
                        ptB[e[i].x]^=val[e[i].y];
                        ptB[e[i].y]^=val[e[i].x];
                    }
                    rep(i,rid*block,y){
                        ptB[e[i].x]^=val[e[i].y];
                        ptB[e[i].y]^=val[e[i].x];
                    }
                }
            }
            else {
                ll resx=getres(x);
                ll resy=getres(y);
                if (resx==resy) putchar('1');
                else putchar('0');
            }
        }
        puts("");
    }
    return 0;
}
