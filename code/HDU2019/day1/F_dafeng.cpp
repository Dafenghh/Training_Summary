#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+10;
struct SAM {
    struct State {
        int link,len,next[26];
    };
    State st[N*2];
    int last,sz;
    void init() {
        last = sz = 1;
        memset(st, 0, sizeof st);
    }
    void extend(int c) {
        int cur = ++sz;
        st[cur].len = st[last].len + 1;
        int p = last;
        for (;p > 0 && !st[p].next[c]; p = st[p].link) {
            st[p].next[c] = cur;
        }
        if (p == 0) {
            st[cur].link = 1;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = ++sz;
                st[clone] = st[q];
                st[clone].len = st[p].len + 1;
                st[q].link = st[cur].link = clone;
                for (; p > 0 && st[p].next[c] == q; p = st[p].link) {
                    st[p].next[c] = clone;
                }
            }
        }
        last = cur;
    }
}sam;

char s[N];
typedef long long ll;
int pre[N];
ll ans[N];
void Mini(ll &a, ll b) {
    if (b < a) a = b;
}
int main() {
    ll p,q;
    while (scanf("%s%lld%lld", s+1, &p, &q) != EOF) {
        int n = strlen(s+1);
        sam.init();
        int cur = 1;
        for (int i = 1, j = 0; i <= n; i++) {
            while (j < i && !sam.st[cur].next[s[i]-'a']) {
                ++j;
                sam.extend(s[j]-'a');
                while (cur>1&&i-j-1<=sam.st[sam.st[cur].link].len) {
                    cur = sam.st[cur].link;   
                }
            }
            if (j < i) cur = sam.st[cur].next[s[i]-'a'];
            pre[i] = j;
        }

        for (int i = 1; i <= n; i++) {
            ans[i] = ans[i-1] + p;
            if (pre[i] < i) Mini(ans[i], ans[pre[i]] + q);
        }
        printf("%lld\n", ans[n]);
    }
}