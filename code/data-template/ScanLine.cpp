//
// Created by leo on 24-8-17.
//

//https://www.luogu.com.cn/problem/P5490
#include <cstdio>
#include <iostream>
#include <algorithm>
#define ls (x << 1)
#define rs (x << 1 | 1)
using namespace std;
const int MAXN = 1e6 + 10;
typedef long long ll;

int n, cnt = 0;
ll x1, y1, x2, y2, X[MAXN << 1];

struct ScanLine {
	ll l, r, h;
	int mark;
	bool operator < (const ScanLine& rhs) const {
		return h < rhs.h;
	}
} line[MAXN << 1];

struct SegTree {
	int l, r, sum;
	ll len;
} tree[MAXN << 2];

void build_tree(int x, int l, int r) {
	tree[x].l = l, tree[x].r = r;
	tree[x].len = 0;
	tree[x].sum = 0;
	if (l == r)
		return;
	int mid = (l + r) >> 1;
	build_tree(ls, l, mid);
	build_tree(rs, mid + 1, r);
	return;
}

void pushup(int x) {
	int l = tree[x].l, r = tree[x].r;
	if (tree[x].sum )tree[x].len = X[r + 1] - X[l];
	else tree[x].len = tree[ls].len + tree[rs].len;
}

void edit_tree(int x, ll L, ll R, int c) {
	int l = tree[x].l, r = tree[x].r;
	if (X[r + 1] <= L || R <= X[l])
		return;
	if (L <= X[l] && X[r + 1] <= R) {
		tree[x].sum += c;
		pushup(x);
		return;
	}
	edit_tree(ls, L, R, c);
	edit_tree(rs, L, R, c);
	pushup(x);
}

int main() {
	cin >> n;
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		cin >> x1 >> y1 >> x2 >> y2;
		X[++cnt] = x1;
		line[cnt] = (ScanLine){ x1, x2, y1, 1 };
		X[++cnt] = x2;
		line[cnt] = (ScanLine){ x1, x2, y2, -1 };
	}
	sort(line + 1, line + cnt + 1);
	sort(X + 1, X + cnt + 1);
	int tot = unique(X + 1, X + cnt + 1) - X - 1;
	build_tree(1, 1, tot - 1);
	ll ans = 0;
	for (int i = 1; i < cnt; i++) {
		edit_tree(1, line[i].l, line[i].r, line[i].mark);
		ans += tree[1].len * (line[i + 1].h - line[i].h);
	}
	printf("%lli", ans);
	return 0;
}