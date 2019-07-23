#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct P {
    int x,y;
    P():x(0), y(0){}
    P(int x, int y):x(x), y(y) {}
    P operator-(const P&b) const {
        return P(x-b.x, y-b.y);
    }

    ll det(const P&b)const {
        return 1LL*x*b.y-1LL*y*b.x;
    }

    ll dot(const P&b) const {
        return 1LL*x*b.x + 1LL*y*b.y;
    }
    int half() const {
        if (y > 0) return 0;
        if (y < 0) return 1;
        if (x > 0) return 0;
        return 1;
    }

    bool operator < (const P&b) const {
        int h1 = half(), h2 = b.half();
        return h1 < h2 || h1 == h2 && det(b) > 0;
    }

    bool operator == (const P&b) const {
        return half() == b.half() && det(b) == 0;
    }

};
const int N = 220;
int X[N], Y[N], Label[N], n, id[N], sz;
P a[N];

int cnt[3];

bool valid(const P&a, const P&b) {
    return a.det(b) > 0 || a.det(b) == 0 && a.dot(b) < 0;
}

int test(int base) {
    sz = 0;

    for (int i = 0; i < n; i++) {
        if (i == base) continue;
        if (X[i] == X[base] && Y[i] == Y[base]) {
            if (Label[i] == Label[base]) continue;
            else return -1;
        }
        a[i] = P(X[i], Y[i]) - P(X[base], Y[base]);
        id[sz++] = i;
    }


  //  printf("base=%d, sz=%d\n", base, sz);
    sort(id, id+sz, [&](int i, int j) {
        return a[i] < a[j];
    });

    for (int i = 0, j = 1; i < sz; i = j) {
        while (j < sz && a[id[i]] == a[id[j]]) {
            if (Label[id[j]] != Label[id[i]]) return -1;
            ++j;
        } 
    }

    for (int i = 0; i < sz; i++) {
       // printf("%d %d %d: %d %d %d\n", X[base], Y[base],i, X[id[i]], Y[id[i]], Label[id[i]]);
    }


    for (int i = 0; i < sz; i++) id[i+sz] = id[i];

    for (int i = 0, j = 0, j2 =0; i < sz; i++) {
        if (Label[id[i]] == Label[base]) {
            if (j <= i) j = i + 1;

            while (j < 2 * sz && Label[id[j]] == Label[base] && valid(a[id[i]], a[id[j]])) {
                ++j;
            }
          //  printf("%d: %d\n", i, j);
            if (j-i+1==cnt[Label[base]+1]) return 1;
        }
        else {
            if (j2 <= i) j2 = i+1;
             while (j2 < 2 * sz && Label[id[j2]] != Label[base] && valid(a[id[i]], a[id[j2]])) {
                ++j2;
            }
           // printf("%d: %d\n", i, j2);
            if (j2-i==cnt[2-(Label[base]+1)]) return 1;           
        }
    }
    return 0;
}


void solve() {
    memset(cnt, 0, sizeof cnt);

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d", X+i, Y+i, Label+i);
        cnt[Label[i] + 1]++;
    }

    if (n == 1) {
        puts("Successful!");
            return;
    }
    

    for (int i = 0; i < n; i++) {
        int ans= test(i);
        if (ans == 1) {
            puts("Successful!");
            return;
        }
        else if (ans == -1) {
            puts("Infinite loop!");
            return;
        }
    }
    puts("Infinite loop!");
}


int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
}
