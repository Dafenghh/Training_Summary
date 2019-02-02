#include<bits/stdc++.h>
#define N 26
#define maxn 2050
#define modu 998244353
using namespace std;
typedef long long LL;

struct Matrix
{
    LL A[N+1][N+1];
    Matrix(LL x=0)    {
        memset(A,0,sizeof(A));
        for (int i=0;i<=N;++i)
            A[i][i]=x;
    }

    LL* operator [] (const int& i)  {
        return A[i];
    }

    const LL* operator [] (const int& i) const  {
        return A[i];
    }

    Matrix operator * (const Matrix& M) const   {
        Matrix Ans;
        for (int i=0;i<=N;++i)
            for (int j=0;j<=N;++j)
                for (int k=0;k<=N;++k)
                    Ans[i][j]=(Ans[i][j]+A[i][k]*M[k][j])%modu;
        return Ans;
    }

} A(1);

int n;
char s[maxn];

Matrix get(int c)
{
    Matrix A(1);
    A[c][c]=0,A[c][N]=1;
    A[N][c]=-1,A[N][N]=2;
    return A;
}

int main()
{
    scanf("%d%s",&n,s+1);
    for (int i=n;i;--i)
        A=A*get(s[i]-'a')*A;
    printf("%lld\n",(A[N][N]-1+modu)%modu);
    return 0;
}
