#include<bits/stdc++.h>
using namespace std;

int main() {
    int n = 100000;
    std::random_device rd;  // 将用于为随机数引擎获得种子
    std::mt19937 gen(rd()); // 以播种标准 mersenne_twister_engine
    std::uniform_int_distribution<> dis(-n, n);
    
    printf("%d\n", n);
    for (int i = 0; i < n; i++) printf("%d%c", dis(gen), " \n"[i==n-1]);
    for (int i = 2; i <= n; i++) printf("%d %d\n", 1, i);
    int q = 20;
    printf("%d\n", q);
    for (int i = 0; i < q; i++) printf("%d\n", 1);
}