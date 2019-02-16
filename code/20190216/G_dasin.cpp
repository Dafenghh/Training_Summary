#include <bits/stdc++.h>
using namespace std;
const int maxn = 100005;
const int maxm = 7000000;
const int inf = 1e9;
int n, K;
template<typename T>
int get(const vector<T>& a, T x) {
  return (int)(lower_bound(a.begin(), a.end(), x) - a.begin());
}
template<typename T>
int _get(const vector<T>& a, T x) {
  return (int)(upper_bound(a.begin(), a.end(), x) - a.begin()) - 1;
}
int tot, val[maxm], son[maxm][2];
int ins(int p, int l, int r, int y) {
  int x = ++tot;
  val[x] = val[y] + 1;
  if (l == r) return x;
  int mid = l + r >> 1;
  if (p <= mid){
    son[x][0] = ins(p, l, mid, son[y][0]);
    son[x][1] = son[y][1];
  } else {
    son[x][0] = son[y][0]; 
    son[x][1] = ins(p, mid + 1, r, son[y][1]);
  }
  return x;
}
int L, R;
int ask(int l, int r, int x, int y) {
  // printf("ask %d %d %d %d %d %d\n", L, R, l, r, x ,y);
  if (L > R || val[y] == 0) return 0;
  if (l >= L && r <= R) {
    return val[y] - val[x];
  }
  int mid = l + r >> 1, res = 0;
  if (L <= mid) res += ask(l, mid, son[x][0], son[y][0]);
  if (R > mid) res += ask(mid + 1, r, son[x][1], son[y][1]);
  return res;
}
template<typename T>
void fit(vector<T>& a) {
  a.resize(unique(a.begin(), a.end()) - a.begin());
}
int x[maxn], r[maxn], q[maxn];
vector<int> B[maxn][2], root[maxn][2];
vector<pair<int, int> > bin[maxn];
int main() {
//freopen("aa.in", "r", stdin);
  scanf("%d%d", &n, &K);
  vector<int> Q;
  for (int i = 1; i <= n; i++) {
    scanf("%d%d%d", x + i, r + i, q + i);
    Q.push_back(q[i]);
  }
  sort(Q.begin(), Q.end());
  fit(Q);
  for (int i = 1; i <= n; i++) {
    int _q = get(Q, q[i]);
    bin[_q].push_back(make_pair(x[i], r[i]));
  }
  for (int _q = 0; _q < Q.size(); _q++) {
    if (bin[_q].size() == 0) continue;
    sort(bin[_q].begin(), bin[_q].end());
    for (auto it : bin[_q]) {
      B[_q][0].push_back(min(it.first + it.second, inf));
      B[_q][1].push_back(max(it.first - it.second, 0));
    }
    sort(B[_q][0].begin(), B[_q][0].end());
    // fit(B[_q][0]);
    sort(B[_q][1].begin(), B[_q][1].end());
    // fit(B[_q][1]);
    for (int i = 0; i < bin[_q].size(); i++) {
      auto& pr = bin[_q][i];
      root[_q][0].push_back(ins(get(B[_q][0], pr.first + pr.second), 0, B[_q][0].size() - 1, i ? root[_q][0][i - 1] : 0));
      root[_q][1].push_back(ins(get(B[_q][1], pr.first - pr.second), 0, B[_q][1].size() - 1, i ? root[_q][1][i - 1] : 0));
    }
  }
  long long ans = 0, offset = 0;
  for (int i = 1; i <= n; i++) {
    int ql = max(0, get(Q, q[i] - K));
    int qr = _get(Q, q[i]);
    // printf("ql %d %d\n", ql, qr);
    for (int j = ql; j <= qr; j++) {
      // printf("ij %d %d\n", i ,j);
      int res = 0;
      int l1 = get(bin[j], make_pair(x[i] - r[i], 0));
      int r1 = _get(bin[j], make_pair(x[i] - 1, inf));
      // printf("sz1 %d %d %d\n", B[j][0].size(), l1,r1);
      if (l1 <= r1) {
        l1 = max(l1, 0);
        r1 = min(r1, (int)B[j][0].size() - 1);
        L = get(B[j][0], x[i]);
        R = B[j][0].size()-1;
        res += ask(0, B[j][0].size()-1, l1?root[j][0][l1-1]:0, root[j][0][r1]);
      }
      int l2 = get(bin[j], make_pair(x[i], 0));
      int r2 = _get(bin[j], make_pair(x[i] + r[i], inf));
      // printf("sz2 %d %d %d\n", B[j][1].size(), l2, r2);
      if (l2 <= r2) {
        l2 = max(l2, 0);
        r2 = min(r2, (int)B[j][1].size() - 1);
        L = 0;
        R = _get(B[j][1], x[i]);
        res += ask(0, B[j][1].size()-1, l2?root[j][1][l2-1]:0, root[j][1][r2]);
      }
      if (j == qr) {
        offset += res - 1;
      } else {
        ans += res;
      }
    }
  }
  assert(offset % 2 == 0);
  ans += offset / 2;
  printf("%lld\n", ans);
  return 0;
}