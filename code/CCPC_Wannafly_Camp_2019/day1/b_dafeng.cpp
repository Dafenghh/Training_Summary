#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const ll INF = 1e18;
const int N = 100;
int tot;
void Mini(ll &a, ll b) {
    if (b < a) a = b;
}
void Maxi(ll &a, ll b) {
    if (a < b) a = b;
}
struct Mat{
    ll a[N][N];
    Mat() {
        for (int i = 0; i < tot; i++)
        for (int j = 0; j < tot; j++)
            a[i][j] = (i == j ? 0 : -INF);

        
    }
    ll* operator[](int i) {
        return a[i];
    }
    const ll* operator[](int i)const{
        return a[i];
    }
    Mat operator*(const Mat&b) const{
        Mat c;
        for (int i = 0; i < tot; i++)
        for (int j = 0; j < tot; j++)
        for (int k = 0; k < tot; k++) 
            Maxi(c[i][j], min(INF,a[i][k]+b[k][j]));
        return c;
    }
};

int n,m,T[10][10],st,ed;
ll C;
const int cycle = 2520;

int getid(int x, int y) {
    return x * m + y;
}

ll dp[cycle+1][N][N];
int d[5][2] = {{0, 0}, {0, -1}, {0, 1}, {1, 0}, {-1, 0}};

bool isvalid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}
Mat A[55];

void solve() {
    
    for (int i = 0; i < tot; i++) 
    for (int j = 0; j < tot; j++)
        A[0][i][j] = dp[cycle][i][j];

    for (int i = 1; i < 55; i++) A[i] = A[i-1] * A[i-1];

    Mat mat;
    ull cnt = 0;
    for (int i = 54; i >= 0; i--) {
        Mat next_mat = mat * A[i];
        if (next_mat[st][ed] < C) mat = next_mat, cnt += 1LL << i;
    }

    cnt *= (ull)cycle;
    for (ull t = 1; t <= (ull)cycle; t++)
    for (int i = 0; i < tot; i++) {
        if (mat[st][i] + dp[t][i][ed] >= C) {
            cout << cnt + t << endl;
            return;
        }
    }
    assert(0);
    cout << "FAIL" << endl;
}

int main(){
    cin >> n >> m >> C;
    tot = n * m;
    for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
        cin >> T[i][j];
    int sx,sy,tx,ty;
    cin >> sx >> sy >> tx >> ty;
    st = getid(sx-1, sy-1), ed = getid(tx-1, ty-1);

    for (int t = 0; t <= cycle; t++)
    for (int i = 0; i < tot; i++)
    for (int j = 0; j < tot; j++) {
        dp[t][i][j] = -INF;
    }

    for (int i = 0; i < tot; i++) dp[0][i][i] = 0;

    for (int t = 0; t < cycle; t++)
    for (int i = 0; i < tot; i++)
    for (int x = 0; x < n; x++)
    for (int y = 0; y < m; y++) {
        for (int k = 0; k < 5; k++) {
            int nx = x + d[k][0], ny = y + d[k][1];
            if (isvalid(nx, ny)) {
                Maxi(dp[t+1][i][getid(nx, ny)], dp[t][i][getid(x, y)] + ((t+1) % T[nx][ny] == 0));
            }
        }
    }


    for (int t = 1; t <= cycle; t++) 
        if (dp[t][st][ed] >= C) return cout << t << endl, 0;
    
    solve();
}