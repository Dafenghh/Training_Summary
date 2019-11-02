#include<bits/stdc++.h>
#define maxw 30
#define maxn 100050
using namespace std;

struct Trie {
    int sz;
    int cnt[maxn*maxw];
    int ch[maxn*maxw][2];
    void clear() {
        sz=0;
        newnode();
    }
    int newnode()   {
        ++sz;
        cnt[sz]=ch[sz][0]=ch[sz][1]=0;
        return sz;
    }
    void ins()   {
        int k=1,a;
        ++cnt[k];
        scanf("%d",&a);
        for (int i=maxw-1;~i;--i)   {
            int c=a>>i&1;
            if (!ch[k][c])  
                ch[k][c]=newnode();
            k=ch[k][c];
            ++cnt[k];
        }
    }
    int find(int a) {
        int k=1,ans=0;
        for (int i=maxw-1;~i;--i)   {
            int c=a>>i&1;
            if (!cnt[ch[k][c]])  c^=1;
            k=ch[k][c];
            ans|=c<<i;
        }
        return ans;
    }
    int del(int a)   {
        int k=1;
        --cnt[k];
        for (int i=maxw-1;~i;--i)   {
            int c=a>>i&1;
            assert(cnt[ch[k][c]]);
            k=ch[k][c];
            --cnt[k];
        }
    }
} T[2];

vector<int> a;
int stk[maxn],tp;

int main()  {
    int n,Tc;
    scanf("%d",&Tc);
    while (Tc--) {
        scanf("%d",&n);
        a.clear();
        for (int c=0;c<=1;++c)  {
            T[c].clear();
            for (int i=1;i<=n;++i)
                T[c].ins();
        }

        for (int c=0;a.size()<n;c^=1)   {
            int x=T[c^1].find(stk[tp]);
            int y=T[c].find(x);
            if (tp&&y==stk[tp]) {
                // cout<<x<<" "<<y<<endl;
                T[c^1].del(x);
                T[c].del(y);
                a.push_back(x^y),--tp;
            }
            else
                stk[++tp]=x;
        }
        sort(a.begin(),a.end());
        for (int i=0;i<n;++i)
            printf("%d%c",a[i]," \n"[i==n-1]);
    }
    return 0;
}
