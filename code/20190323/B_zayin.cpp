#include <bits/stdc++.h>
#define mkp(x,y)	make_pair(x,y)
#define maxn 1000005
using namespace std;
typedef pair<int,int> pii;

string s;
char c;

int N;
map<string,int> Id;

int id(const string& s)	{
	if (Id.count(s))	return Id[s];
	return Id[s]=++N;
}

vector<string> T;
vector<char> nxt;

vector<int> G[2][maxn];

bool vis[maxn][2];

queue<pii> q;

int main() {
	while (cin>>s)	{
		c=0;
		if (!isalpha(s.back()))
			c=s.back(),s.pop_back();
		T.push_back(s),nxt.push_back(c);
	}
	for (int i=0;i+1<T.size();++i)	{
		if (nxt[i]!='.')
			G[0][id(T[i])].push_back(id(T[i+1])),
			G[1][id(T[i+1])].push_back(id(T[i]));
		if (nxt[i]==',')
			vis[id(T[i])][0]=vis[id(T[i+1])][1]=1;
	}
	for (int i=1;i<=N;++i)
		for (int c=0;c<=1;++c)
			if (vis[i][c])
				q.push(mkp(i,c));
	while (!q.empty())	{
		auto p=q.front();	q.pop();
		int c=p.second;
		for (int j:G[c][p.first])
			if (!vis[j][c^1])
				q.push(mkp(j,c^1)),vis[j][c^1]=1;
	}
	for (int i=0;i<T.size();++i)	{
		cout<<T[i];
		if (nxt[i]=='.') cout<<".";
		else
		if (vis[id(T[i])][0])	cout<<",";
		if (i+1<T.size())	cout<<" ";
	}
}
