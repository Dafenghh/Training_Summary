#include<bits/stdc++.h>
using namespace std;
const int maxn=100500;
int n,m,rt;
struct node{
    int x,mx,lc,rc,sz,key;
}t[maxn];
void up(int i){
    if (!i) return;
    int lc=t[i].lc,rc=t[i].rc;
    t[i].sz=t[lc].sz+t[rc].sz+1;
    t[i].mx=max(t[i].x,max(t[lc].mx,t[rc].mx));
}
int merge(int x,int y){
    if (!x||!y) return x+y;
    if (t[x].key>t[y].key) {
        t[x].rc=merge(t[x].rc,y);
        up(x);
        return x;
    }
    else {
        t[y].lc=merge(x,t[y].lc);
        up(y);
        return y;
    }
}
void split(int rt,int k,int &x,int &y){
    if (!rt) {x=y=0; return;}
    if (t[t[rt].lc].sz+1<=k){
        x=rt;
        split(t[rt].rc,k-t[t[rt].lc].sz-1,t[rt].rc,y);
    }
    else {
        y=rt;
        split(t[rt].lc,k,x,t[rt].lc);
    }
    up(x); up(y);
}
int get(int rt,int k){
    if (t[t[rt].lc].sz>=k) return get(t[rt].lc,k);
    if (t[t[rt].lc].sz+1==k) return t[rt].x;
    return get(t[rt].rc,k-t[t[rt].lc].sz-1);
}
int getlen(int rt,int x){
    if (!rt) return 0;
    if (t[t[rt].lc].mx>x) return getlen(t[rt].lc,x);
    if (t[rt].x>x) return t[t[rt].lc].sz;
    return getlen(t[rt].rc,x)+t[t[rt].lc].sz+1;
}
void solve(int &rt,int m){
    int t1,t2,tmp;
    split(rt,m,t1,t2);
    rt=0;
    while (t1&&t2){
        int x1=get(t1,1),x2=get(t2,1);
        if (x1>x2) swap(x1,x2),swap(t1,t2);
        int len=getlen(t1,x2);
        split(t1,len,tmp,t1);
        rt=merge(rt,tmp);
    }
    rt=merge(rt,t1);
    rt=merge(rt,t2);
}
char pool[1<<15],*head=pool,*tail=pool;
#define getc() (head==tail&&(tail=(head=pool)+fread(pool,1,maxn,stdin),head==tail)?0:*head++)
#define isd(c) (c>='0'&&c<='9')
int read(){
    int x=0; char ch=getc();
    while (!isd(ch)) ch=getc();
    while (isd(ch)) {x=x*10+ch-'0'; ch=getc();}
    return x;
}
int main(){
    srand(time(0));
    n=read(),m=read();
    for (int i=1;i<=n;i++){
        t[i].mx=t[i].x=read();
        t[i].key=rand();
        t[i].sz=1;
        rt=merge(rt,i);
    }
    for (int i=1;i<=m;i++){
        int op=read();
        if (op==1){
            int l=read(),m=read(),r=read();
            int t1,t2;
            split(rt,r,t1,t2);
            solve(t1,m);
            rt=merge(t1,t2);
        }
        else {
            int x=read();
            printf("%d\n",get(rt,x));
        }
    }
    return 0;
}

