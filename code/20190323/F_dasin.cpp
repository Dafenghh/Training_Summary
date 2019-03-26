#include <bits/stdc++.h>
using namespace std;

int main() {
	int n; cin >> n;
	vector<string> a(n);
	int maxLen = 1;
	int sumLen = 0;
	for (string &s : a) {
		cin >> s;
		maxLen = max(maxLen, (int)s.size());
		sumLen += s.size();
	}
	pair<int, int> ans = make_pair(0, 0);
	vector<pair<int, int> > space;
	vector<int> f(n), ban(n);
	for (int width = maxLen; width <= sumLen + n; width++) {
		int curRow = 0;
		int curCol = 0;
		space.clear();
		fill(ban.begin(), ban.end(), 0);
		for (string &s : a) {
			curCol += s.size();
			if (curCol > width) {
				curRow++;
				curCol = s.size();
				if (space.size()) ban[(int)space.size() - 1] = 1;
			}
			if (curCol < width) {
				curCol++;
			}
			space.emplace_back(curRow, curCol);
		}
		ban[(int)space.size() - 1] = 1;
		int res = 0;
		fill(f.begin(), f.end(), 0);
		for (int i = 0, j = 0; i < space.size(); i++) {
			for (; space[j].first < space[i].first - 1 || (
					space[j].first == space[i].first - 1 && 
					space[j].second < space[i].second - 1); j++);
			if (ban[i]) continue;
			int k = j;
			for (; space[k].first == space[i].first - 1 && 
					space[k].second <= space[i].second + 1; k++) {
				if (!ban[k]) f[i] = max(f[i], f[k]);		
			}
			f[i]++;
			res = max(res, f[i]);
		}
		ans = max(ans, make_pair(res, -width));
	}
	cout << -ans.second << " " << ans.first << endl;
	return 0;
}
