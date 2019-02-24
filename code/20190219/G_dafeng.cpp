#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+10;
const int K = 26;
char s[N];
int n, q, lst[N][K], nxt[N][K], f[N][K], sum[N], mem[K+1];

int calc(int l, int r, int c, bool INIT) {
	if (l >= r) return 0;
	if (mem[c] != -1) return mem[c];
	int mask = 0;
	for (int j = 0; j < K; j++) {
		int fi = nxt[l][j], la = lst[r-1][j];
		if (fi >= r) continue;
		mask |= 1 << (sum[fi]^sum[la]^(INIT ? calc(l, fi, j, 1)^f[la+1][c] : f[l][j]^calc(la+1, r, j, 0))); 
	}
	int t = 0;
	while (mask>>t&1) t++;
	return mem[c] = t;
}

int main() {
	scanf("%s%d", s+1, &q);	
	n = strlen(s+1);
	for (int i = 1; i <= n; i++) 
		for (int j = 0; j < K; j++) 
			lst[i][j] = s[i] == 'a' + j ? i : lst[i-1][j];	
	for (int j = 0; j < K; j++) nxt[n+1][j] = n+1;
	for (int i = n; i >= 1; i--) {
		for (int j = 0; j < K; j++) {
			nxt[i][j] = s[i] == 'a' + j ? i : nxt[i+1][j];
		}
		int c = s[i] - 'a';
		sum[i] = sum[nxt[i+1][c]] ^ f[i+1][c];
		memset(mem, -1, sizeof mem);
		for (int j = 0; j < K; j++)
			f[i][j] = calc(i, nxt[i][j], j, 1);
	}
	while (q--) {
		int l,r;
		scanf("%d%d", &l, &r);
		memset(mem, -1, sizeof mem);
		puts(calc(l, r+1, K, 0) > 0 ? "Alice" : "Bob");
	}
}