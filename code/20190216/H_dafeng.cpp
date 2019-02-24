#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+10;
const int Mod = 1e9+7;
typedef long long ll;
ll fact[N], inv[N];

void add(ll &a, ll b) {
    a = (a + b) % Mod;
}

ll mod_pow(ll x, ll n) {
    ll res = 1;
    for (; n > 0; n >>= 1) {
        if (n & 1) res = res * x % Mod;
        x = x * x % Mod;
    }
    return res;
}

void init() {
    fact[0] = 1;
    for (int i = 1; i < N; i++) fact[i] = fact[i-1] * i % Mod;
    for (int i = 0; i < N; i++) inv[i] = mod_pow(fact[i], Mod - 2);
}

ll C(int n, int m) {
    if (m < 0 || m > n) return 0;
    return fact[n] * inv[n-m] % Mod * inv[m] % Mod;
}

ll get(int n, int seg) {
    if (n == 0 && seg == 0) return 1;
    return C(n-1, seg-1);
}

ll calc(int n, int last, int occs[2][2]) {
    int c[2][2];
    for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++)
        c[i][j] = last == 1 ? occs[1-i][1-j] : occs[i][j];

    if (c[0][0] + c[0][1] + c[1][0] + c[1][1] != n) return 0;

    
    int seg[2] = {c[1][0] + 1, c[0][1]}, cnt[2] = {c[0][0]+c[1][0]+1, c[0][1]+c[1][1]};

    if (seg[0] != seg[1] && seg[0] != seg[1] + 1) return 0;

    for (int i = 0; i < 2; i++) {
        printf("cnt, seg: %d %d\n", cnt[i], seg[i]);
    }

    return get(cnt[0], seg[0]) * get(cnt[1], seg[1])% Mod;
}

int occs[2][2];

ll solve(char *s) {
    int n = strlen(s);
    if (occs[0][0] + occs[0][1] + occs[1][0] + occs[1][1] == 0) return 1;
    ll res = 0;
    for (int i = 1; i <= n - 1; i++) add(res, calc(i, 1, occs));
    int c[2][2] = {0};
    for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++)
        c[i][j] = occs[i][j];
    
    for (int i = 1; i < )


    return res;
}

bool test(char *s) {
    int n = strlen(s);
    int c[2][2] = {0};
    for (int i = 0; i < n - 1; i++) {
        c[s[i]-'0'][s[i+1]-'0']++;
    }
    for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++)
        if (c[i][j] != occs[i][j]) return false;
    return true;
}

char s[2][N];

int main() {
    init();

    scanf("%s%s", s[0], s[1]);
    for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++) 
        scanf("%d", &occs[i][j]);

/*    int n, last;
    int c[2][2];
    scanf("%d%d", &n, &last);
    for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++)
        scanf("%d", &c[i][j]);

    printf("%lld\n", calc(n, last, c));*/

    ll ans = (solve(s[1]) - solve(s[0])) % Mod;

    ans += test(s[1]);

    ans = (ans + Mod) % Mod;

    printf("%lld\n", ans);
}