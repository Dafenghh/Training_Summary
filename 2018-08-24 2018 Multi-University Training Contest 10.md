# 2018 Multi-University Training Contest 10
Date: 2018-08-24

## Practice Link
https://vjudge.net/contest/248150

## 流水账
开场，赛波过了高精度签到题H。之后达烽做G(容斥)，立辉做L(费用流)。立辉L抄完模板后WA了。达烽推错了公式，卡了很久很久，到2h30min才过了G。之后立辉发现I是水题，达烽发现J是水题，数分钟后连过两道。之后立辉敲了一发暴力构图，过了L。3h57min立辉过了E。随后赛波和立辉想C，达烽想D。都没搞出来。
## 个人总结
### 徐达烽
今天这场就打得很糟糕了，首先签到性质的G搞了这么久，实在不应该。另外大水题J应该早点发现早点过的。（Claris所说读新题优先级高于一切）D的DP差最后一步就想出正解了，超伤心的。

## 要补的题+题解
### D题
很好的一道DP题。对一个排列a,设它与标准排列的曼哈顿距离为s，对所有s,求排列数。

 |1|2|3|4|
 |-|-|-|-|
 |?|?|?|?|
 
 我们在第二行填入1..n。填完之后，把绝对值拆开，每一列的数一正一负，例如：
 
 |-1|-2|+3|+4|
 |--|--|--|--|
 |+2|+4|-3|-1|
 
 事实上，只需要知道取负的数（即同一列中较小的数）的和，就能算得全部的和。
 
 再发现，第二行中，对任意一个数x，当它在前x列则取正，否则取负。
 
 `f[i][j][s]`表示前i列中，有j个空白位置（未填），取负的数的和为s的方案数。其实1..i中，没有用过的数也是j个。
根据a[i]填什么数，i放哪个位置来讨论，从而写出转移。
```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 105;
int f[2][N][N*N], r[2][N], ans[N*N];
int n,Mod;
void add(int &a, ll b) {
    a = (a + b) % Mod;
}
void init(int i) {
    int now = i & 1;
    for (int j = 0; j <= i; j++) {
        for (int s = 0; s <= r[now][j]; s++) 
            f[now][j][s] = 0;
        r[now][j] = 0;
    }
}
void Maxi(int &a, int b) {
    if (b > a) a = b;
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &Mod);      
        memset(f,0,sizeof f);
        memset(r,0,sizeof r);
        f[0][0][0] = 1;
        for (int i = 0; i < n; i++) {
            int now = i & 1;
            int x = i + 1;
            init(i+1);
            for (int j = 0; j <= i; j++)
            for (int s = 0; s <= r[now][j]; s++) {
                if (f[now][j][s] == 0) continue;
                add(f[now^1][j][s+x], (1LL + 2 * j)*f[now][j][s]);
                Maxi(r[now^1][j], s + x);
                add(f[now^1][j+1][s+2*x], f[now][j][s]);
                Maxi(r[now^1][j+1], s + 2 * x);
                if (j > 0) {
                    add(f[now^1][j-1][s], 1LL*j*j*f[now][j][s]);
                    Maxi(r[now^1][j-1],s);
                }
            }                
        }
        for (int s = 0; s <= n * (n + 1) / 2; s++)
            ans[n*(n+1) - 2 * s] = f[n&1][0][s];
        for (int i = 0; i < n * n; i++)
            printf("%d%c", ans[i], " \n"[i==n*n-1]);
    }
}
```
 
 

### C题
待补
### K题
待补
### A题

