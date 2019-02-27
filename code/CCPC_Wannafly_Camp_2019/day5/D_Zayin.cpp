#include<bits/stdc++.h>
#define maxn 10
#define dis(A)  (A[1]-A[0]-1)
#define in(A,p) (A[0]<p&&p<A[1])
using namespace std;

int n;
int rsum[maxn],csum[maxn];

vector<int> rp[maxn],cp[maxn];

int okdis[maxn*maxn];
int ok[maxn][maxn*maxn][1<<maxn];

int *okr[maxn],*okc[maxn];

int cr[maxn],cc[maxn];
int sr[maxn],sc[maxn];

int low[1<<maxn];
int vr[maxn],vc[maxn];

int mp[maxn][maxn];
const char *num="X123456789";

void init()
{
    scanf("%d",&n);
    for (int i=1;i<=n;++i)  scanf("%d",rsum+i);
    for (int i=1;i<=n;++i)  scanf("%d",csum+i);
}

void predo()    {
    memset(ok,0,sizeof(ok));
    memset(okdis,0,sizeof(okdis));
    for (int s=0;s<(1<<n);++s)  {
        int cnt=0,sum=0;
        for (int i=0;i<n;++i)
            if (s>>i&1)
                ++cnt,sum+=i+1;
        // cout<<cnt<<" "<<sum<<" "<<s<<endl;
        okdis[sum]|=1<<cnt;
        ok[cnt][sum][0]=1;
        for (int t=s;t;t=(t-1)&s)
            // cout<<"ok:"<<cnt<<" "<<sum<<" "<<t<<endl,
            ok[cnt][sum][t]=1;
    }
}

bool judge(int i,int j,int c)   {
    bool fr=!in(rp[i],j)||ok[cr[i]][rsum[i]][sr[i]|(1<<c)];
    bool fc=!in(cp[j],i)||ok[cc[j]][csum[j]][sc[j]|(1<<c)];
    // cout<<"judge:"<<i<<" "<<j<<" "<<fr<<"("<<cr[i]<<" "<<rsum[i]<<" "<<sr[i]<<" "<<(sr[i]|(1<<c))<<") "<<fc<<endl;
    return fr&&fc;
}

bool change(int i,int j,int c)  {
    vr[i]^=1<<c,vc[j]^=1<<c;
    if (in(rp[i],j)) sr[i]^=1<<c;
    if (in(cp[j],i)) sc[j]^=1<<c;
}

bool dfs2(int i,int j) {
    // cout<<"dfs2:"<<i<<"("<<vr[i]<<") "<<j<<"("<<vc[j]<<")"<<endl;
    if (i>n)    return 1;
    if (j>n)    return dfs2(i+1,1);
    if (!mp[i][j])  return dfs2(i,j+1);
    
    for (int s=vr[i]&vc[j];s;s^=s&(-s))   {
        int c=low[s&(-s)];
        // cout<<"pre:"<<i<<" "<<j<<" "<<c<<endl;
        if (!judge(i,j,c))  continue;
        change(i,j,c);
        mp[i][j]=c+1;
        // cout<<"add:"<<i<<" "<<j<<" "<<c+1<<endl;
        if (dfs2(i,j+1))    return 1;
        mp[i][j]=-1;
        change(i,j,c);
    }
    // cout<<"end_dfs2:"<<i<<" "<<j<<endl;
    return 0;
}

int cnt=0;

bool fill() {
    for (int i=1;i<=n;++i)  okr[i]=ok[cr[i]=dis(rp[i])][rsum[i]];
    for (int i=1;i<=n;++i)  okc[i]=ok[cc[i]=dis(cp[i])][csum[i]];
    ++cnt;
    if (!dfs2(1,1)) return 0;
    for (int i=1;i<=n;++i)  {
        for (int j=1;j<=n;++j)
            printf("%c",num[mp[i][j]]);
        puts("");
    }

    return 1;
}

bool dfs1(int s) {
    if (s>n)    {
        return fill();
    } else
    {
        for (int i=1;i<=n;++i)
            if (cp[i].size()<2) {
                if (cp[i].size()==1&&!(okdis[csum[i]]>>(s-cp[i].back()-1)&1)) continue;

                mp[s][i]=0;
                cp[i].push_back(s),rp[s].push_back(i);
                for (int j=i+1;j<=n;++j)
                    if (cp[j].size()<2&&(okdis[rsum[s]]>>(j-i-1)&1)) {
                        if (cp[j].size()==1&&!(okdis[csum[j]]>>(s-cp[j].back()-1)&1))    continue;

                        mp[s][j]=0;
                        cp[j].push_back(s),rp[s].push_back(j);

                        if (dfs1(s+1))  return 1;

                        cp[j].pop_back(),rp[s].pop_back();
                        mp[s][j]=-1;
                    }
                cp[i].pop_back(),rp[s].pop_back();
                mp[s][i]=-1;
            }
        return 0;
    }
}

void solve()
{
    memset(mp,-1,sizeof(mp));
    predo();
    for (int i=0;i<n;++i)   low[1<<i]=i;

    for (int i=1;i<=n;++i)  sr[i]=sc[i]=0;
    for (int i=1;i<=n;++i)  vr[i]=vc[i]=(1<<(n-2))-1;
    for (int i=1;i<=n;++i)  rp[i].clear(),cp[i].clear();
    dfs1(1);
    puts("");
    // cout<<cnt<<endl;
}

int main()
{
    int T;
    scanf("%d",&T);
    while (T--)
    {
        init();
        solve();
    }
    return 0;
}
