#include<bits/stdc++.h>
#define id(i,j) ((i)*N+(j))
#define pos(i,j)    (id(i,j)<<1)
#define st(i,j)     (3<<pos(i,j))
#define maxs 300050
using namespace std;

const double inf=1e5;
const double eps=1e-5;

const int N=3;
char s[maxs];

bool vis[maxs];
double dp[maxs];

vector<int> opA[maxs],opB[maxs];

const char *str="#OX";
int chr(char c) {
    if (c=='O') return 1;
    if (c=='X') return 2;
    return 0;
}

void predo()    {
    for (int i=0;i<N;++i)
        for (int j=0;j<N;++j)   {
            int k=id(i,j),t1=~st(i,j),t2=t1;
            opB[k].push_back(t1);

            if (i)  t1&=~st(i-1,j);
            if (i!=N-1) t1&=~st(i+1,j);
            if (j)  t2&=~st(i,j-1);
            if (j!=N-1) t2&=~st(i,j+1);
            opA[k]={t1,t2,t1&t2};
        }
}

double calc(int st) {
    if (vis[st])    return dp[st];
    // cout<<"calc:"<<st<<endl;
    vis[st]=1;
    double L=-inf,R=inf;
    for (int i=0;i<N;++i)
        for (int j=0;j<N;++j)   {
            int x=(st&st(i,j))>>pos(i,j)&3;
            if (x==1)
                for (int s:opA[id(i,j)])
                    L=max(L,calc(st&s));
            if (x==2)
                for (int s:opB[id(i,j)])
                    R=min(R,calc(st&s));
        }
    if (L<-eps&&R>eps)
        dp[st]=0;
    else    {
        for (int q=1;;q<<=1)    {
            int l=ceil(L*q+eps),r=floor(R*q-eps);
            if (l<=r)   {
                // cout<<L<<" "<<R<<" "<<q<<" "<<l<<" "<<r<<endl;
                dp[st]=(double)(l>=0?l:r)/q;
                break;
            }
        }
    }
    // cout<<"calc:"<<st<<" "<<dp[st]<<" -> "<<L<<" "<<R<<endl;
    // for (int i=0;i<N;++i)   {
    //     for (int j=0;j<N;++j)
    //         putchar(str[(st&st(i,j))>>pos(i,j)]);
    //     cout<<endl;
    // }
    return dp[st];
}

int main()  {
    predo();
    int T;
    scanf("%d",&T);
    while (T--) {
        int n;
        scanf("%d",&n);
        double ans=0;
        while (n--) {
            int st=0;
            for (int i=0;i<N;++i)   {
                scanf("%s",s);
                for (int j=0;j<N;++j)
                    // cout<<s[j<<1]<<"("<<chr(s[j<<1])<<","<<pos(i,j)<<") ",
                    st|=chr(s[j<<1])<<pos(i,j);
                // cout<<endl;
            }
            double t=calc(st);
            // cout<<st<<":"<<t<<endl;
            ans+=t;
        }
        // cout<<"ans:"<<ans<<endl;
        // cout<<(int)(ans*512)<<endl;
        if (ans>eps)
            puts("Alice");
        else
        if (ans<-eps)
            puts("Bob");
        else
            puts("Second");
    }
    return 0;
}
