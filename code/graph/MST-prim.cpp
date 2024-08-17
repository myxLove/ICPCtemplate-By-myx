//
// Created by leo on 24-8-17.
//

//prim
#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;
using ll = long long;
const int N = 2e5 + 21;
int vis[N], n, m;
using E = pair<int,int>;
vector<E> G[N];
void prim(int s) {
    priority_queue<E,vector<E>,greater<E>> q;
    q.emplace(s,0);
    int ans = 0, cnt = 0;
    while (!q.empty()) {
        auto [u , w] = q.top(); q.pop();
        if (vis[u])continue;
        vis[u] = 1;
        ans += w;cnt++;
        for (int i = 0; i < G[u].size(); i++) {
            auto [to,val] = G[u][i];
            if (vis[to])continue;
            q.emplace(to,val);
        }
    }
    if (cnt == n)cout << ans;
    else cout << "orz";
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int a, b, w; cin >> a >> b >> w;
        G[a].push_back({b, w});
        G[b].push_back({a, w});
    }
    prim(1);
    return 0;
}