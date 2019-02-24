#include<bits/stdc++.h>
#define maxn 1000050
#define maxm 2000050
#define maxk 16
#define maxs (1<<maxk)
using namespace std;
typedef long long LL;

int m,n,K,status;

int pos[maxn];
char s[maxn];

int col[maxn],col_cnt[maxn];

int last[maxk],mn[maxk];

void init()
{
    scanf("%d%d%d",&n,&m,&K);
    status=1<<K;

    for (int c=0;c<K;++c)
        col_cnt[c]=0;
    for (int k=1;k<=m;++k)
    {
        scanf("%s",s+pos[k]);
        pos[k+1]=pos[k]+strlen(s+pos[k]);

        for (int i=pos[k];i<pos[k+1];++i)
            ++col_cnt[col[i]=s[i]-'a'];
    }
}

int dis[maxk][maxn];
int dis_col[maxk][maxk];

int D,C;

void spfa()
{
    memset(dis_col,0x3f,sizeof(dis_col));
    for (int i=0;i<n;++i)
        for (int c=0;c<K;++c)
            dis[c][i]=K<<1;

    for (int k=1;k<=m;++k)
    {
        for (int c=0;c<K;++c)   last[c]=-1;
        for (int i=pos[k];i<pos[k+1];++i)
        {
            last[col[i]]=i;
            for (int c=0;c<K;++c)
                if (~last[c])
                {
                    int j=last[c],a=col[i];
                    dis_col[c][a]=min(dis_col[c][a],i-j),dis[c][i]=min(dis[c][i],i-j);
                    dis_col[a][c]=min(dis_col[a][c],i-j),dis[a][j]=min(dis[a][j],i-j);
                }
        }
    }

    for (int k=0;k<K;++k)
        for (int i=0;i<K;++i)
            for (int j=0;j<K;++j)
                dis_col[i][j]=min(dis_col[i][j],dis_col[i][k]+dis_col[k][j]+1);
    
    for (int k=1;k<=m;++k)
    {
        for (int c=0;c<K;++c)   mn[c]=maxn;
        for (int i=pos[k];i<pos[k+1];++i)
        {
            for (int c=0;c<K;++c)
                mn[c]=min(mn[c],dis_col[col[i]][c]+1-i);
            for (int c=0;c<K;++c) dis[c][i]=min(dis[c][i],i+mn[c]);
        }
        for (int c=0;c<K;++c)   mn[c]=maxn;
        for (int i=pos[k+1]-1;i>=pos[k];--i)
        {
            for (int c=0;c<K;++c)
                mn[c]=min(mn[c],dis_col[col[i]][c]+1+i);
            for (int c=0;c<K;++c) dis[c][i]=min(dis[c][i],mn[c]-i);
        }
    }
}

int sta[maxn];
int cnt[maxk][maxs],sum[maxk][maxs];

int sp[maxk][maxk][2];

void predo()
{
    spfa();

    for (int c=0;c<K;++c)
        for (int s=0;s<status;++s)
            cnt[c][s]=sum[c][s]=0;

    for (int a=0;a<K;++a)
        for (int b=0;b<K;++b)
            for (int j=0;j<=1;++j)
            {
                sp[a][b][j]=0;
                for (int c=0;c<K;++c)
                    if (dis_col[a][c]+1+dis_col[c][b]==dis_col[a][b]+j)
                        sp[a][b][j]|=1<<c;
            }

    for (int i=0;i<n;++i)
    {
        sta[i]=0;
        for (int c=0;c<K;++c)
            sta[i]|=(dis[c][i]-dis_col[c][col[i]])<<c;
        ++cnt[col[i]][sta[i]],++sum[col[i]][sta[i]];
    }
    //&
    for (int c=0;c<K;++c)
        for (int i=0;i<K;++i)
            for (int s=0;s<status;++s)
                if (s>>i&1)
                    sum[c][s^(1<<i)]+=sum[c][s];
}

LL solve()
{
    LL ans=0;
    for (int a=0;a<K;++a)
    {
        ans+=(LL)col_cnt[a]*(col_cnt[a]-1)/2;
        for (int b=0;b<a;++b)
        {
            LL res=(LL)col_cnt[a]*col_cnt[b]*dis_col[a][b];
            for (int s=0;s<status;++s)
            {
                if (!cnt[a][s]) continue;
                int t=(~s&sp[a][b][0]);
                if (t)
                    res+=(LL)cnt[a][s]*sum[b][t];
                else
                {
                    if (s>>b&1)
                    {
                        t=(~s&sp[a][b][1]);
                        res+=(LL)cnt[a][s]*(col_cnt[b]+sum[b][t]);
                    }
                    else
                        res+=(LL)cnt[a][s]*col_cnt[b];
                }
            }
            ans+=res;
        }
    }

    for (int k=1;k<=m;++k)
    {
        memset(last,-1,sizeof(last));
        for (int i=pos[k];i<pos[k+1];++i)
        {
            for (int c=0;c<K;++c)
            {
                if (!~last[c]||c==col[i])  continue;
                int j=last[c],a=col[i],b=col[j],d;

                if (~sta[i]&~sta[j]&sp[b][a][0]) continue;
                if (~sta[i]&~sta[j]&sp[b][a][1])
                    d=dis_col[a][b]+1;
                else
                    d=dis_col[a][b]+2;

                if (d>i-j)
                    ans+=(i-j)-d;
            }
            last[col[i]]=i;
        }
    }
    return ans;
}

int main()
{
    int T,icase=0;
    scanf("%d",&T);
    while (T--)
    {
        init();
        predo();
        printf("Case #%d: %lld\n",++icase,solve());
    }
    return 0;
}
