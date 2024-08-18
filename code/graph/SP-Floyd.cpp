//
// Created by leo on 24-8-17.
//

#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int N = 300;
int dp[N][N];
int n, m;

void Floyd() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
            }
        }
    }
}

int main() {
    cin >> n >> m;
    memset(dp, 0x3f, sizeof(dp));					//初始化dp数组
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        dp[u][v] = dp[v][u] = min(dp[u][v],w);		//防止出现重边
    }

    Floyd();

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j)cout << 0 << " ";
            else cout << dp[i][j] << " ";
        }
        cout << '\n';
    }
    return 0;
}