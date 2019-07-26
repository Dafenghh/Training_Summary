#include<bits/stdc++.h>
#define ll long long
#define inf 9999999999999999ll
#define N 10010
using namespace std;
int T,n,m,K,t1,t2;
ll f[N],g1[N],g2[N],Fmin[N],Gmin[N],Hmin[N];
ll L1min[N],R1min[N],L2min[N],R2min[N],pos;
struct info{
  ll x,y,c;
  bool operator<(const info &p)const{
    if(x!=p.x)return x<p.x;
	return abs(y-pos)<abs(p.y-pos);
  }
}s[N],t[N],s1[N],s2[N];
bool cmp(const info &a,const info &b){
  return a.y<b.y;
}

int main()
{
  int x,y,c;ll tmp;
  scanf("%d",&T);
  while(T--)
  {
    scanf("%d%d%d",&n,&m,&K);
	for(int i=1;i<=K;i++)f[i]=inf,Fmin[i]=inf,Hmin[i]=inf;
	pos=m/2+1;t1=0;t2=0;
    for(int i=1;i<=K;i++)
    {
	  scanf("%d%d%d",&x,&y,&c);
	  if(x==1)s[++t1]=(info){x,y,c};
	  else t[++t2]=(info){x,y,c};
	}
	sort(s+1,s+t1+1,cmp);
	sort(t+1,t+t2+1);Hmin[0]=-1;
	for(int i=1;i<=t1;i++)
	  for(int j=i;j;j--)
	  {
	    f[j]=min(f[j],Hmin[j-1]+s[i].y+s[i].c);
	    Hmin[j]=min(Hmin[j],Hmin[j-1]+s[i].c);
	    Fmin[j]=min(Fmin[j],Hmin[j-1]+s[i].c+s[i].y+abs(pos-s[i].y)-1);
	  }
	Fmin[0]=pos-2;
	//the first line 
	for(int i=1;i<=t2;)
	{
	  int k1=0,k2=0;ll p=t[i].x;
	  for(;t[i].x==p;i++)
	  {
	    if(t[i].y<pos)s1[++k1]=t[i];
	    else s2[++k2]=t[i];
	  }
	  //split
	  for(int j=1;j<=k1+k2;j++)
	  {
	    g1[j]=inf;g2[j]=inf;
		L1min[j]=inf;R1min[j]=inf;
		L2min[j]=inf;R2min[j]=inf;
	  }
	  //init 
	  Gmin[0]=pos;
	  for(int j=1;j<=k1;j++)Gmin[j]=inf;
	  for(int j=1;j<=k1;j++)
	    for(int k=j;k;k--)
	    {
	      tmp=Gmin[k-1]-s1[j].y+s1[j].c;
		  Gmin[k]=min(Gmin[k],tmp+s1[j].y);
		  L1min[k]=min(L1min[k],tmp);
		  L2min[k]=min(L2min[k],tmp+pos-s1[j].y);
		}
	  //left 
	  Gmin[0]=-pos;
	  for(int j=1;j<=k2;j++)Gmin[j]=inf;
	  for(int j=1;j<=k2;j++)
	    for(int k=j;k;k--)
	    {
	      tmp=Gmin[k-1]+s2[j].y+s2[j].c;
	      Gmin[k]=min(Gmin[k],tmp-s2[j].y);
	      R1min[k]=min(R1min[k],tmp);
	      R2min[k]=min(R2min[k],tmp+s2[j].y-pos);
		}
	  //right
	  for(int j=1;j<=k1+k2;j++)
	    for(int k=0;k<=j;k++)
	    { 
		  g1[j]=min(g1[j],L1min[k]+R2min[j-k]);
		  g1[j]=min(g1[j],L2min[k]+R1min[j-k]);
		  g2[j]=min(g2[j],L2min[k]+R2min[j-k]);
		}
	  //merge
	  for(int j=K;j;j--)
	    for(int k=1;k<=min(j,k1+k2);k++)
	    {
	      f[j]=min(f[j],Fmin[j-k]+p+g1[k]);
	      Fmin[j]=min(Fmin[j],Fmin[j-k]+g2[k]);
		}
	  //update 
	}
	for(int i=1;i<K;i++)printf("%lld ",f[i]);
	printf("%lld\n",f[K]);
  }
  return 0;
} 
