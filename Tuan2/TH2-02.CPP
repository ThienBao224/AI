#include<iostream>
#include<cstring>
using namespace std;

const int MAX = 100;
int n, c[MAX][MAX], dp[MAX][1 << MAX];

int tsp(int current, int mask) {
    if (mask == (1 << n) - 1) {
        return c[current][0];
    }

    if (dp[current][mask] != -1) {
        return dp[current][mask];
    }

    int ans = INT_MAX;
    for (int i = 0; i < n; i++) {
        if ((mask & (1 << i)) == 0) {
            int newMask = mask | (1 << i);
            int cost = c[current][i] + tsp(i, newMask);
            ans = min(ans, cost);
        }
    }

    return dp[current][mask] = ans;
}

void nhap() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> c[i][j];
        }
    }
    memset(dp, -1, sizeof(dp));
}

int main() {
    nhap();
    int ans = tsp(0, 1);
    cout << ans << endl;

    return 0;
}
