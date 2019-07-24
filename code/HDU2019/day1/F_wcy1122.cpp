#include<bits/stdc++.h>
#define ll long long
#define N 400010
#define M 27
using namespace std;
int n,p,q,pos,cnt,f[N],fa[N],ch[N][M];
char s[N];ll g[N];

class SAM
{
  public:
  int build(int x,int c)
  {
    int nx=++cnt;c-='a';f[nx]=f[x]+1;
    while(x&&!ch[x][c])ch[x][c]=nx,x=fa[x];
    if(!x)fa[nx]=1;
    else
    {
      int p=ch[x][c];
      if(f[p]==f[x]+1)fa[nx]=p;
      else
      {
        int np=++cnt;f[np]=f[x]+1;
        memcpy(ch[np],ch[p],sizeof(ch[p]));
        fa[np]=fa[p];fa[nx]=fa[p]=np;
        while(x&&ch[x][c]==p)ch[x][c]=np,x=fa[x];
      }
    }
    return nx;
  }
}S;

int main()
{
  int po;
  while(~scanf(" %s",s+1))
  {
    scanf("%d%d",&p,&q);n=strlen(s+1);
	g[1]=p;cnt=1;pos=1;po=1;
    for(int i=2,j=1;i<=n;i++)
    {
      for(;j<=i;j++)
      {
	    if(ch[po][s[i]-'a'])break;
	    pos=S.build(pos,s[j]);
		while(po&&f[fa[po]]+1>=i-j)po=fa[po];
      	if(!po)po=1;
	  }
	  g[i]=g[i-1]+p;
	  if(j<=i)g[i]=min(g[i],g[j-1]+q);
	  po=ch[po][s[i]-'a'];if(!po)po=1;
	  while(po&&f[fa[po]]>=i-j+1)po=fa[po];
	  if(!po)po=1;
	}
	printf("%lld\n",g[n]);
	for(int i=1;i<=cnt;i++)
	{
	  f[i]=0;fa[i]=0;
	  memset(ch[i],0,sizeof(ch[i]));
	}
  }
  return 0;
} 
