#include<bits/stdc++.h>
#define rep(i,l,r) for (int i=l;i<=r;i++)
using namespace std;
char s[100500];
int n,ans,sz[2];
map<int ,int> mp;
int main(){
    scanf("%d",&n);
    scanf("%s",s+1);
    int now=0;
    mp[0]=0;
    rep(i,1,n){
        if (s[i]=='1') now++;
        else now--;
        if (mp.count(now)) ans=max(ans,i-mp[now]);
        else mp[now]=i;
    }
    rep(i,1,n) sz[s[i]-'0']++;
    printf("%d %d\n",ans,min(sz[0],sz[1])*2);
    return 0;
}
