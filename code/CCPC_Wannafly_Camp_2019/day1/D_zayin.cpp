#include<bits/stdc++.h>
#define maxn 105
#define maxm 10
using namespace std;
typedef unsigned long long LL;

int F10[4]={1,10,100,1000};

int getlen(LL n)    {
    int cnt=0;
    for (;n;n/=10)  ++cnt;
    return cnt;
}

struct HP
{
    static const int base=10000;
    static const int width=4;
    
    deque<int> a;

    // HP()    {
    //     a.clear();
    // }

    HP (LL x=0) {
        if (!x)
            a.push_back(x);
        else
            for (;x;x/=base)
                a.push_back(x%base);
    }

    HP operator + (const HP& N) const   {
        HP ans;
        ans.a.clear();
        for (int i=0,g=0;;++i)
        {
            if (!g&&i>=a.size()&&i>=N.a.size())   break;
            if (i<a.size()) g+=a[i];
            if (i<N.a.size())   g+=N.a[i];
            ans.a.push_back(g%base);
            g/=base;
        }
        return ans;
    }

    HP operator - (const HP& N) const   {
        HP ans;
        ans.a.clear();
        for (int i=0;i<a.size();++i)
            if (i<N.a.size())
                ans.a.push_back(a[i]-N.a[i]);
            else
                ans.a.push_back(a[i]);
        
        for (int i=0;i<ans.a.size();++i)
            if (ans.a[i]<0)
                assert(i+1<ans.a.size()),
                ans.a[i]+=base,--ans.a[i+1];

        while (!ans.a.back())
            ans.a.pop_back();
        return ans;
    }

    HP operator * (const int& x) const  {
        HP ans;
        ans.a.clear();
        for (int i=0,g=0;;++i)
        {
            if (!g&&i>=a.size())    break;
            if (i<a.size()) g+=a[i]*x;
            ans.a.push_back(g%base);
            g/=base;
        }
        return ans;
    }

    HP operator / (const int& x) const  {
        HP ans;
        ans.a.clear();
        for (int i=a.size()-1,g=0;i>=0;--i)
        {
            g=g*base+a[i];
            ans.a.push_front(g/x);
            g%=x;
        }

        while (!ans.a.back())
            ans.a.pop_back();
        return ans;
    }

    int pos(int x)   {
        int p=x/width;
        return a[p]/F10[x%width]%10;
    }

    int len()   {
        return (a.size()-1)*width+getlen(a.back());
    }

    HP last(int len)    {
        HP ans=*this;
        ans.a.resize(len/width);
        if (len%width)
            ans.a.push_back(a[len/width]%F10[len%width]);
        return ans;
    }

    bool operator < (const HP& N)   const   {
        if (a.size()!=N.a.size())
            return a.size()<N.a.size();
        for (int i=a.size()-1;i>=0;--i)
            if (a[i]!=N.a[i])
                return a[i]<N.a[i];
        return 0;
    }
} ;

ostream& operator << (ostream& os,const HP& N)  {
    os<<N.a.back();
    for (int i=N.a.size()-2;i>=0;--i)
        os<<setw(HP::width)<<setfill('0')<<N.a[i]<<setfill(' ');
    return os;
}

HP F[maxn]={1};
HP f[maxm][maxn],g[maxn],sg[maxn];
HP dp[maxm][maxm][maxn];

void ten(HP &N,int len)
{
    N.a.resize(len/HP::width,0);
    N.a.push_back(F10[len%HP::width]);
}

void predo()
{
    for (int i=0;i<maxn;++i)
        ten(F[i],i);
    for (int len=3;len<maxn;++len)
    {
        for (int a=0;a<maxm;++a)
        {
            for (int b=0;b<maxm;++b)
            {
                for (int c=0;c<maxm;++c)
                    if (a<b&&b<c)
                        dp[a][b][len]=dp[a][b][len]+F[len-3];
                    else
                        dp[a][b][len]=dp[a][b][len]+dp[b][c][len-1];
                f[a][len]=f[a][len]+dp[a][b][len];
            }
            if (a)
                g[len]=g[len]+f[a][len];
        }
        sg[len]=sg[len-1]+g[len];
    }
}

HP count(HP n)
{
    int len=n.len();
    HP ans=sg[len-1];
    
    // cout<<"len:"<<len<<endl;
    int a=9,b=9;
    for (int i=len-1;i>=0;--i)
    {
        int c=n.pos(i);

        HP t=0;
        for (int j=(i==len-1);j<c;++j)
            if (a<b&&b<j)
                t=t+F[i];
            else
                t=t+dp[b][j][i+2];
        ans=ans+t;
        // cout<<i<<" "<<a<<" "<<b<<" "<<c<<" "<<t<<endl;
        if (a<b&b<c)
        {
            ans=ans+n.last(i)+1;
            break;
        } else
        {
            a=b,b=c;
        }
    }
    return ans;
}

int main()
{
    predo();

    double f;
    cin>>f;

    LL q=100000,p=f*100000;

    // cout<<p<<"/"<<q<<endl;
    HP a=0,b=99;

    while (a*q<b*p)
    {
        HP c=(b*p-a*q+(q-p-1))/(q-p);
        
        // cout<<a<<" "<<b<<" "<<c<<endl;
        b=b+c,a=count(b);
        // cout<<a<<" "<<b<<" "<<1.0*a/b<<endl;
    }
    cout<<b<<endl;
    return 0;
}