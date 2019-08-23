#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll mod_pow(ll x, ll n, ll Mod) {
    x %= Mod;
    ll res = 1;
    for (; n > 0; n >>= 1) {
        if (n & 1) res = res * x % Mod;
        x = x * x % Mod;
    }
    return res;
}
const int Mod = 1e9+9;

void add(int &a, ll b) {
    a = (a+b)%Mod;
}

const int w = 115381398;
const int w2 = 1LL*w*w%Mod;

const ll inv3 = mod_pow(3, Mod-2, Mod);

void FWT(int *a, int n, int flag = 1) {
    for (int d = 1; d < n; d *= 3)
    for (int i = 0; i < n; i += 3*d)
    for (int j = 0; j < d; j++) {
        ll x = a[i+j], y = a[i+j+d], z = a[i+j+2*d]; 
        a[i+j] = (x+y+z)%Mod;
        a[i+j+d] = (x+w*y+w2*z)%Mod;
        a[i+j+2*d] = (x+w2*y+w*z)%Mod;
        if (flag == -1) {
            a[i+j]=inv3*a[i+j]%Mod;
            a[i+j+d]=inv3*a[i+j+d]%Mod;
            a[i+j+2*d]=inv3*a[i+j+2*d]%Mod;
        }
    }
}
const int N = 6561;
int pw3[8];
int p;

struct Node {
    ll len;
    vector<int> a[7];
    Node() {
        len = 0;
        for (int i = 0; i < p; i++) a[i] = vector<int>(N);
    }
    Node operator*(const Node&b) const {
        Node res;
        res.len = len+b.len;
        int pw = mod_pow(8, b.len, p);
        for (int i = 0; i < p; i++) 
        for (int j = 0; j < p; j++) {
            int tar = (i*pw+j)%p;
            for (int k = 0; k < N; k++)
                add(res.a[tar][k], 1LL*a[i][k]*b.a[j][k]);
        }
        return res;
    }
}base[8][63];

Node Base(int l, int r) {
    Node res;
    res.len = 1;
    for (int i = l; i < r; i++) {
        res.a[i%p][pw3[i]]++;
    }
    for (int i = 0; i < p; i++) {
        FWT(&res.a[i][0], N);
    }
    return res;
}
Node Empty() {
    Node res;
    res.len = 0;
    res.a[0][0] = 1;
    FWT(&res.a[0][0], N);
    return res;
}


int main() {
    pw3[0] = 1;
    for (int i = 1; i < 8; i++) pw3[i] = pw3[i-1]*3;

    for (p = 1; p < 8; p++) {
        base[p][0] = Base(0,8);
        for (int i = 1; i < 63; i++) base[p][i] = base[p][i-1]*base[p][i-1];
    }


    ll k;
    while (scanf("%lld%d", &k, &p) != EOF) {
        --k;
        Node res = Empty();
        for (int i = 0; k > 0; k >>= 1, ++i) {
            if (k & 1) res = res * base[p][i];
        }
        res = Base(1,8)*res;
        FWT(&res.a[0][0],N,-1);
        printf("%d\n", res.a[0][0]);
    }
}
