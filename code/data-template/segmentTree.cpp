//
// Created by leo on 24-8-17.
//


//https://www.luogu.com.cn/problem/P3372
//线段树1

//动态开点

#include<iostream>
using namespace std;
using ll = long long;
const int N = 1e5 + 12;
int cnt;
struct node {
    ll val, lazy, ls, rs;
};
#define ls tr[rt].ls
#define rs tr[rt].rs
node tr[N << 2];
int A[N];
void update(int rt) {
    tr[rt].val = tr[ls].val + tr[rs].val;
}

int build(int l, int r) {
    int rt = ++cnt;
    if (l == r) {
        tr[rt].val = A[l];
        return rt;
    }
    int m = (l + r) / 2;
    ls = build(l, m);
    rs = build(m + 1, r);
    update(rt);
    return rt;
}

void addtag(int rt,int lsize,int rsize) {
    if (tr[rt].lazy) {
        tr[ls].val += tr[rt].lazy * lsize;
        tr[rs].val += tr[rt].lazy * rsize;
        tr[ls].lazy += tr[rt].lazy;
        tr[rs].lazy += tr[rt].lazy;
        tr[rt].lazy = 0;
    }
}

void pushDown(int rt, int lsize, int rsize) {
    addtag(rt, lsize, rsize);
}

void range_update(int L, int R, int val, int l, int r, int rt) {
    if (L <= l && r <= R) {
        tr[rt].val += val * (r - l + 1);
        tr[rt].lazy += val;
        return;
    }
    int m = (l + r) / 2;
    pushDown(rt, m - l + 1, r - m);
    if (L <= m)range_update(L, R, val, l, m, ls);
    if (R > m)range_update(L, R, val, m + 1, r, rs);
    update(rt);

}

ll range_query(int L, int R, int l, int r, int rt) {
    if (L <= l && r <= R) {
        return tr[rt].val;
    }
    int m = (l + r) / 2;
    ll res = 0;
    pushDown(rt, m - l + 1, r - m);
    if (L <= m)res += range_query(L, R, l, m, ls);
    if (R > m)res += range_query(L, R, m + 1, r, rs);
    return res;
}

int main() {
    int n, q; cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
    }
    build(1, n);
    while (q--) {
        int op, x, y; cin >> op >> x >> y;
        if (op == 1) {
            int k; cin >> k;
            range_update(x, y, k, 1, n, 1);
        }
        else if (op == 2) {
            cout << range_query(x, y, 1, n, 1) << endl;
        }
    }
    return 0;
}