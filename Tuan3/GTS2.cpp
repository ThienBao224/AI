#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

#define max 2000

vector<int> tour(max), bestTour(max), visit(max);
int c[max][max];

int selectNextCity(int c[max][max], int n, int currentCity) {
    int minCost = INT_MAX;
    int nextCity = -1;
    for (int i = 1; i <= n; ++i) {
        if (visit[i] == 0 && c[currentCity][i] < minCost) {
            minCost = c[currentCity][i];
            nextCity = i;
        }
    }
    return nextCity;
}

int GTS1(int c[max][max], int n, int starCity) {
    int w, d = 1, cost = 0;
    tour[d] = starCity;
    visit[starCity] = 1;
    int currentCity = starCity;
    for (int i = 1; i <= n - 1; ++i) {
        w = selectNextCity(c, n, currentCity);
        tour[++d] = w;
        visit[w] = 1;
        cost += c[currentCity][w];
        currentCity = w;
    }
    cost += c[currentCity][starCity];
    return cost;
}

void GTS2(int c[max][max], int n, vector<int>& startCities) {
    int minCostGTS1 = INT_MAX;
    int bestCityGTS1 = -1;

    for (int startCity : startCities) {
        visit.assign(n + 1, 0);
        int cost = GTS1(c, n, startCity);
        if (cost < minCostGTS1) {
            minCostGTS1 = cost;
            bestCityGTS1 = startCity;
            bestTour = tour;
        }
    }

    int minCostGTS2 = INT_MAX;
    int bestCityGTS2 = -1;
    for (int startCity : startCities) {
        visit.assign(n + 1, 0);
        int cost = GTS1(c, n, startCity);
        if (cost < minCostGTS2) {
            minCostGTS2 = cost;
            bestCityGTS2 = startCity;
        }
    }

    if (minCostGTS2 < minCostGTS1) {
        cout << "Best starting city (GTS2): " << bestCityGTS2 << endl;
        cout << "Cost (GTS2): " << minCostGTS2 << endl;
        cout << "Tour (GTS2): ";
        for (int i = 1; i <= n; ++i) {
            cout << bestTour[i];
            if (i < n) cout << " -> ";
        }
        cout << endl;
    } else {
        cout << "Best starting city: " << bestCityGTS1 << endl;
        cout << "Cost : " << minCostGTS1 << endl;
        cout << "Tour : ";
        for (int i = 1; i <= n; ++i) {
            cout << bestTour[i];
            if (i < n) cout << " -> ";
        }
        cout << endl;
    }
}

void readFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Khong tim thay file.\n";
        return;
    }
    int n, p;
    file >> n >> p;
    vector<int> startCities(p);
    for (int i = 0; i < p; ++i) {
        file >> startCities[i];
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            file >> c[i][j];
        }
    }
    GTS2(c, n, startCities);
}

int main() {
    string filename = "GTS2b.txt";
    readFile(filename);
    return 0;
}
