#include<bits/stdc++.h>
#define rep(i,l,r) for (int i=l;i<=r;i++)
using namespace std;
typedef long long ll;
const int maxn=1000500;
vector<int> vec;
int n,m;
int suf[maxn],a[maxn],pre[maxn],nxt[maxn],last[maxn];
void gg(){
    puts("no"); exit(0);
}
void del(int x,int y){
    suf[pre[x]]=suf[y];
    pre[suf[y]]=pre[x];
}
int get(){
    int x=vec.back();
    vec.pop_back();
    return x;
}
void dfs(int l,int r){
//    if ((r-l)&1) gg();
    for (int i=l;i<=r;i=suf[i]){
        while (nxt[i]){
//            if (nxt[i]>r) gg();
            dfs(suf[i],pre[nxt[i]]);
            del(suf[i],nxt[i]);
            nxt[i]=nxt[nxt[i]];
        }
    }
    int cnt=0,sum=0,rt=a[pre[l]];
    for (int i=l;i<=r;i=suf[i]) {
        sum++;
        if (a[i]) cnt++;
    }
    sum=(sum+1)/2;
//    if (cnt>sum) gg();
    for (int i=suf[l];i<=r;i=suf[i]) if (cnt<sum&&!a[i]) a[i]=get(),cnt++;
    if (sum==1&&cnt==0) a[l]=get();
    for (int i=l;suf[i]<=r;i=suf[i]){
        while (i>l&&suf[i]<=r&&!a[pre[i]]&&a[i]&&a[suf[i]]){
            a[pre[i]]=a[suf[i]];
            del(i,suf[i]);
            i=pre[pre[i]];
        }
        while (i>=l&&suf[suf[i]]<=r&&a[i]&&a[suf[i]]&&!a[suf[suf[i]]]){
            a[suf[suf[i]]]=a[i];
            del(suf[i],suf[suf[i]]);
            i=pre[i];
        }
    }
    for (int i=l;i<=r;i=suf[i]) if (!a[i]) a[i]=rt;
}
int read(){
    int x=0,f=1; char ch=getchar();
    while (!isdigit(ch)) {if (ch=='-') f=-1; ch=getchar();}
    while (isdigit(ch)) {x=x*10+ch-'0'; ch=getchar();}
    return x*f;
}
int main(){
    int tt=read();
    while(tt--){
        vec.clear();
        n=read();
        m=2*n-1;
        rep(i,1,m) {
            a[i]=read();
            if (a[i]==-1) a[i]=0;
        }
//        if (a[1]&&a[m]&&a[1]!=a[m]) gg();
        a[1]=a[m]=1;
        rep(i,0,m) pre[i]=i-1,suf[i]=i+1,last[i]=nxt[i]=0;
        for (int i=m;i>=1;i--) if (a[i]){
            nxt[i]=last[a[i]],last[a[i]]=i;
        }
        rep(i,1,n) if (!last[i]) vec.push_back(i);
        dfs(1,m);
        rep(i,1,m-1) printf("%d ",a[i]);
        printf("%d\n",a[m]);
    }
    return 0;
}
