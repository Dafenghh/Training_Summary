#include<bits/stdc++.h>
#define maxn 2000050
using namespace std;

int n,H,W;
struct point {
	int x,y;
	int id()	{
		if (!y)	return x;
		if (x==W)	return W+y;
		if (y==H)	return W+H+W-x;
		if (x==0)	return W+H+W+H-y;
	}
};
struct seg	{
	point p,q;
	void read()	{	scanf("%d%d%d%d",&p.x,&p.y,&q.x,&q.y);	}
} L[maxn];

int len[maxn],pos[maxn];

bool cmp(int i,int j)	{
	return len[i]<len[j];
}
bool vis[maxn];

void P(double x)	{
	if (x<W)	printf("%lf 0 ",x);
	else
	if (x<W+H)	printf("%d %lf ",W,x-W);
	else
	if (x<W+H+W)	printf("%lf %d ",(W+H+W)-x,H);
	else
	printf("%d %lf ",0,(W+H+W+H)-x);
}
void print(double l,double r)	{
	printf("1\n");
	P(l),P(r);
}

bool judge()	{
	for (int i=0;i<n;++i)	{
		len[i<<1]=L[i].p.id();
		len[i<<1|1]=L[i].q.id();
	}
	for (int i=0;i<2*n;++i)	pos[i]=i;
	sort(pos,pos+n*2,cmp);
	for (int i=0,j=0;i<n*2;++i)	{
		while (j<n*2&&!vis[pos[j]>>1])	vis[pos[j]>>1]=1,++j;
		if (j-i==n)	
			return print(len[pos[i]]-0.5,len[pos[j]]-0.5),1;
		vis[pos[i]>>1]=0;
	}
	return 0;
}

int main()	{
	scanf("%d%d%d",&n,&W,&H);
	for (int i=0;i<n;++i)
		L[i].read();
	if (!judge())	{
		puts("2");
		printf("%lf %d %lf %d\n%lf %d %lf %d\n",	0.5,H,W-0.5,0,
													0.5,0,W-0.5,H);
	}
	return 0;
}
