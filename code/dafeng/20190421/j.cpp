#include <bits/stdc++.h>
using namespace std;
const int N = 22;
const int W1 = 16;
const int W2 = 17;
char s[10];
int n;
int trans(const string&s) {
    if (s == "W1") return W1;
    if (s == "W2") return W2;
    if (s == "J") return 11;
    if (s == "Q") return 12;
    if (s == "K") return 13;
    if (s == "A") return 14;
    if (s == "2") return 15;
    if (s == "10") return 10;
    int x = s[0] - '0';
    assert(s.size() == 1 && x >= 3 && x <= 9);
    return x;
}

vector<int> v;
bool Single() {
    return v.size() == 1;
}

bool Pair() {
    return v.size() == 2 && v[0] == v[1];
}

bool Triple() {
    return v.size() == 3 && v[0] == v[1] && v[1] == v[2];
}

bool Straight(const vector<int> &v) {
    for (int i = 1; i < v.size(); i++) {
        if (v[i] != v[0] + i) return false;
    }
    return v.back() <= 14;
} 

bool PairStraight() {
    if (n % 2 != 0) return false;
    for (int i = 0; i < n / 2; i++) {
        if (v[2*i] != v[0] + i || v[2*i+1] != v[2*i]) return false;
    }
    return v.back() <= 14;
}

bool TripleStraight() {
    if (n % 3 != 0) return false;
    for (int i = 0; i < n / 3; i++) {
        if (v[3*i] != v[0] + i || v[3*i+1] != v[3*i]
                               || v[3*i+2] != v[3*i]) return false;
    }
    return v.back() <= 14;
}

map<int,int> M;
typedef pair<int,int> P;
vector<P> cnt;
bool TripleSingle() {
    return cnt.size() == 2 && cnt[0].first == 1 && cnt[1].first == 3;
}
bool TriplePair() {
    return cnt.size() == 2 && cnt[0].first == 2 && cnt[1].first == 3;
}
bool Airplane1() {
    if (n%4 != 0) return false;
    int w=n/4;
    vector<int> st;
    for (const auto&p: cnt) {
        if (p.first >= 3 && p.second != 15) st.push_back(p.second);
    }
    sort(st.begin(), st.end());
    if (st.empty()) return false;
    int c = 1;
    int mx = 1;
    for (int i = 1; i < st.size(); i++) {
        if (st[i] != st[i-1] + 1) {
            c = 1;
        }
        else {
            c++;
        }
        mx = max(mx, c);
    }
    return mx >= w;
}

bool Airplane2() {
    vector<int> st;
    int rest = 0;
    for (const auto&p: cnt) {
        if (p.first == 3) st.push_back(p.second);
        else if (p.first == 2) rest++;
        else if (p.first == 4) rest+=2;
        else return false;
    }
    return st.size() >= 2 && Straight(st) && rest == st.size();
}

bool Bomb() {
    return cnt.size() == 1 && cnt[0].first == 4;
}

bool Rocket() {
    vector<int> tar{W1, W2};
    return v == tar;
}

bool Quartet() {
    vector<int> st;
    int rest = 0;
    for (const auto&p: cnt) {
        if (p.first == 4) st.push_back(p.second);
        else rest += p.first;
    }
    return st.size() == 1 && rest == 2;
}

bool solve() {
    v.clear();
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", s);
        string card(s);
        v.push_back(trans(card));
    }
    sort(v.begin(), v.end());
    M.clear();
    for (auto x: v) M[x]++;
    cnt.clear();
    for (auto i:M) {
        cnt.push_back(P(i.second, i.first));
    }
    sort(cnt.begin(), cnt.end());

  //  printf("%d %d %d %d %d %d %d %d %d %d %d %d %d\n", Single(),Pair(), Triple(), n >= 5 && Straight(v),n >= 6 && PairStraight(), TripleStraight(),
 //           TripleSingle() , TriplePair() , Airplane1(), Airplane2() , Bomb() , Rocket() ,Quartet() );


    return Single() || Pair() || Triple() || n >= 5 && Straight(v) || n >= 6 && PairStraight() || TripleStraight() ||
            TripleSingle() || TriplePair() || Airplane1() || Airplane2() || Bomb() || Rocket() || Quartet(); 
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        puts(solve()?"Ye5":"N0");
    }
}