#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
ll trans(const string &s) {
    ll res = 1;
    for (char c: s) {
        res = res * 10 + c - '0';
    }
    return res;
}
 
unordered_map<ll, int> M;
 
const int N = 6e5+10;
 
struct Node{
    ll key;
    int data,prev,next;
}a[N];
 
int tot = 0, q,m;
 
void Remove(int pos) {
    int prev = a[pos].prev, next = a[pos].next;
    a[prev].next = next;
    a[next].prev = prev;
}
 
void Insert(int x, int pos) { // insert to [pos-1, pos]
    int prev = a[pos].prev;
    a[prev].next = x;
    a[x].prev = prev;
 
    a[pos].prev = x;
    a[x].next = pos;
}
int op, v, cnt;
char s[20];
 
int access() {
    ll key = trans(s);
    if (M.count(key)) {
        int pos = M[key];
        Remove(pos);
        Insert(pos, 0);
        return a[pos].data;
    }
    else {
        int pos = ++tot;
        M[key] = pos;
        a[pos].data = v;
        a[pos].key = key;
        Insert(pos, 0);
        ++cnt;
        if (cnt > m) {
            int x = a[0].next;
            Remove(x);
            M.erase(a[x].key);
            --cnt;
        }
 
        return v;
    }
}
 
void answer() {
    ll key = trans(s);
    if (!M.count(key)) {
        puts("Invalid");
        return;
    }
 
    int pos = M[key];
    if (v == 0) {
        printf("%d\n", a[pos].data);
    }
    else {
        int x = (v == -1 ? a[pos].prev : a[pos].next);
        if (x == 0) puts("Invalid");
        else printf("%d\n", a[x].data);
    }
}
 
 
void solve() {
    cnt = 0;
    tot = 0;
    a[0].prev = a[0].next = 0;
    M.clear();
    scanf("%d%d", &q, &m);
    while (q--) {      
        scanf("%d%s%d", &op, s, &v);
 
     //   cout << ": " << q << endl;
 
        if (op == 0) printf("%d\n",access());
        else answer();
    }
 
}
 
 
 
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
}
