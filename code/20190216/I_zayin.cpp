#include<bits/stdc++.h>
#define maxn 1000050
#define maxs (1<<26)
using namespace std;
typedef long long LL;

int n;
char s[maxn];

map<int,int> cnt;

int main()
{
	LL ans=0;
	scanf("%d",&n);
	while (n--)
	{
		scanf("%s",s);
		int S=0;
		for (int i=0;s[i];++i)
			S^=1<<(s[i]-'a');
		for (int c=0;c<26;++c)
			if (cnt.count(S^(1<<c)))
				ans+=cnt[S^(1<<c)];
		ans+=cnt[S]++;
	}
	printf("%lld\n",ans);
	return 0;
}