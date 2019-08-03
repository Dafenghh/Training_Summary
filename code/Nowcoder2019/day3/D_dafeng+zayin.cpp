#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long long LL;
int p;
const int N = 2;
void add(int &a, ll b) {
    a = (a + b) % p;
}
struct Mat {
    int a[N][N];
    Mat() {
        for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            a[i][j] = 0;
        }
    }
     
    static Mat Ident() {
        Mat res;
        for (int i = 0; i < N; i++) res[i][i] = 1;
        return res;
    }
    int* operator[](int x) {
        return a[x];
    }
    const int* operator[](int x)const {
        return a[x];
    }
    static Mat Standard() {
        Mat res;
        res[0][0] = 10;
        res[0][1] = 1;
        res[1][1] = 1;
        return res;
    }
    Mat operator*(const Mat&b) const {
        Mat c;
        for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                add(c[i][k], 1LL*a[i][j]*b[j][k]);
            }
        }
        return c;
    }
};
 
Mat Pow(Mat A, int n) {
    Mat res = Mat::Ident();
    for (; n > 0; n >>= 1) {
        if (n & 1) res = res * A;
        A = A * A;
    }
    return res;
}
 
bool test(int x) {
    Mat A = Pow(Mat::Standard(), x);
    return A[0][1] == 0;
}
 
int minLen() {
    vector<int> vec;
    for (ll i = 2; i * i <= p-1; i++) {
        if ((p-1) % i == 0) {
            if (test(i)) return i;
            int x = (p-1)/i;
            if (x!=i) vec.push_back(x);
        }
    }
    reverse(vec.begin(), vec.end());
    for (auto x: vec) {
        if (test(x)) return x;
    }
    return p-1;
}
 
 
 
int n,m, len;
 
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &p, &n, &m);
        if (p == 2 || p == 5) {
            puts("0");
            continue;
        }
         
        if (p == 3) len = 3;
        else len = minLen();
         
        LL ans=0;
        int C=1;
        vector<pair<int,int> > A;
        for (int i=2;i*i<=len;++i)  {
            if (len%i)  continue;
            int c=0;
            while (len%i==0)    ++c,len/=i;
            A.emplace_back(i,c);
            C=max(C,c);
        }
        if (len>1)
            A.emplace_back(len,1);
        for (int j=1;j<=C&&j<=m;++j)  {
            int g=1;
            for (pair<int,int> p:A)   {
                int e=(p.second-1)/j+1;
                while (e--) g*=p.first;
            }
            if (j<C)
                ans+=(n/g);
            else
                ans+=(LL)(m-j+1)*(n/g);
        }
        printf("%lld\n",ans);
    }
     
}