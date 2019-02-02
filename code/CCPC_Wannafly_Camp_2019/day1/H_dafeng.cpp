#include <bits/stdc++.h>
using namespace std;
const int N = 105;

vector<int> dp[N][N][N];
int a[N], nums[N], sz;
int rangeMin[N][N];

int n,k;

void Maxi(int &a, int b) {
    if (a < b) a = b;
}

void merge(vector<int> &f, const vector<int> &g) {
    for (int i = k; i >= 1; i--)
    for (int j = 0; j < i; j++) {
        Maxi(f[i], f[j] + g[i-j]);
    }
}

void print(vector<int> v) {
    for (int i = 1; i <= k; i++) printf("%d ", v[i]);
    puts("");
}

vector<int> f(int l, int r, int h) {
    if (!dp[l][r][h].empty()) return dp[l][r][h];
    vector<int> g(k+1, 0), g_cut(k+1, 0);
    int last = l - 1, Min = rangeMin[l][r];
    for (int i = l; i <= r; i++) {
        if (a[i] != rangeMin[l][r]) continue;

        if (i-1 >= last+1) {
            merge(g, f(last+1, i-1, h));
            merge(g_cut, f(last+1, i-1, Min));
        }
        last = i;
    }

    if (last < r) {
        merge(g, f(last+1, r, h));
        merge(g_cut, f(last+1, r, Min));
    }

    int profit = (r-l+1) * (nums[Min]-nums[h]);
    for (int i = 1; i <= k; i++) {
        
        Maxi(g[i], g_cut[i-1]+profit);
        Maxi(g[i], g[i-1]);
    }

    return dp[l][r][h] = g;
}

int main() {
    scanf("%d%d", &n, &k);
    sz = 1;
    for (int i = 0; i < n; i++) {
        scanf("%d", a + i);
        nums[sz++] = a[i];
    }
    sort(nums, nums+sz);
    sz = unique(nums, nums+sz) - nums;
    for (int i = 0; i < n; i++) {
        a[i] = lower_bound(nums, nums+sz, a[i]) - nums;
    }

    for (int i = 0; i < n; i++) {
        rangeMin[i][i] = a[i];
        for (int j = i + 1; j < n; j++) rangeMin[i][j] = min(rangeMin[i][j-1], a[j]);
    }

    vector<int> ans = f(0,n-1,0);
    printf("%d\n", ans[k]);
}
