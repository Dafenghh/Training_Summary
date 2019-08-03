#include <bits/stdc++.h>
using namespace std;
const int N = 50050;
const int M = 10;
const int Mod = 1e9+7;
typedef long long ll;
void add(int &a, ll b) {
    a = (a+b)%Mod; 
}
int n,m,q, b[N][M];
 
struct Mat {
    int a[M][M];
    Mat() {
        for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
            a[i][j] = 0;
    }
    static Mat Ident() {
        Mat res;
        for (int i = 0; i < m; i++) res[i][i] = 1;
        return res;
    }
    int* operator[](int x) {
        return a[x];
    }
     
    const int* operator[](int x)const {
        return a[x];
    }
         
    Mat operator*(const Mat&b)const{
        Mat c;
        for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++) {
            if (a[i][j] == 0) continue;
            for (int k = 0; k < m; k++) add(c[i][k], 1LL*a[i][j]*b[j][k]);  
        }
        return c;
    }  
};
 
Mat dat[N*4];
 
 
void build(int v = 0, int l = 1, int r = n+1) {
    if (l + 1 == r) {
        dat[v] = Mat();
        for (int i = 0; i < m; i++) {
            for (int j = i; j < m && b[l][j] == 0;   j++) dat[v][i][j] = 1;
            for (int j = i; j >= 0 && b[l][j] == 0; j--) dat[v][i][j] = 1;  
        }
    }
    else {
        int mid = (l + r) / 2, chl = v * 2 + 1, chr = v * 2 + 2;
        build(chl, l, mid);
        build(chr, mid, r);
        dat[v] = dat[chl] * dat[chr];
    }
}
/*
vector<int> ans;
 
void query(int L, int R, int v = 0, int l = 1, int r = n+1) {
    if (R <= l || r <= L) return;
    if (L <= l && r <= R) {
        assert(ans.size() == m);
        vector<int> new_ans(m, 0);
        for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
            add(new_ans[j], 1LL * ans[i] * dat[v][i][j]);
        return;
    }
     
    int mid = (l + r) / 2, chl = v * 2 + 1, chr = v * 2 + 2;
    query(L, R, chl, l, mid);
    query(L, R, chr, mid, r);
}
*/
 
void update(int x, int v = 0, int l = 1, int r = n + 1) {
    if (l + 1 == r) {
        dat[v] = Mat();
        for (int i = 0; i < m; i++) {
            for (int j = i; j < m && b[l][j] == 0;   j++) dat[v][i][j] = 1;
            for (int j = i; j >= 0 && b[l][j] == 0; j--) dat[v][i][j] = 1;  
        }      
        return;
    }
    int mid = (l + r) / 2, chl = v * 2 + 1, chr = v * 2 + 2;
    if (x < mid) update(x, chl, l, mid);
    else update(x, chr, mid, r);
     
    dat[v] = dat[chl] * dat[chr];
}
 
int main() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++)
    for (int j = 0; j < m; j++) scanf("%1d", &b[i][j]);
     
    build();
     
    while (q--) {
        int op,x,y;
        scanf("%d%d%d", &op, &x, &y);
        if (op == 1) {
            b[x][y-1]  ^= 1;
            update(x); 
        }
        else {
            printf("%d\n", dat[0][x-1][y-1]);  
        }
     
    }
     
}
