#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
void solve() {
    ll x;
    scanf("%lld", &x);
    if (x % 3 == 0) {
        printf("1 %lld\n", x);
        return;
 
    }
 
    vector<ll> num[2];
    for (int i = 0; i < 63; ++i) {
        if (x >> i & 1) num[i&1].push_back(1LL<<i);
    }
 
    int t = (x%3==1?0:1);
    
        if (!num[t].empty()) {
            ll y = num[t][0]^x, z = num[t][0];
            if (num[t].size() >= 3) {
                z ^= num[t][1];
                z ^= num[t][2];
            }
            else {
                assert(!num[t^1].empty());
                z ^= num[t^1][0];
            }
            assert(y%3==0&&z%3==0&&(y|z)==x);
            printf("2 %lld %lld\n", y, z);
        }
        else {
            assert(num[t^1].size() >= 3);
            ll y = x^num[t^1][0]^num[t^1][1], z = num[t^1][0]^num[t^1][1]^num[t^1][2];
            printf("2 %lld %lld\n", y, z);
        }
     
     
 
}
 
 
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
}
