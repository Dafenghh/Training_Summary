#include <bits/stdc++.h>
using namespace std;
const int N = 502;

int n;
double p[6][6], first[6][N][N], never[6][N][N], pos[6][N][7][N];

void solve(double p[], double first[N][N], double never[N][N], double pos[N][7][N]) {
    for (int j = 0; j <= 6; j++) pos[0][j][0] = 1;

    for (int i = 0; i <= 500; i++)
    for (int j = 0; j <= 6; j++)
    for (int k = 0; k < n; k++) {
        never[i][j] += pos[i][j][k];
        for (int t = 0; t < 6; t++) {
            int nk = (k+t+1)%n;
            if (nk == j) first[i+1][j] += pos[i][j][k] * p[t];
            else pos[i+1][j][nk] += pos[i][j][k] * p[t];
        }
    }

    for (int k = 0; k < n; k++) never[0][k] = 1;

    for (int i = 1; i <= 500; i++)
    for (int j = 7; j < n; j++) 
    for (int t = 0; t < 6; t++) {
        first[i][j] += p[t] * first[i-1][j-t-1];
        never[i][j] += p[t] * never[i-1][j-t-1];
    }
}

double ans[6];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < 6; i++)
    for (int j = 0; j < 6; j++)
        scanf("%lf", &p[i][j]);

    for (int i = 0; i < 6; i++) solve(p[i], first[i], never[i], pos[i]);

    for (int i = 0; i < 6; i++)
    for (int j = 1; j <= 500; j++)
    for (int k = 0; k < n; k++) {
        double prob = first[i][j][k];
        for (int t = 0; t < i; t++) prob *= never[t][j][k];
        for (int t = i+1; t < 6; t++) prob *= never[t][j-1][k];
        ans[i] += prob;
    }
    for (int i = 0; i < 6; i++) printf("%.3lf\n", ans[i]); 
}