#include<bits/stdc++.h>
#define maxn 100050
using namespace std;
typedef long long LL;

int S;

int n,T;
int a[maxn],b[maxn],p[maxn];

vector<int> G[maxn];
int tb[maxn],g[maxn],sgn[maxn];

LL tag[maxn],sum[maxn];

const int sz=67108864;
char inbuf[sz],*pl=inbuf,*pr=inbuf;
inline char Getc()  {
    if (pl==pr)
        pr=(pl=inbuf)+fread(inbuf,1,sz,stdin);
    return pl==pr?-1:*pl++;
}
int read()  {
    int x=0;
    char c=Getc();
    while ((c<'0'||c>'9')&&~c)    c=Getc();
    if (!~c)    return -1;
    while ('0'<=c&&c<='9')  x=(x<<3)+(x<<1)+c-'0',c=Getc();
    return x;
}

inline void add(int &a,const int &b,const int& p)	{
	a+=b;
	if (a>=p)	a-=p;
}

int main()	{
	while (~scanf("%d%d",&n,&T))	{
		for (int i=1;i<=n;++i)	scanf("%d",a+i);
		for (int i=1;i<=n;++i)	scanf("%d",b+i);
		for (int i=1;i<=n;++i)	scanf("%d",p+i);
		
		S=0.7*sqrt(n)+5;
		for (int i=0;i<=S;++i)	G[i].clear();
		for (int i=0;i<=T;++i)	sum[i]=0;
		
		for (int i=1;i<=n;++i)	{
			int t=0;
			tb[i]=p[i];
			for (int j=1;j<=S;++j)	{
				add(t,b[i],p[i]);
				if (tb[i]>t)
					tb[i]=t,sgn[i]=1,g[i]=j;
				if (tb[i]>p[i]-t)
					tb[i]=p[i]-t,sgn[i]=-1,g[i]=j;
			}
			G[g[i]].push_back(i);
		}
		
		for (int s=1;s<=S;++s)	{
			if (!G[s].size())	continue;
			for (int t=0;t<=T;++t)	tag[t]=0;
			LL sumb=0;
			for (int i:G[s])	{
				if (sgn[i]==1)	{
					sumb+=tb[i];
					for (int st=0,ta=a[i];st<s&&st<=T;++st,add(ta,b[i],p[i]))	{
						int Lim=(T-st)/s;
						tag[st]+=ta;
						if (!tb[i])	continue;
                        for (LL kp=p[i]-ta-1;;kp+=p[i])   {
                            LL l=kp/tb[i]+1;
                            if (l>Lim)  break;
                            tag[st+l*s]-=p[i];
                        }
					}
				} else	{
					sumb-=tb[i];
					for (int st=0,ta=a[i];st<s&&st<=T;++st,add(ta,b[i],p[i]))	{
						int Lim=(T-st)/s;
						tag[st]+=ta;
						if (!tb[i])	continue;
						for (LL kp=ta;;kp+=p[i])	{
							LL l=kp/tb[i]+1;
							if (l>Lim)	break;
							tag[st+l*s]+=p[i];
						}
					}
				}
			}
			for (int st=0;st<s;++st)
				for (int j=st+s;j<=T;j+=s)
					tag[j]+=tag[j-s]+sumb;
			for (int t=0;t<=T;++t)
				sum[t]+=tag[t];
		}
		int t=0;
		for (int i=0;i<=T;++i)
			if (sum[i]>sum[t])
				t=i;
		printf("%lld %d\n",sum[t],t);
	}
	return 0;
}
