#include <bits/stdc++.h>
using namespace std;

#define MAX 20
#define INF 1e9

int n, dist[MAX][MAX], dp[MAX][1 << MAX], next_vertex[MAX][1 << MAX];

int tsp(int i, int mask) {
    if(mask == (1 << n) - 1) return dist[i][0];
    if(dp[i][mask] != -1) return dp[i][mask];

    int ans = INF;
    for(int j = 0; j < n; j++) {
        if(i != j && !(mask & (1 << j))) {
            int curr = dist[i][j] + tsp(j, mask | (1 << j));
            if(curr < ans) {
                ans = curr;
                next_vertex[i][mask] = j;
            }
        }
    }

    return dp[i][mask] = ans;
}
void print_path(ostream& output) {
    int mask = 1;
    int i = 0;
    while(true) {
        output << i << " ";
        if(mask == (1 << n) - 1) break;
        int j = next_vertex[i][mask];
        mask |= (1 << j);
        i = j;
    }
    output << "0\n";
}

int main() {
    ifstream input("tsp1a.txt");
    input >> n;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            input >> dist[i][j];
        }
    }
    input.close();

    memset(dp, -1, sizeof dp);
    int optimal_cost = tsp(0, 1);

    ofstream output("temp2.txt");
    output << "Best cost: " << optimal_cost << endl;
    output << "Best tour: ";
    print_path(output);
    output.close();

    cout << "Best cost: " << optimal_cost << endl;
    cout << "Best tour: ";
    print_path(cout);

    return 0;
}
