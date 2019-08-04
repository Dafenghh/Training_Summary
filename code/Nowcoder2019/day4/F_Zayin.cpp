#include<bits/stdc++.h>
#define maxn 100050
#define ls(k)   T[k].ls
#define rs(k)   T[k].rs
#define val(k)  T[k].val
#define rnd(k)  T[k].rnd
#define sz(k)   T[k].sz
#define mx(k)   T[k].mx
using namespace std;

struct node {
    int ls,rs;
    int val,rnd;
    int sz,mx;
} T[maxn];

int rt,sz;

int newnode(int _val)   {
    static uniform_int_distribution<int> u(0,1e9);
    static default_random_engine e(rand());
    ++sz;
    ls(sz)=rs(sz)=0;
    sz(sz)=1;
    mx(sz)=val(sz)=_val,rnd(sz)=u(e);
    return sz;
}

void update(int k)  {
    sz(k)=sz(ls(k))+sz(rs(k))+1;
    mx(k)=max({mx(ls(k)),mx(rs(k)),val(k)});
}

void spilt_mx(int k,int v,int &x,int &y)   {
    // cout<<"spilt_mx:"<<k<<"("<<ls(k)<<","<<rs(k)<<") "<<val(k)<<" "<<mx(k)<<" "<<v<<endl;
    if (mx(k)<=v)
        x=k,y=0;
    else
    if (!k)
        x=y=0;
    else    {
        if (mx(ls(k))>v)
            spilt_mx(ls(k),v,x,ls(y=k));
        else
        if (val(k)>v)
            x=ls(k),ls(y=k)=0;
        else
            spilt_mx(rs(k),v,rs(x=k),y);
        update(k);
    }
}

void spilt_sz(int k,int sz,int &x,int &y)   {
    // cout<<"spilt_sz:"<<k<<"("<<ls(k)<<","<<rs(k)<<") "<<sz<<endl;
    if (!sz)
        x=0,y=k;
    else
    if (!k)
        x=y=0;
    else    {
        if (sz(ls(k))>=sz)
            spilt_sz(ls(k),sz,x,ls(y=k));
        else
            spilt_sz(rs(k),sz-sz(ls(k))-1,rs(x=k),y);
        update(k);
    }
}

int merge(int x,int y)  {
    if (!x||!y) return x|y;
    int rt;
    if (rnd(x)<rnd(y))
        rs(rt=x)=merge(rs(x),y);
    else
        ls(rt=y)=merge(x,ls(y));
    return update(rt),rt;
}

int kth(int k,int rk)   {
    if (sz(ls(k))+1==rk)    return k;
    if (sz(ls(k))>=rk)
        return kth(ls(k),rk);
    else
        return kth(rs(k),rk-sz(ls(k))-1);
}

void print(int k)   {
    if (!k) return ;
    print(ls(k));
    printf("%d ",val(k));
    print(rs(k));
}

int n,m;

int main()  {
    srand(time(0));
    scanf("%d%d",&n,&m);
    for (int a,i=1;i<=n;++i)
        scanf("%d",&a),rt=merge(rt,newnode(a));
    // print(rt),cout<<endl;
    while (m--) {
        int op;
        scanf("%d",&op);
        if (op==1)  {
            int l,m,r;
            scanf("%d%d%d",&l,&m,&r);
            int k1=0,k2=0,k3=0;
            spilt_sz(rt,r,k2,k3);
            spilt_sz(k2,m,k1,k2);
            while (k2)  {
                int v2=val(kth(k2,1));
                if (mx(k1)<=v2) break;
                int l1=0,r1=0,l2=0,r2=0;
                spilt_mx(k1,v2,l1,r1);
                spilt_mx(k2,v2,l2,r2);
                k1=merge(l1,merge(l2,r1));
                k2=r2;
            }
            rt=merge(k1,merge(k2,k3));
        } else  {
            int i;
            scanf("%d",&i);
            printf("%d\n",val(kth(rt,i)));
        }
        // print(rt),cout<<endl;
    }
    return 0;
}
