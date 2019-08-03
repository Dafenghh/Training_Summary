#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
int Mod;
void add(int &a, ll b) {
    a = (a + b) % Mod;
}
 
struct Mat {
    static const int N = 2;
    int a[N][N];
    Mat() {
        for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            a[i][j] = 0;
    }
    int* operator[](int x) {
        return a[x];
    }
    const int * operator[](int x)const {
        return a[x];
    }
    static Mat Ident() {
        Mat res;
        for (int i = 0; i < N; i++) res[i][i] = 1;
        return res;
    }
    Mat operator*(const Mat &b) const {
        Mat res;
        for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            if (a[i][j] == 0) continue;
            for (int k = 0; k < N; k++)
                add(res[i][k], 1LL*a[i][j]*b[j][k]);
        }
        return res;
    }
};
 
const int N = 1e6+10;
 
Mat pw10[N];
 
Mat calc10(const Mat&A) {
    Mat A2 = A*A, A4 = A2*A2, A8 = A4*A4;
    return A2*A8;
}
 
Mat Pow(Mat A, int n) {
    Mat res = Mat::Ident();
    for (; n > 0; n >>= 1) {
        if (n & 1) res = res * A;
        A = A*A;
    }
    return res;
}
 
 
char s[N];
 
int main() {
    ll x0, x1;
    int a, b;
    scanf("%lld%lld%d%d", &x0, &x1, &a, &b);
    Mat A;
    A[0][0] = a; A[0][1] = b;
    A[1][0] = 1;
 
    pw10[0] = A;
    scanf("%s%d", s, &Mod);
    int n = strlen(s);
    for (int i = 0; i < n - 1; i++) {
        pw10[i+1] = calc10(pw10[i]);
    }
 
    Mat res = Mat::Ident();
    for (int i = 0; i < n; i++) {
        int x = s[n-1-i] - '0';
        if (x>0) res = res*Pow(pw10[i], x);
    }
    printf("%lld\n", (res[1][0]*x1%Mod+res[1][1]*x0%Mod)%Mod);
 
}
