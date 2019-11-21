#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+10;
struct Node {
    int rnd,sz,dat,ch[2], fa;
}T[N];
#define rnd(v) T[v].rnd
#define sz(v) T[v].sz
#define dat(v) T[v].dat
#define chl(v) T[v].ch[0]
#define chr(v) T[v].ch[1]
#define ch(v) T[v].ch
#define fa(v) T[v].fa

int tot;
int newnode(int num) {
    int x = ++tot;
    rnd(x) = rand();
    sz(x) = 1;
    dat(x) = num;
    fa(x) = 0;
    return x;
}

void update(int v) {
    sz(v) = 1+sz(chl(v))+sz(chr(v));
}
void setfa(int v, int f) {
    if (v!=0) fa(v) = f;
}

int merge(int x, int y) {
    if (!x || !y) return x+y;
    int w;
    if (rnd(x) < rnd(y)) {
        w = x;
        chr(x) = merge(chr(x), y);
        setfa(chr(x),x);
    } else {
        w = y;
        chl(y) = merge(x, chl(y));
        setfa(chl(y),y);
    }
    update(w);
    return w;
}

void split(int now, int k, int &x, int &y) {
    if (!now) x=y=0;
    else {
        if (sz(chl(now))>=k) {
            y=now,split(chl(now), k, x, chl(now));
            setfa(chl(now), now);
            setfa(x,0);
        } else {
            x=now,split(chr(now), k-sz(chl(now))-1, chr(now), y);
            setfa(chr(now), now);
            setfa(y,0);
        }
        update(now);
    }
}
int Next(int x) {
    if (chr(x) != 0) {
        x=chr(x);
        while (chl(x) != 0) x = chl(x);
    } else {
        while (x==chr(fa(x))) x = fa(x);
        x = fa(x);
    }
    return x;
}


int main() {

}
