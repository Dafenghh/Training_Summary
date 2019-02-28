#include<bits/stdc++.h>
#define ALL(A)  A.begin(),A.end()
using namespace std;

int x,y;
int n,r,m,k,s;
set<int> pass[2],spc[2];

int main()  {
    cin>>n>>r>>m>>k>>s;

    while (r--) {
        scanf("%d%d",&x,&y);
        pass[y].insert(x);
    }

    spc[0].insert(s);
    spc[0].insert(1),spc[0].insert(n);
    spc[1].insert(1),spc[1].insert(n);
    while (m--) {
        scanf("%d",&x);
        spc[0].insert(x);
        spc[1].insert(x);
    }


    int L=s,R=s;
    set<int>::iterator it;
    for (int i=0;i<=1;++i)  {
        if (!pass[i].size())   continue;
        it=upper_bound(ALL(spc[i]),*pass[i].begin());
        L=min(L,*(--it));
        it=lower_bound(ALL(spc[i]),*pass[i].rbegin());
        R=max(R,*it);
    }
    int ans=(R-L)<<1;
    if (pass[1].size()) ans+=k<<1;
    cout<<ans<<endl;
    return 0;
}
