//
// Created by leo on 24-8-17.
//


#include<iostream>
#include<algorithm>
using namespace std;
const int N = 2e5 + 21;
using ll = long long;
int node[N];
struct Edge {
    int u, v, val;
}e[N];
int f(int x) {
    while (node[x] != x) x = node[x];
    return x;
}
void Kruskal(int n, int m) {
    int ans = 0, en = 0;
    for (int i = 1; i <= n; i++)node[i] = i;
    sort(e + 1, e + m + 1, [](Edge a, Edge b) {return a.val < b.val; });
    for (int i = 1; i <= m; i++) {
        int t1 = f(e[i].u);
        int t2 = f(e[i].v);
        if (t1 != t2){
            node[t1] = t2;
            ans += e[i].val;
            en++;
        }
    }
    if (en == n - 1)cout << ans;
    else cout << "orz";
}
int main() {
    int n, m; cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> e[i].u >> e[i].v >> e[i].val;
    }
    Kruskal(n, m);
    return 0;
}