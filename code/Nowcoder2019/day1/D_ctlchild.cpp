#include <bits/stdc++.h>
using namespace std;
const int maxn=1205000;
int n, m, k;
int gray[maxn], nd[maxn];
int a[maxn], f[maxn];
const long long P = 1e9 + 7;
void fwt(int a[], int n){
    for (int d = 1; d < n; d <<= 1)
        for (int m = d << 1, i = 0; i < n; i +=m)
            for (int j = 0; j < d; j++){
                int x=a[i + j], y = a[i + j + d];
                a[i + j]=(x + y) % P;
                a[i + j + d] = (x - y + P) % P;  
            }
}
long long Pow(long long x, long long y){
    long long ans = 1;
    while (y){
        if (y & 1) ans = ans * x % P;
        x = x * x % P;
        y >>= 1;
    }
    return ans;
}
int read(){
    int x = 0; char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) {x = x * 10 + ch - '0'; ch = getchar();}
    return x;
}
int main()
{
    while (~scanf("%d%d%d", &n, &m, &k))
    {
        for (int i = 0; i < (1 << m); i++)
            gray[i] = i ^ (i >> 1);
        for (int i = 0; i < (1 << m); i++)
            nd[i]=__builtin_ctz(gray[i] ^ gray[i + 1]);
        for (int i = 0; i < (1 << k); i++) f[i] = 0;
        for (int i = 1; i <= n; i++){
            for (int j = 0; j < m; j++) a[j] = read();
            for (int j = 0, sgn = 1, val = 0; j < (1 << m); j++){
                f[val] += sgn;
                val ^= a[nd[j]];
                sgn = -sgn;
            }          
        }
//        for (int i = 0; i < (1 << k); i++) printf("%lld ", f[i]);
//        puts("");
        fwt(f , 1 << k);
        long long inv = Pow(1 << m, P - 2);
        long long ans = 0, mul = 1;
        for (int i = 0; i < (1 << k); i++) {
            ans ^= 1ll * f[i] * mul % P * inv % P;
            mul = mul * 3 % P;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
