#include<bits/stdc++.h>
#define N 100010
#define M 27
using namespace std;
int n,m,f[N][M],pos[M],used[M],L[N],R[N];
char s[N],ans[N];
vector<int>t[M];
int main()
{
  while(~scanf(" %s%d",s+1,&m))
  {
    n=strlen(s+1);
    for(int i=0;i<26;i++)
	  f[n+1][i]=0,t[i].clear(),pos[i]=0,used[i]=0;
    for(int i=1;i<=n;i++)
      t[s[i]-'a'].push_back(i);
    for(int i=0;i<26;i++)
      scanf("%d%d",&L[i],&R[i]);
    for(int i=n;i;i--)
     for(int j=0;j<26;j++)
      { 
        if(s[i]-'a'==j)f[i][j]=f[i+1][j]+1;
        else f[i][j]=f[i+1][j];
	  }
	int invalid=0;
    for(int i=1,pre=0;i<=m;i++)
    {
	  int tag=0;
      for(int j=0;j<26;j++)
      {
        for(;pos[j]<t[j].size()&&t[j][pos[j]]<=pre;pos[j]++);
	    if(pos[j]>=t[j].size())continue;
	    if(used[j]==R[j])continue;
	    int flag=0,sum=0,res=0,p=t[j][pos[j]];
	    for(int k=0;k<26;k++)
	    {
	  	  if(f[p][k]+used[k]<L[k]){flag=1;break;}
	      res+=max(0,L[k]-used[k]);
	      if(j==k&&L[k]>used[k])res--;
		  sum+=min(R[k]-used[k],f[p][k]);
	    }
	    if(flag||i+sum-1<m||i+res>m)continue;
	    pre=p;ans[i]='a'+j;used[j]++;
		tag=1;break;
	  }
	  if(!tag){invalid=1;break;}
	}
	if(invalid)printf("-1");
	else for(int i=1;i<=m;i++)printf("%c",ans[i]);
	printf("\n");
  }
  return 0;
}

