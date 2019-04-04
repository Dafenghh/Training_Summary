#include<bits/stdc++.h>
#define maxn 100050
#define maxl 550050
#define modu 998244353
#define bad(k)	(circle[edge[k]]&&circle[edge[k^1]])
using namespace std;
typedef long long LL;

LL pw(LL a,LL k=modu-2)	{
	LL ans=1;
	for (;k;k>>=1)	{
		if (k&1)
			ans=ans*a%modu;
		a=a*a%modu;
	}
	return ans;
}
struct NTT	{
	int N,rev[maxl];
	LL I,w[maxl];
	void init(int n)	{
		for (N=1;N<=n;N<<=1);	I=pw(N);
		
		rev[0]=0,rev[1]=N>>1;
		for (int i=2;i<N;++i)
			rev[i]=rev[i>>1]>>1|rev[i&1];
		
		w[0]=1,w[1]=pw(3,(modu-1)/N);
		for (int i=2;i<N;++i)
			w[i]=w[i-1]*w[1]%modu;
	}
	
	void DFT(LL *A)	{
		for (int i=0;i<N;++i)
			if (i<rev[i])
				swap(A[i],A[rev[i]]);
		for (int len=2;len<=N;len<<=1)	{
			int m=len>>1;
			for (LL *p=A;p!=A+N;p+=len)
				for (int i=0;i<m;++i)	{
					LL u=p[i],v=p[i+m]*w[N/len*i]%modu;
					p[i]=(u+v)%modu;
					p[i+m]=(u-v+modu)%modu;
				}
		}
	}
	
	void IDFT(LL *A)	{
		DFT(A);
		reverse(A+1,A+N);
		for (int i=0;i<N;++i)
			A[i]=A[i]*I%modu;
	}
} T;

int n;

int tot;
int head[maxn],edge[maxn<<1],nxt[maxn<<1];

void join(int u,int v)	{
	edge[tot]=v; nxt[tot]=head[u]; head[u]=tot++;
	edge[tot]=u; nxt[tot]=head[v]; head[v]=tot++;
}

void init()	{
	tot=0;
	memset(head,-1,sizeof(head));
	
	scanf("%d",&n);
	for (int k=0;k<n;++k)	{
		int u,v;
		scanf("%d%d",&u,&v);
		join(u,v);
	}
}

int fa[maxn];

vector<int> C,L[maxn],R[maxn];
int circle[maxn];
int find_circle(int i=1)	{
	circle[i]=0;
	for (int k=head[i],j;~k;k=nxt[k])	{
		if ((j=edge[k])==fa[i])	continue;
		if (!~fa[j])
			fa[j]=i,circle[i]+=find_circle(j);
		else
		if (!circle[i])
			circle[i]=1,circle[fa[j]]=-1;
	}
	if (circle[i])	C.push_back(i);
	return circle[i];
}

int tT;

int vis[maxn];
int sz[maxn],mx[maxn]={maxn};

LL ans[maxl],f[maxl],g[maxl];

int D,dis[maxn];
int Q[maxn],l,r;

void getvert(int v,int d=0)	{
	Q[l=r=1]=v;
	fa[v]=D=0,dis[v]=d;
	for (int i;l<=r;++l)	{
		++f[dis[i=Q[l]]];
		D=max(D,dis[i]+1);
		for (int k=head[i],j;~k;k=nxt[k])
			if (!bad(k)&&(j=edge[k])!=fa[i]&&!vis[j])	{
				Q[++r]=j;
				fa[j]=i,dis[j]=dis[i]+1;
			}
	}
}
int getroot(int v,int d=0)	{
	getvert(v,d);
	for (int k=1;k<=r;++k)	sz[Q[k]]=1,mx[Q[k]]=0;
	int rt=0;
	for (int k=r;k;--k)	{
		int i=Q[k];
		sz[fa[i]]+=sz[i];
		mx[fa[i]]=max(mx[fa[i]],sz[i]);
		mx[i]=max(mx[i],r-sz[i]);
		if (mx[rt]>mx[i])
			rt=i;
	}
	return rt;
}

void calc1(int diff,int sgn)	{
	T.init(D<<1);
	T.DFT(f);
	for (int i=0;i<T.N;++i)	f[i]=f[i]*f[i]%modu;
	T.IDFT(f);
	sgn=(sgn+modu)%modu;
	for (int i=0;i<T.N;f[i++]=0)
		if (f[i])
			ans[i+diff]=(ans[i+diff]+sgn*f[i])%modu;
}

void tree_calc(int i,int diff=1)	{
	int rt=getroot(i,diff!=C.size());
	calc1(diff,diff==C.size()?1:-1);
	getvert(rt,0);
	calc1(1,1);
	vis[rt]=1;
	for (int k=head[rt],j;~k;k=nxt[k])
		if (!bad(k)&&!vis[j=edge[k]])
			tree_calc(j);
}

void calc2(const vector<int>& A,const vector<int>& B,int diff)	{
	for (int i=0;i<A.size();++i)	f[i]=A[i];
	for (int i=0;i<B.size();++i)	g[i]=B[i];
	T.init(A.size()+B.size());
	T.DFT(f),T.DFT(g);
	for (int i=0;i<T.N;++i)	f[i]=f[i]*g[i]%modu;
	T.IDFT(f);
	for (int i=0;i<T.N;++i)
		if (f[i])
			ans[i+diff]=(ans[i+diff]+2*f[i])%modu;
	for (int i=0;i<T.N;++i)	f[i]=g[i]=0;
}

void add(vector<int> &A,const vector<int>& B,int diff)	{
	if (A.size()<B.size()+diff)
		A.resize(B.size()+diff);
	for (int i=0;i<B.size();++i)
		A[i+diff]+=B[i];
}

void circle_calc(int l,int r)	{
	if (l==r)	return ;
	int mid=(l+r)>>1;
	circle_calc(l,mid);
	circle_calc(mid+1,r);

	calc2(R[mid],L[mid+1],2);
	calc2(L[l],R[r],C.size()-(r-l)+1);

	add(L[l],L[mid+1],mid-l+1);
	add(R[r],R[mid],r-mid);
}

void solve()	{
	memset(ans,0,sizeof(ans));
	
	fill(fa,fa+n+1,-1);
	C.clear();
	fa[1]=0,find_circle();
	
	fill(vis,vis+n+1,0);
    T.init(n*2+5);
	for (int i=0;i<C.size();++i)	{
		getvert(C[i]);
		L[i].clear(),R[i].clear();
		L[i].resize(D),R[i].resize(D);
		for (int j=0;j<D;f[j++]=0)
			L[i][j]=R[i][j]=f[j];
	}
	for (int i=0;i<C.size();++i)
		for (int j=0;j<L[i].size();++j)
			f[j]+=L[i][j];

	D=n,calc1(C.size(),-1);
	for (int i:C)
		tree_calc(i,C.size());

	fill(vis,vis+n+1,0);
	circle_calc(0,C.size()-1);
	
	LL Ans=0;
	for (int i=1;i<=n;++i)
		Ans=(Ans+ans[i]*pw(i))%modu;
	printf("%lld\n",Ans);
}

int main()	{
	int T,icase=0;
	scanf("%d",&T);
	while (T--)	{
		printf("Case #%d: ",++icase);
		init();
		solve();
	}
	return 0;
}
