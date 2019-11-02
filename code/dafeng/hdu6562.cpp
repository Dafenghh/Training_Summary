#include <bits/stdc++.h>
using namespace std;

const int N = 4e5+10;
const int M = 3;
const int Mod = 1e9+7;
typedef long long ll;
void add(int &a, ll b) {
    a = (a+b)%Mod;
}
struct Mat {
    int a[M][M];
    Mat() {
        memset(a, 0, sizeof a);
    }
    int * operator[](int x) {
        return a[x];
    }
    const int* operator[](int x)const{
        return a[x];
    }
    static Mat Ident() {
        Mat res;
        for (int i = 0; i < M; i++) res[i][i] = 1;
        return res;
    }
    Mat operator*(const Mat&b)const {
        Mat c;
        for (int i = 0; i < M; i++)
        for (int j = 0; j < M; j++)
        for (int k = 0; k < M; k++) {
            add(c[i][k], 1LL*a[i][j]*b[j][k]);
            //c[i][j] = (1LL*a[i][0]*b[0][j]+1LL*a[i][1]*b[1][j]+1LL*a[i][2]*b[2][j])%Mod;
        }
        return c;
    }
    Mat operator+(const Mat&b)const{
        Mat c;
        for (int i = 0; i < M; i++)
        for (int j = 0; j < M; j++)
            c[i][j] = (a[i][j]+b[i][j])%Mod;
        return c;
    }
};

struct node {
    Mat dat, tag; 
}T[N];
#define dat(v) T[v].dat
#define tag(v) T[v].tag
void add_val(int v, const Mat&m) {
   // printf("add val %d ", v); m.print();
    dat(v) = m * dat(v);
    tag(v) = m * tag(v);
}

void pushdown(int v) {
    int chl=v*2+1, chr=v*2+2;
    add_val(chl, tag(v));
    add_val(chr, tag(v));
    tag(v) = Mat::Ident();
}

void pushup(int v) {
    int chl=v*2+1, chr=v*2+2;
    dat(v) = dat(chl) + dat(chr);
}


int n;
void update(int L, int R, const Mat&m, int v = 0, int l = 1, int r = n+1) {
    if (R <= l || r <= L) return;
    if (L <= l && r <= R) {
      //  printf("update: "); m.print(l,r);
        add_val(v, m);
        return;
    }
    pushdown(v);
    int mid=(l+r)/2, chl=v*2+1, chr=v*2+2;
    update(L,R,m,chl,l,mid);
    update(L,R,m,chr,mid,r);
    pushup(v);
}

int query(int L, int R, int v = 0, int l = 1, int r = n+1) {
    if (R <= l || r <= L) return 0;
    if (L <= l && r <= R) {
       // dat(v).print(l,r);
        return (dat(v)[0][1]+dat(v)[0][2])%Mod;
    }
    pushdown(v);
    int mid=(l+r)/2, chl=v*2+1, chr=v*2+2;
    return (query(L,R,chl,l,mid)+query(L,R,chr,mid,r))%Mod;
}

void build(int v=0,int l=1, int r =n+1) {
    tag(v) = Mat::Ident();
    if (l+1==r) {
        dat(v)=Mat::Ident();
     //   dat(v).print(l,r);
    } else {
        int mid=(l+r)/2, chl=v*2+1, chr=v*2+2;
        build(chl,l,mid);
        build(chr,mid,r);
        pushup(v);
    }
}

Mat base[10];

void init() {
    for (int d=0; d<10; d++) {
        base[d][0][0]=10;
        base[d][0][1]=10*d;
        base[d][0][2]=d;
        base[d][1][1]=100;
        base[d][2][2]=1;
    }
}
char s[10];
void solve() {
    int q;
    scanf("%d%d", &n, &q);
    build();
    while (q--) {
        int l,r;
        scanf("%s%d%d", s, &l, &r);
        ++r;
        if (s[0]=='q') {
            printf("%d\n", query(l,r));
        } else {
            int d;
            scanf("%d", &d);
            update(l,r,base[d]);
        }
    }
}

int main() {
    init();
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++) {
        printf("Case %d:\n", i);
        solve();
    }
}
