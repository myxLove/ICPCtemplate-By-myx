//
// Created by leo on 24-8-17.
//

//https://www.luogu.com.cn/problem/P3690
//lct + lca

#include<iostream>
using namespace std;
const int N = 3e5 + 12;
#define ls t[x].ch[0]
#define rs t[x].ch[1]
int st[N];
struct node {
	int fa, ch[2], val, s, lazy;
}t[N];
void pushup(int x) {
	t[x].s = t[x].val ^ t[rs].s ^ t[ls].s;
}
bool nRoot(int x) {
	int f = t[x].fa;
	return t[f].ch[0] == x || t[f].ch[1] == x;
}
void pushr(int x) {
	swap(ls, rs);
	t[x].lazy ^= 1;
}
void pushdown(int x) {
	if (t[x].lazy) {
		if (ls)pushr(ls);
		if (rs)pushr(rs);
		t[x].lazy = 0;
	}
}
void push(int x) {
	if (nRoot(x))push(t[x].fa);
	pushdown(x);
}
void rot(int x) {
	int y = t[x].fa, z = t[y].fa, k = t[y].ch[1] == x, w = t[x].ch[!k];
	if (nRoot(y))t[z].ch[t[z].ch[1] == y] = x; t[x].ch[!k] = y; t[y].ch[k] = w;//额外注意if(nroot(y))语句，此处不判断会引起致命错误（与普通Splay的区别2）
	if (w)t[w].fa = y; t[y].fa = x; t[x].fa = z;
	pushup(y);
}
void splay(int x) {
	int y = x, z = 0;
	//st[++z] = y;
	//while (isRoot(y))st[++z] = y = t[y].fa;
	//while (z)pushdown(st[z--]);
	push(x);
	while (nRoot(x)) {
		y = t[x].fa, z = t[y].fa;
		if (nRoot(y))rot((t[z].ch[0] == y) ^ (t[y].ch[0] == x) ? x : y);
		rot(x);
	}
	pushup(x);
}
int access(int x) {
	int y;
	for (y = 0; x; x = t[y = x].fa)
		splay(x), rs = y, pushup(x);
	return y;
}

int lca(int a, int b) {
	access(a);
	return access(b);
}

//查找根节点
int findroot(int x) {
	access(x);
	splay(x);
	while (ls)pushdown(x), x = ls;
	splay(x);
	return x;
}

//切换树根
void makeroot(int x) {
	access(x);
	splay(x);
	pushr(x);
	//t[x].lazy ^= 1;
}

void link(int a, int b) {
	makeroot(a);
	if(findroot(b) != a)t[a].fa = b;
}

//路径查询
void split(int a, int b) {
	makeroot(a);
	access(b);
	splay(b);
}

void cut(int x, int y) {//断边
	makeroot(x);
	if (findroot(y) == x && t[y].fa == x && !t[y].ch[0]) {
		t[y].fa = t[x].ch[1] = 0;
		pushup(x);
	}
}

int main()
{
	int n, m; cin >> n >> m;
	for (int i = 1; i <= n; ++i)cin >> t[i].val;
	while (m--) {
		int op, a, b; cin >> op >> a >> b;
		switch (op) {
		case 0:split(a, b);cout << t[b].s << '\n'; break;
		case 1:if(findroot(a) != findroot(b))link(a, b); break;
		case 2:cut(a, b); break;
		case 3:splay(a); t[a].val = b;//先把x转上去再改，不然会影响Splay信息的正确性
		}
	}
	return 0;
}