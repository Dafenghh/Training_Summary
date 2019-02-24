#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 6;
const int K = 3;
const int B[K] = {59, 43, 67};
unsigned long long f[K][maxn], pw[K][maxn];
int main() {
  //freopen("aa.in", "r", stdin);
  string s, t;
  cin >> s >> t;
  for (char& c : s) c -= '0';
  for (char& c : t) c -= 'a';
  vector<int> cnt(2);
  for (char c : s) cnt[c]++;
  int w = cnt[0] < cnt[1] ? 0 : 1;
  vector<int> len(2);
  int ans = 0;
  for (int i = 0; i < K; i++) pw[i][0] = 1;\
  for (int i = 1; i <= t.size(); i++) {
    for (int j = 0; j < K; j++) {
      pw[j][i] = pw[j][i - 1] * B[j];
      f[j][i] = f[j][i - 1] * B[j] + t[i - 1] + 1;
    }
  }
  auto get_hash = [&](int l, int r) {
    l++, r++;
    return make_pair(f[0][r] - f[0][l - 1] * pw[0][r - l + 1],
                    make_pair(f[1][r] - f[1][l - 1] * pw[1][r - l + 1],
                              f[2][r] - f[2][l - 1] * pw[2][r - l + 1]
                            ));
  };
  for (len[w] = 1; len[w] * cnt[w] < t.size(); len[w]++) {
    if ((t.size() - len[w] * cnt[w]) % cnt[1-w]) continue;
    len[1-w] = (t.size() - len[w] * cnt[w]) / cnt[1-w];
    if (len[1-w] == 0) continue;
    vector<int> st(2, -1);
    auto comp = [&](int x, int y, int d) {
      return get_hash(x, x + d - 1) == get_hash(y, y + d - 1);
    };
    int ok = 1;
    for (int i = 0, j = 0; i < s.size(); i++) {
      if (~st[s[i]]) {
        if (!comp(st[s[i]], j, len[s[i]])) {
          ok = 0; break;
        }
      } else {
        st[s[i]] = j;
      }
      j += len[s[i]];
    }
    if (ok && len[0] == len[1] && comp(st[0], st[1], len[0])) {
      ok = 0;
    }
    ans += ok;
  }
  cout << ans << endl;
  return 0;
}