#include<bits/stdc++.h>
#define maxc 26
#define maxn 300050
using namespace std;
typedef unsigned long long ULL;
const ULL p=131;

int n;
char s[maxn];

ULL h[maxn],g[maxn],pw[maxn]={1};

bool ok[maxn];
int all,son[maxn][maxc],fail[maxn],cnt[maxn],len[maxn],text[maxn],last,sz;

int newnode(int l)	{
	memset(son[sz],0,sizeof(son[sz]));
	cnt[sz]=ok[sz]=0;
	len[sz]=l;
	return sz++;
}

void init()	{
	last=sz=all=0;
	newnode(0),newnode(-1);
	text[0]=-1,fail[0]=1;
}


int getfail(int x)	{
	while (text[all-len[x]-1]!=text[all])	x=fail[x];
	return x;
}

bool add(int w)	{
	text[++all]=w;
	int x=getfail(last);
	bool flag=0;
	if (!son[x][w])	{
		int y=newnode(len[x]+2);
		fail[y]=son[getfail(fail[x])][w];
		son[x][w]=y;
		flag=1;
	}
	cnt[last=son[x][w]]++;
	return flag;
}

ULL h_hash(int l,int r)	{
	return h[r]-h[l-1]*pw[r-l+1];
}
ULL g_hash(int l,int r)	{
	return g[l]-g[r+1]*pw[r-l+1];
}

int ans[maxn];

int main()	{
	for (int i=1;i<maxn;++i) pw[i]=pw[i-1]*p;
	while (~scanf("%s",s+1))	{
		n=strlen(s+1);
		h[0]=0;for (int i=1;i<=n;++i) h[i]=h[i-1]*p+s[i];
		g[n+1]=0;for (int i=n;i;--i)    g[i]=g[i+1]*p+s[i];
		init();
		for (int i=1;i<=n;++i)	{
			if (!add(s[i]-'a'))	continue;
			int l=len[last];
			l=(l+1)/2;
	//		cout<<i<<" "<<l<<" "<<h_hash(i-l+1,i)<<" "<<g_hash(i-l+1,i)<<endl;
			if (h_hash(i-l+1,i)==g_hash(i-l+1,i))
	//			cout<<"ok!!"<<endl,
				ok[last]=1;
		}
		for (int i=sz-1;~i;--i)
			cnt[fail[i]]+=cnt[i];
		for (int i=1;i<=n;++i)	ans[i]=0;
		for (int i=2;i<sz;++i)
			if (ok[i])
				ans[len[i]]+=cnt[i];
		for (int i=1;i<=n;++i)
			printf("%d%c",ans[i]," \n"[i==n]);
	}
	return 0;
}
