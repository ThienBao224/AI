#include <iostream>
#include <fstream>

using namespace std;
#define max 2000

int tour[max], visit[max], c[max][max];

int selectnextcity(int c[max][max], int n, int currentcity) {
    int minCost = INT_MAX;
    int nextcity = -1;
    for (int i = 1; i <= n; ++i) {
        if (visit[i] == 0 && c[currentcity][i] < minCost) {
            minCost = c[currentcity][i];
            nextcity = i;
        }
    }
    return nextcity;
}

void GTS1(int c[max][max], int n, int starcity) {
    int w, d = 1, cost = 0;
    tour[d] = starcity;
    visit[starcity] = 1;
    int currentcity = starcity;
    for (int i = 1; i <= n - 1; ++i) {
        w = selectnextcity(c, n, currentcity);
        tour[++d] = w;
        visit[w] = 1;
        cost += c[currentcity][w];
        currentcity = w;
    }
    cost += c[currentcity][starcity];
    tour[++d] = starcity;
    cout << "Tour: ";
    for (int i = 1; i <= n + 1; ++i) {
        cout << tour[i];
        if (i < n + 1) {
            cout << " -> ";
        }
    }
    cout << endl;
    cout << "Cost: " << cost << endl;
}

void readFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Khong tim thay file.\n";
        return;
    }
    int n, starcity;
    file >> n >> starcity;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            file >> c[i][j];
        }
    }
    GTS1(c, n, starcity);
}

int main() {
    string filename = "GTS1a.txt";
    readFile(filename);
    return 0;
}

